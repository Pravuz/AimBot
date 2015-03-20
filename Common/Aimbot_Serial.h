#ifndef SERIAL_H
#define SERIAL_H

#define BUF_SIZE 6
#define BAUDRATE 115200

enum CMD_ID {
	SYNC = 0xa5,
	VECTOR,
	PIXY_PARAM_NOFP,
	PIXY_PARAM_DELTAP,
	PIXY_STOP,
	PIXY_START,
	MOV_X,
	MOV_Y,
	POS_REACHED
};


#ifndef __ARDUINO


struct AimBot_Serial
{

	AimBot_Serial(HardwareSerial *serial, unsigned long baudrate){
		m_serial = serial;
		m_serial->begin(baudrate);
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
	void posReached(){
		m_rxbuf[0] = SYNC;
		m_rxbuf[1] = POS_REACHED;
		for (int i = 2; i < 6; i++){
			m_rxbuf[i] = 0;
		}
		m_serial->write(m_rxbuf, 6);
	}
private:

	void sync(){
		if (m_buf[0] != SYNC){
			while (1)
			{
				if (m_serial->peek() != SYNC)
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

#endif
#ifdef __DESKTOP
#endif
#endif // SERIAL_H