#include "RobotOpen.h"
#include <EEPROM.h>




/* Constructor */
ROParameter::ROParameter(String _label, char _type, uint8_t _location)
{
	label = _label;
	type = _type;
	location = _location;	   // Allocate space for up to 4 bytes of data
	RobotOpen.addParameter(this);  // Register parameter with main RobotOpen class
}

boolean ROParameter::getBool() {
	return (EEPROM.read(location * 4) > 0);
}

char ROParameter::getChar() {
	return (char)EEPROM.read(location * 4);
}

int ROParameter::getInt() {
	byte loByte = EEPROM.read(location * 4);
  byte hiByte = EEPROM.read((location * 4) + 1);

  return ((loByte << 0) & 0xFF) + ((hiByte << 8) & 0xFF00);
}

long ROParameter::getLong() {
	byte b1 = EEPROM.read(location * 4);
  byte b2 = EEPROM.read((location * 4) + 1);
  byte b3 = EEPROM.read((location * 4) + 2);
  byte b4 = EEPROM.read((location * 4) + 3);

  return ((b1 << 0) & 0xFF) + ((b2 << 8) & 0xFF00) + ((b3 << 16) & 0xFF0000) + ((b4 << 24) & 0xFF000000);
}

float ROParameter::getFloat() {
	// thanks to http://www.elcojacobs.com/storing-settings-between-restarts-in-eeprom-on-arduino/
	union u_tag {
    byte b[4];
    float fval;
  } u;

  u.b[0] = EEPROM.read(location * 4);
  u.b[1] = EEPROM.read((location * 4) + 1);
  u.b[2] = EEPROM.read((location * 4) + 2);
  u.b[3] = EEPROM.read((location * 4) + 3);

  return u.fval;
}