#include <EEPROM\EEPROM.h>

// There is 4K (4096 bytes) EEPROM storage on ATmega2560


//Writes a 16 bit int to EEPROM
void EEPROMWriteInt16(int p_address, int p_value)
{
     byte lowByte = p_value; // everything above the first eight bits is set to zero
	 byte highByte = (p_value >> 8);

     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
}

// Reads a 16 bit int from EEPROM
int EEPROMReadInt16(int p_address)
{
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);
	 return highByte << 8 | lowByte;
}

// Write byte
void EEPROMWriteByte(int p_address, byte p_value)
{
	EEPROM.write(p_address, p_value);
}

// Read byte
byte EEPROMReadByte(int p_address)
{
	return EEPROM.read(p_address);
}

void EEPROMWriteBool(int p_address, bool p_bool)
{
	if (p_bool) EEPROM.write(p_address, (byte)1);
	else EEPROM.write(p_address, (byte)0);
}

bool EEPROMReadBool(int p_address)
{
	if (EEPROM.read(p_address) == 1) return true;
	else return false;
}


