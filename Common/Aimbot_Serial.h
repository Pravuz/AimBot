#ifndef SERIAL_H
#define SERIAL_H
#define BAUDRATE 115200

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

#if defined(__MEGA) || defined(__ESC)
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
struct baseArduinoSerial {

	baseArduinoSerial(Stream &serial):m_serial(serial) {
		m_tx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		m_rx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
	}

	void flush() {
		//flush local rx buffer
		for (int i = 0; i <= 3; i++) m_rx[i] = 0;
	}

	bool update() {
		if (m_serial.available()>4) {
			int len = 0;
			if (!sync()) {
				if (debug) Serial.println("Serial update: failed");
				return false;
			}
			while (true) {
				m_rx[len] = (uint8_t)m_serial.read();
				len++;
				if ((uint8_t)m_serial.peek() == AIM_SYNC) break; //next packet will have to wait.
			}
			if (debug)
			{
				Serial.println("Serial update: complete");
				for (int i = 0; i <= len; i++) Serial.print(m_rx[i], HEX);
				Serial.println();
			}
			return true;
		}
		if (debug) Serial.println("Serial update: Nothing recieved");
		return false;
	}

	char getX() {
		if (debug) {
			if (m_rx[1] == VECTOR || m_rx[1] == MOV_XY) {
				Serial.print("Recieved X-Vector: ");
				Serial.println((char)m_rx[2],DEC);
			}
			else {
				Serial.println("Have not recieved X");
			}
		}
		if (m_rx[1] == VECTOR || m_rx[1] == MOV_XY) return (char)m_rx[2];
		return 0;
	}

	char getY() {
		if (debug) {
			if (m_rx[1] == VECTOR || m_rx[1] == MOV_XY) {
				Serial.print("Recieved Y-Vector: ");
				Serial.println((char)m_rx[3],DEC);
			}
			else {
				Serial.println("Have not recieved Y");
			}
		}
		if (m_rx[1] == VECTOR || m_rx[1] == MOV_XY) return (char)m_rx[3];
		return 0;
	}

	void sendXY(char x, char y, CMD_ID type) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = type;
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug) {
			Serial.print("Sending XY: ");
			Serial.print(AIM_SYNC, HEX);
			Serial.print(" ");
			Serial.print(type, HEX);
			Serial.print(" ");
			Serial.print(x, DEC);
			Serial.print(" ");
			Serial.print(y, DEC);
			Serial.println();
		}
		m_serial.write(m_tx, sizeof(uint8_t)* 4);
	}

protected:
	~baseArduinoSerial() {
		free(m_rx);
		free(m_tx);
	}

	bool sync() {
		if ((uint8_t)m_serial.peek() != AIM_SYNC) {
			m_serial.read();
			uint16_t timeout = 0;
			while (m_serial.available()>1)
			{
				if (timeout > 20) return false;
				if ((uint8_t)m_serial.peek() != AIM_SYNC) {
					m_serial.read();
					timeout++;
				}
				else return true;
			}
		}
		else return true;
	}

	uint8_t *m_tx, *m_rx;
	Stream &m_serial;
};
#endif
#ifdef __MEGA
struct AimBot_Serial : public baseArduinoSerial
{
	AimBot_Serial(Stream &serial): baseArduinoSerial(serial) {}

	void flush() {
		while (m_serial.available() > 0) m_serial.read();
		for (int i = 0; i <= 3; i++) m_rx[i] = 0;
	}

	void pixyCmd(CMD_ID cmd) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = cmd;
		if (debug) {
			Serial.print("Pixy command: ");
			Serial.println(m_tx[1],HEX);
		}
		m_serial.write(m_tx, sizeof(uint8_t)* 2);
	}

	void pixyCmd(CMD_ID cmd, unsigned int value) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = cmd;
		switch (cmd)
		{
			case PIXY_PARAM_NOFP:
			m_tx[2] = value;
			m_tx[3] = value >> 8;
			m_serial.write(m_tx, sizeof(uint8_t)* 4);
			break;
			case PIXY_PARAM_DELTAP:
			m_tx[2] = value;
			m_serial.write(m_tx, sizeof(uint8_t)* 3);
			break;
		}
	}
	using baseArduinoSerial::m_rx;
	using baseArduinoSerial::m_tx;
	using baseArduinoSerial::m_serial;
};
#endif
#ifdef __ESC

