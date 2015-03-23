#ifndef SERIAL_H
#define SERIAL_H

#define BUF_SIZE 6 //todo: remove this stupid shit
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
	POS_REACHED
};


#ifdef __ARDUINO

struct AimBot_Serial
{

	AimBot_Serial(HardwareSerial *serial){
		m_serial = serial;
		m_serial->begin(BAUDRATE);
	}

	void serialUpdate(){
		if (m_serial->available()){
			sync();
			for (int i = 0; i < 6; i++){
				m_buf[i] = m_serial->read();
			}
		}
	}

	int getX(){
		if (m_buf[1] == VECTOR)	return m_buf[2];
		else return 0;
	}

	int getY(){
		if (m_buf[1] == VECTOR)	return m_buf[3];
		else return 0;
	}

	void sendVect(byte x, byte y){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = VECTOR;
		m_rxbuf[2] = x;
		m_rxbuf[3] = y;
		for (int i = 4; i < 6; i++){
			m_rxbuf[i] = 0;
		}
	}

	void stopPixy(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = PIXY_STOP;
		for (int i = 2; i < 6; i++){
			m_rxbuf[i] = 0;
		}
	}

	void startPixy(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = PIXY_START;
		for (int i = 2; i < 6; i++){
			m_rxbuf[i] = 0;
		}
	}
	void posReached(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = POS_REACHED;
		for (int i = 2; i < 6; i++){
			m_rxbuf[i] = 0;
		}
		m_serial->write(m_rxbuf, 6);
	}
private:

	void sync(){
		if (m_buf[0] != AIM_SYNC){
			while (1)
			{
				if (m_serial->peek() != AIM_SYNC)
					m_serial->read();
				else break;
			}
		}
	}

	int temp;
	HardwareSerial *m_serial;
	byte m_buf[BUF_SIZE];
	byte m_rxbuf[BUF_SIZE];
};

#endif
#ifdef __PIXY
//todo: move code from greyshades to here
#endif
#ifdef __DESKTOP
#endif
#endif // SERIAL_H
