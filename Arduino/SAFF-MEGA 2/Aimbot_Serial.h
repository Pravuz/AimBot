#ifndef SERIAL_H
#define SERIAL_H

#define BAUDRATE 115200

enum CMD_ID{
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


#ifdef __ARDUINO
#ifdef __DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif
#include <Arduino.h>

bool debug = DEBUG;

struct AimBot_Serial
{
	AimBot_Serial(HardwareSerial *serial){
		m_serial = serial;
		m_serial->begin(BAUDRATE);
		m_rx = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	void serialUpdate(){
		if (m_serial->available()){
			sync();
			while (true){
				m_rx[len] = m_serial->read();
				if (m_serial->peek() == AIM_SYNC) break;
			}
		}
		if (debug){
			Serial.println("Serial update complete");
		}
		if (debug){}
		switch (m_rx[1])
		{
		case PIXY_PARAM_DELTAP:
			Serial.print("Pixy is now using deltaP setting = ");
			int temp = (char)(m_rx[2] << 8) | (byte)m_rx[3];
			Serial.println(temp);
			break;
		case PIXY_PARAM_NOFP:
			Serial.print("Pixy is now using Number of Pixel-changes treshold setting = ");
			Serial.println(m_rx[2]);
			break;
		default:
			break;
		}
	}

	char getX(){
		if (debug){
			Serial.print("Recieved X-Vector: ");
			Serial.println((char)m_rx[2]);
		}
		if (m_rx[1] == VECTOR)	return (char)m_rx[2];
		else return 0;
	}

	char getY(){
		if (debug){
			Serial.print("Recieved Y-Vector: ");
			Serial.println((char)m_rx[3]);
		}
		if (m_rx[1] == VECTOR)	return (char)m_rx[3];
		else return 0;
	}

	bool isRCmode(){	// check if last recieved coords are RC or pixy-vector
		if (debug){
			Serial.print("Mode RC? : ");
			Serial.println((char)m_rx[1]);
		}
		if (m_rx[1] == VECTOR)	return false;
		else return true;
	}

	void sendVect(char x, char y){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = VECTOR;
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug){
			Serial.println("Sending Vector");
			m_serial->write(m_tx, sizeof(uint8_t)* 4);
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 4);
	}
	void sendRCxy(char x, char y){
		m_tx[0] = AIM_SYNC;  // Sync
		m_tx[1] = MOV_XY;  // Signal the brugi it's in RC mode 
		m_tx[2] = x;
		m_tx[3] = y;
		if (debug){
			//Serial.println("Sending RC xy");  // For debug
			m_serial->write(m_tx, sizeof(uint8_t)* 4);
			//Serial.println();
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 4);  // Write to brugi
	}

	void startPixy(){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_START;
		if (debug){
			Serial.print("Pixy command START: ");
			Serial.println(m_tx[1]);
		}
		m_serial->write(m_rx, sizeof(uint8_t)* 2);
	}

	void stopPixy(){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_STOP;
		if (debug){
			Serial.print("Pixy command STOP: ");
			Serial.println(m_tx[1]);
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 2);
	}

	void sendPosReached(){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = POS_REACHED;
		if (debug){
			Serial.print("ESC Reached position ");
			Serial.println(m_tx[1]);
		}
		m_serial->write(m_tx, sizeof(uint8_t)* 2);
	}

	void flushBuf(){
		delete[] m_tx, m_rx;
		m_serial->flush();
		m_rx = new uint8_t[8];
		m_tx = new uint8_t[8];
	}

	void pixyNOfP(int nofp){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_PARAM_NOFP;
		m_tx[2] = (byte)nofp;
		m_tx[3] = (char)(nofp >> 8);
		m_serial->write(m_tx, sizeof(uint8_t)* 4);
	}

	void pixyDeltaP(char deltaP){
		m_tx[0] = AIM_SYNC;
		m_tx[1] = PIXY_PARAM_DELTAP;
		m_tx[2] = deltaP;
		m_serial->write(m_tx, sizeof(uint8_t)* 3);
	}

private:

	void sync(){
		if (m_serial->peek() != AIM_SYNC){
			while (1)
			{
				if (m_serial->peek() != AIM_SYNC)
					m_serial->read();
				else break;
			}
		}
	}

	HardwareSerial *m_serial;
	uint8_t *m_tx, *m_rx;
	unsigned int len;
};
#endif
#ifdef __PIXY
//todo: move code from greyshades to here
#endif
#ifdef __DESKTOP
#endif
#endif // SERIAL_H