struct AimBot_Serial : baseArduinoSerial
{
	AimBot_Serial(Stream &serial) : baseArduinoSerial(serial) {}

	void sendPosReached() {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = POS_REACHED;
		m_serial.write(m_tx, sizeof(uint8_t)* 2);
	}

	bool isRCmode() {	// check if last recieved coords are RC or pixy-vector
		if (m_rx[1] == VECTOR) return false;
		return true;
	}
	using baseArduinoSerial::m_rx;
	using baseArduinoSerial::m_tx;
	using baseArduinoSerial::m_serial;
};
#endif
#ifdef __PIXY

#include "lpc43xx_uart.h"

struct AimBot_Serial {

	AimBot_Serial() {
#if 0
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

		//m_tx = new uint8_t[4];
		//m_rx = new uint8_t[4];
		m_tx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		m_rx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
#endif
	}

	~AimBot_Serial() {
		//reset pinmux
		scu_pinmux(0x2, 0, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC4);// U0_TXD
		scu_pinmux(0x2, 1, (MD_PLN | MD_EZI | MD_ZI | MD_EHS), FUNC4);// U0_RXD

		NVIC_DisableIRQ(USART0_IRQn);

		//delete buffer reservation
		//delete[] m_tx, m_rx;
		free(m_tx);
		free(m_rx);
	}

	void setupSerial() {
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

		//m_tx = new uint8_t[4];
		//m_rx = new uint8_t[4];
		m_tx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
		m_rx = (uint8_t*)malloc(sizeof(uint8_t)* 4);
	}

	uint32_t updateSerial() {

		//Checking if line is busy
		uint8_t timeOut = 250;
		while (UART_CheckBusy(LPC_USART0) == SET) {
			if (timeOut = 0) return 0;
			timeOut--;
		}

		//waiting for line to be ready
		timeOut = UART_BLOCKING_TIMEOUT;
		while (!(LPC_USART0->LSR & UART_LSR_RDR)) {
			if (timeOut == 0) return 0;
			timeOut--;
		}

		//Synchronizing
		timeOut = 20;
		while(true) {
			if(LPC_USART0->LSR & UART_LSR_RDR) {
				m_rx[0] = UART_ReceiveByte(LPC_USART0);
				if(m_rx[0] == AIM_SYNC) break; //now in sync
				if(timeOut == 0) return 0;//Data is corrupted or something is terribly wrong.
				timeOut--;
			}
		}

		//handling package.
		if(LPC_USART0->LSR & UART_LSR_RDR && m_rx[0] == AIM_SYNC) { //need to test if we actually recieved a package with sync.
			m_rx[1] =UART_ReceiveByte(LPC_USART0);
			switch (m_rx[1]) {
				case PIXY_PARAM_NOFP:
				uint16_t m_nOfP;

				//recieve the rest of the package
				m_rx[2] = UART_ReceiveByte(LPC_USART0);
				m_rx[3] = UART_ReceiveByte(LPC_USART0);

				m_nOfP = m_rx[2] << 8 | m_rx[3];
				g_greyShades.setParams(g_greyShades.deltaP, m_nOfP);
				g_greyShades.reset();
				break;

				case PIXY_PARAM_DELTAP:
				uint8_t m_deltaP;

				//recieve the rest of the package
				m_rx[2] = UART_ReceiveByte(LPC_USART0);

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
			m_rx[0] = 0; //making sure this sync will count for next update.
			return 1;//win
		}
#if 0
		if (UART_Receive(LPC_USART0, m_rx, 6, BLOCKING)
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
#endif
		//propably never reached.
		m_rx[0] = 0;//making sure this sync will count for next update.
		return 0;//fail
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
		return UART_Send(LPC_USART0, m_tx, 4 * sizeof(uint8_t), BLOCKING);
	}

private:
	uint8_t *m_tx, *m_rx;
};
#endif
#ifdef __DESKTOP
#endif
#endif // SERIAL_H
