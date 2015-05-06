#ifndef SERIAL_H
#define SERIAL_H

#define BUF_SIZE 6 //todo: remove this stupid shit
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
	POS_REACHED
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
	}

	void serialUpdate(){
		if (m_serial->available()){
			sync();
			for (int i = 0; i < BUF_SIZE; i++){
				m_buf[i] = m_serial->read();
			}
		}
		if (debug){
			Serial.println("Serial synchronization complete");
		}
#if 0
		//RECIEVE COMMANDS
		switch (m_buf[1])
		{
		case POS_REACHED:
			break;
		default:
			break;
		}
#endif
	}

	char getX(){
		if (debug){
			Serial.print("Recieved X-Vector: ");
			Serial.println((char)m_buf[2]);
		}
		if (m_buf[1] == VECTOR)	return (char)m_buf[2];
		else return 0;
	}

	char getY(){
		if (debug){
			Serial.print("Recieved Y-Vector: ");
			Serial.println((char)m_buf[3]);
		}
		if (m_buf[1] == VECTOR)	return (char)m_buf[3];
		else return 0;
	}

	void sendVect(char x, char y){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = VECTOR;
		m_rxbuf[2] = x;
		m_rxbuf[3] = y;
		for (int i = 4; i < BUF_SIZE; i++){
			m_rxbuf[i] = 0;
		}
		if (debug){
			Serial.println("Sending Vector");
			for (int i = 0; i < BUF_SIZE; i++) Serial.print(i);
			Serial.println();
		}
		m_serial->write(m_rxbuf, BUF_SIZE);
	}

	void startPixy(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = PIXY_START;
		for (int i = 2; i < BUF_SIZE; i++){
			m_rxbuf[i] = 0;
		}
		if (debug){
			Serial.print("Pixy command START: ");
			Serial.println(m_rxbuf[1]);
		}
		m_serial->write(m_rxbuf, BUF_SIZE);
	}
	
	void stopPixy(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = PIXY_STOP;
		for (int i = 2; i < BUF_SIZE; i++){
			m_rxbuf[i] = 0;
		}
		if (debug){
			Serial.print("Pixy command STOP: ");
			Serial.println(m_rxbuf[1]);
		}
		m_serial->write(m_rxbuf, BUF_SIZE);
	}

	void sendPosReached(){
		m_rxbuf[0] = AIM_SYNC;
		m_rxbuf[1] = POS_REACHED;
		for (int i = 2; i < BUF_SIZE; i++){
			m_rxbuf[i] = 0;
		}if (debug){
			Serial.print("ESC Reached position ");
			Serial.println(m_rxbuf[1]);
		}
		m_serial->write(m_rxbuf, BUF_SIZE);
	}
	
	void flushBuf(){
		delete[] m_rxbuf, m_buf;
		m_serial->flush();
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
	byte m_buf[BUF_SIZE];
	byte m_rxbuf[BUF_SIZE];
};

#endif
#ifdef __PIXY
//todo: move code from greyshades to here
#endif
#ifdef __DESKTOP
public ref struct AimBot_Serial
{

	AimBot_Serial(System::IO::Ports::SerialPort^ serial){
		m_serial = serial;
		m_serial->BaudRate = BAUDRATE;
	}

	array<Object^>^ findPorts(){
		return m_serial->GetPortNames();
	}

	void setName(System::String^ portName){
		m_serial->PortName = portName;
	}

	System::String^ readS(){
		return m_serial->ReadLine();
	}

	void openPort(){
		m_serial->Open();
	}

	void closePort(){
		m_serial->Close();
	}

	int status(){
		int test = 1;
		if (m_serial->IsOpen == true)
		{
			test = 0;
		}
		else
		{
			test = 1;
		}
		return test;
	}

	void request(){
		m_serial->WriteLine("sendx");
	}
	void sendSettings(System::String^ newSettings){

		m_serial->WriteLine(newSettings);
		


	}
	void saveEEPROM(){

		m_serial->WriteLine("savex");



	}
	
	System::IO::Ports::SerialPort^ m_serial;

};
#endif
#endif // SERIAL_H
