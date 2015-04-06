//Writes a 16 bit uint to EEPROM
void EEPROMWriteUint16(int p_address, int p_value)
{
     byte lowByte = ((p_value >> 0) & 0xFF); // everything above the first eight bits is set to zero
     byte highByte = ((p_value >> 8) & 0xFF);

     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
}

// Reads a 16 bit uint from EEPROM
unsigned int EEPROMReadUint16(int p_address)
{
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}


// TODO: implement below
//Writes a 16 bit signed int to EEPROM
void EEPROMWriteInt16(int p_address, int p_value)
{
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);

     EEPROM.write(p_address, lowByte);
     EEPROM.write(p_address + 1, highByte);
}

// Reads a 16 bit signed int from EEPROM
unsigned int EEPROMReadInt16(int p_address)
{
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
}