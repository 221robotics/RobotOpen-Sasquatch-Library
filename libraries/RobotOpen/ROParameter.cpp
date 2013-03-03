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
	union i_tag {
    byte b[2];
    int ival;
  } i;

  i.b[1] = EEPROM.read(location * 4);
  i.b[0] = EEPROM.read((location * 4) + 1);

  return i.ival;
}

long ROParameter::getLong() {
  union l_tag {
    byte b[4];
    long lval;
  } l;

	l.b[3] = EEPROM.read(location * 4);
  l.b[2] = EEPROM.read((location * 4) + 1);
  l.b[1] = EEPROM.read((location * 4) + 2);
  l.b[0] = EEPROM.read((location * 4) + 3);

  return l.lval;
}

float ROParameter::getFloat() {
	// thanks to http://www.elcojacobs.com/storing-settings-between-restarts-in-eeprom-on-arduino/
	union u_tag {
    byte b[4];
    float fval;
  } u;

  u.b[3] = EEPROM.read(location * 4);
  u.b[2] = EEPROM.read((location * 4) + 1);
  u.b[1] = EEPROM.read((location * 4) + 2);
  u.b[0] = EEPROM.read((location * 4) + 3);

  return u.fval;
}