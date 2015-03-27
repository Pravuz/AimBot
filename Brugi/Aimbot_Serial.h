#ifndef SERIAL_H
#define SERIAL_H
#define BAUDRATE 115200
#ifdef __MEGA
#include <Arduino.h>
#endif
#ifdef __ESC
#include <Arduino.h>
#endif 
#ifdef __DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

bool debug = DEBUG;

enum CMD_ID {
	AIM_SYNC = 0xa5,
	VECTOR,
	MOV_XY,
	POS_REACHED,
	PIXY_PARAM_NOFP,
	PIXY_PARAM_DELTAP,
	PIXY_STOP,
	PIXY_START
};

struct baseArduinoSerial {

	baseArduinoSerial(HardwareSerial *serial){
		m_serial = serial;
		m_serial->begin(BAUDRATE);
		m_rx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		m_tx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
	}

	void flush() {
		m_serial->flush();
		m_rx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		m_tx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		free(m_rx);
		free(m_tx);
	}

	bool update(){
		if (m_serial->available()) {
			int len = 0;
			if (!sync()) {
				if (debug) Serial.println("Serial update failed");
				return false;
			}
			while (true) {
				m_rx[len] = m_serial->read();
				len++;
				if (m_serial->peek() == AIM_SYNC) break;
			}
			if (debug) Serial.println("Serial update complete");
			return true;
		}
	}

	char getX() {
		if (debug) {
			if (m_rx[1] == VECTOR) {
				Serial.print("Recieved X-Vector: ");
				Serial.println((char)m_rx[2]);
			}
			else{
				Serial.println("Have not recieved X");
			}
		}
		if (m_rx[1] == VECTOR) return (char)m_rx[2];
		else return 0;
	}

	char getY() {
		if (debug) {
			if (m_rx[1] == VECTOR) {
				Serial.print("Recieved Y-Vector: ");
				Serial.println((char)m_rx[3]);
			}
			else{
				Serial.println("Have not recieved Y");
			}
		}
		if (m_rx[1] == VECTOR) return (char)m_rx[3];
		else return 0;
	}

	void sendXY(char x, char y, CMD_ID type){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = type;
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug) {
			Serial.println("Sending XY");
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 4);
	}

protected:
	~baseArduinoSerial(){
		m_serial->end();
		free(m_rx);
		free(m_tx);
	}

	bool sync(){
		if (m_serial->peek() != AIM_SYNC) {
			unsigned int timeout = 0;
			while (1)
			{
				if (timeout > 1000) return false;
				if (m_serial->peek() != AIM_SYNC){
					m_serial->read();
					timeout++;
				}
				else return true;
			}
		}
	}

	uint8_t *m_tx, *m_rx;
	HardwareSerial *m_serial;
};

#ifdef __MEGA
struct AimBot_Serial : public baseArduinoSerial
{

	AimBot_Serial(HardwareSerial *serial) : baseArduinoSerial(serial){}

	void pixyCmd(CMD_ID cmd){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = cmd;
		if (debug) {
			Serial.print("Pixy command: ");
			Serial.println(m_tx[1]);
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 2);
	}

	void pixyCmd(CMD_ID cmd, unsigned int value){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = cmd;
		switch (cmd)
		{
		case PIXY_PARAM_NOFP:
			m_tx[2] = value;
			m_tx[3] = value >> 8;
			Serial3.write(m_tx, sizeof(uint8_t)* 4);
			break;
		case PIXY_PARAM_DELTAP:
			m_tx[2] = value;
			m_serial->write(m_tx, sizeof(uint8_t)* 3);
			break;
		}
	}

	void pixyDeltaP(char deltaP) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_PARAM_DELTAP;
	}
};
#endif
#ifdef __ESC

struct AimBot_Serial : baseArduinoSerial
{
	AimBot_Serial(HardwareSerial *serial) : baseArduinoSerial(serial){}

	void sendPosReached() {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = POS_REACHED;
		Serial.write(m_tx, sizeof(uint8_t)* 2);
	}

	bool isRCmode() {	// check if last recieved coords are RC or pixy-vector
		if (m_rx[1] == VECTOR) return false;
		else return true;
	}
};
#endif
#ifdef __PIXY
//todo: move code from greyshades to here

#include "lpc43xx_uart.h"

struct AimBot_Serial {

	AimBot_Serial() {
		scu_pinmux(0x2, 0, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC1); // U0_TXD
		scu_pinmux(0x2, 1, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC1);// U0_RXD
		scu_pinmux(0x1, 3, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC0);// turn SSP1_MISO into GPIO0[10]
		scu_pinmux(0x1, 4, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC0);// turn SSP1_MOSI into GPIO0[11]

		UART_CFG_Type ucfg;
		// regular config
		ucfg.Baud_rate = 115200;
		ucfg.Databits = UART_DATABIT_8;
		ucfg.Parity = UART_PARITY_NONE;
		ucfg.Stopbits = UART_STOPBIT_1;
		ucfg.Clock_Speed = CLKFREQ;
		UART_Init(LPC_USART0, &ucfg);
		UART_TxCmd(LPC_USART0, ENABLE);

		m_rx = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	~AimBot_Serial() {
		//reset pinmux
		scu_pinmux(0x2, 0, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC4); 	   // U0_TXD
		scu_pinmux(0x2, 1, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC4);// U0_RXD

		NVIC_DisableIRQ(USART0_IRQn);

		//delete buffer reservation
		delete[] m_rx, m_tx;
	}

	uint32_t updateSerial() {
		uint8_t timeout = 250;
		while (UART_CheckBusy(LPC_USART0) == SET) {
			timeout--;
			if (timeout = 0)
				return 0;
		}
		if (UART_Receive(LPC_USART0, m_rx, 6 * sizeof(uint8_t), NONE_BLOCKING)
				> 0) {
			if (m_rx[0] == AIM_SYNC) {
				switch (m_rx[1]) {
				case PIXY_PARAM_NOFP:
					uint16_t m_nOfP;
					m_nOfP = m_rx[2] << 8 | m_rx[3];
					g_greyShades.setParams(g_greyShades.deltaP, m_nOfP);
					g_greyShades.reset();
					break;
				case PIXY_PARAM_DELTAP:
					uint8_t m_deltaP;
					m_deltaP = m_rx[2];
					g_greyShades.setParams(m_deltaP, g_greyShades.nOfP);
					g_greyShades.reset();
					break;
				case PIXY_START:
					if (!running) {
						running = true;
						g_greyShades.reset();
					}
					break;
				case PIXY_STOP:
					if (running) {
						running = false;
						g_greyShades.reset();
					}
					break;
				}
				return 1;
			} else {
				sync();
			}
		}
		return 0;
	}

	uint32_t sendVector(sPoint16 &p) {
		//startbyte
		m_tx[0] = AIM_SYNC;
		m_tx[1] = VECTOR;
		//data
#if 1
		if (p.m_x > 127)
			m_tx[2] = 127;
		else if (p.m_x < -127)
			m_tx[2] = -127;
		else
			m_tx[2] = (int8_t) p.m_x;
		m_tx[3] = (int8_t) p.m_y;

#endif
		uint8_t timeout = 250;
		while (UART_CheckBusy(LPC_USART0) == SET) {
			timeout--;
			if (timeout = 0)
				return 0;
		}
		return UART_Send(LPC_USART0, m_tx, 4 * sizeof(uint8_t), NONE_BLOCKING);
	}

private:

	void sync() {
		//how to sync??
	}

	uint8_t *m_tx, *m_rx;
};
#endif
#ifdef __DESKTOP
#endif
#endif // SERIAL_H
