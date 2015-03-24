#ifndef SERIAL_H
#define SERIAL_H

#define BAUDRATE 115200

enum CMD_ID {
	AIM_SYNC = 0xa5,
	VECTOR,
	PIXY_PARAM_NOFP,
	PIXY_PARAM_DELTAP,
	PIXY_STOP,
	PIXY_START,
	MOV_X,
	MOV_Y,
	POS_REACHED,
	MOV_XY
};
#ifdef __MEGA
#ifdef __DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif
#include <Arduino.h>

bool debug = DEBUG;

struct AimBot_Serial
{
	AimBot_Serial() {
		Serial2.begin(BAUDRATE);
		Serial3.begin(BAUDRATE);
		m_rx1 = new uint8_t[8];
		m_rx2 = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	~AimBot_Serial() {
		delete[] m_rx1, m_rx2, m_tx;
	}

	void serialUpdate() {
		//ESC Serial
		if (Serial2.available()) {
			int len = 0;
			syncEsc();
			while (true) {
				m_rx1[len] = Serial2.read();
				len++;
				if (Serial2.peek() == AIM_SYNC) break;
			}
		}
		if (debug) {
			Serial.println("Serial update complete");
			int temp = 0;
		}

		//Pixy Serial
		if (Serial3.available()) {
			int len = 0;
			syncPixy();
			while (true) {
				m_rx2[len] = Serial3.read();
				len++;
				if (Serial3.peek() == AIM_SYNC) break;
			}
		}
		if (debug) {
			Serial.println("Serial update complete");
			int temp = 0;
			switch (m_rx2[1])
			{
			case PIXY_PARAM_DELTAP:
				Serial.print("Pixy is now using deltaP setting = ");
				temp = (int)((char)(m_rx2[2] << 8) | (byte)m_rx2[3]);
				Serial.println(temp);
				break;
			case PIXY_PARAM_NOFP:
				Serial.print("Pixy is now using Number of Pixel-changes treshold setting = ");
				Serial.println(m_rx2[2]);
				break;
			default:
				break;
			}
		}
	}

	char getX() {
		if (debug) {
			Serial.print("Recieved X-Vector: ");
			Serial.println((char)m_rx2[2]);
		}
		if (m_rx2[1] == VECTOR) return (char)m_rx2[2];
		else return 0;
	}

	char getY() {
		if (debug) {
			Serial.print("Recieved Y-Vector: ");
			Serial.println((char)m_rx2[3]);
		}
		if (m_rx2[1] == VECTOR) return (char)m_rx2[3];
		else return 0;
	}

	void sendVect(char x, char y) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = VECTOR;
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug) {
			Serial.println("Sending Vector");
			Serial.write(m_tx, sizeof(uint8_t)* 4);
		}
		Serial2.write(m_tx, sizeof(uint8_t)* 4);
	}
	void sendRCxy(char x, char y) {
		m_tx[0] = AIM_SYNC;  // Sync
		m_tx[1] = MOV_XY;// Signal the brugi it's in RC mode
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug) {
			Serial.println("Sending RC xy");  // For debug
			//Serial.write(m_tx, sizeof(uint8_t)* 4);
			for (int i = 0; i < 4; i++)
			{
				Serial.print(m_tx[i]);
				Serial.print(" ");
			}
			Serial.println();
		}
		Serial2.write(m_tx, sizeof(uint8_t)* 4);  // Write to brugi
	}

	void startPixy() {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_START;
		if (debug) {
			Serial.print("Pixy command START: ");
			Serial.println(m_tx[1]);
		}
		Serial3.write(m_tx, sizeof(uint8_t)* 2);
	}

	void stopPixy() {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_STOP;
		if (debug) {
			Serial.print("Pixy command STOP: ");
			Serial.println(m_tx[1]);
		}
		Serial3.write(m_tx, sizeof(uint8_t)* 2);
	}

	void flushBuf() {
		delete[] m_tx, m_rx1, m_rx2;
		Serial2.flush();
		Serial3.flush();
		m_rx1 = new uint8_t[8];
		m_rx2 = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	void pixyNOfP(int nofp) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_PARAM_NOFP;
		m_tx[2] = (byte)nofp;
		m_tx[3] = (char)(nofp >> 8);
		Serial3.write(m_tx, sizeof(uint8_t)* 4);
	}

	void pixyDeltaP(char deltaP) {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_PARAM_DELTAP;
		m_tx[2] = deltaP;
		Serial3.write(m_tx, sizeof(uint8_t)* 3);
	}

private:

	void syncEsc() {
		if (Serial2.peek() != AIM_SYNC) {
			while (1)
			{
				if (Serial2.peek() != AIM_SYNC)
					Serial2.read();
				else break;
			}
		}
	}

	void syncPixy() {
		if (Serial3.peek() != AIM_SYNC) {
			while (1)
			{
				if (Serial3.peek() != AIM_SYNC)
					Serial3.read();
				else break;
			}
		}
	}

	uint8_t *m_tx, *m_rx1, *m_rx2;
	unsigned int len;
};
#endif
#ifdef __ESC

struct AimBot_Serial
{
	AimBot_Serial() {
		Serial.begin(BAUDRATE);
		m_rx = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	~AimBot_Serial() {
		delete[] m_rx, m_tx;
	}

	void serialUpdate() {
		//ESC Serial
		if (Serial.available()) {
			int len = 0;
			sync();
			while (true) {
				m_rx[len] = Serial.read();
				len++;
				if (Serial.peek() == AIM_SYNC) break;
			}
		}
	}

	char getX() {
		if (m_rx[1] == VECTOR) return (char)m_rx[2];
		else return 0;
	}

	char getY() {
		if (m_rx[1] == VECTOR) return (char)m_rx[3];
		else return 0;
	}
	void sendPosReached() {
		m_tx[0] = AIM_SYNC;
		m_tx[1] = POS_REACHED;
		Serial.write(m_tx, sizeof(uint8_t)* 2);
	}

	bool isRCmode() {	// check if last recieved coords are RC or pixy-vector
		if (m_rx[1] == VECTOR) return false;
		else return true;
	}

private:
	void sync(){

	}
	uint8_t *m_tx, *m_rx;
	unsigned int len;
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
