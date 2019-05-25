#include "RobotOpenSQ.h"
#include <EEPROM.h>




/* Constructor */
ROBoolParameter::ROBoolParameter(String _label, uint8_t _location)
{
	label = _label;
	type = BOOL;
	location = _location;	   // Allocate space for up to 4 bytes of data
	RobotOpen.addParameter((ROParameter*)this);  // Register parameter with main RobotOpen class
}

// getter
boolean ROBoolParameter::get() {
	return (EEPROM.read(location * 4) > 0);
}



/* Constructor */
ROCharParameter::ROCharParameter(String _label, uint8_t _location)
{
  label = _label;
  type = CHAR;
  location = _location;    // Allocate space for up to 4 bytes of data
  RobotOpen.addParameter((ROParameter*)this);  // Register parameter with main RobotOpen class
}

// getter
char ROCharParameter::get() {
  return (char)EEPROM.read(location * 4);
}



/* Constructor */
ROIntParameter::ROIntParameter(String _label, uint8_t _location)
{
  label = _label;
  type = INT;
  location = _location;    // Allocate space for up to 4 bytes of data
  RobotOpen.addParameter((ROParameter*)this);  // Register parameter with main RobotOpen class
}

// getter
int ROIntParameter::get() {
  union i_tag {
    byte b[2];
    int ival;
  } i;

  i.b[1] = EEPROM.read(location * 4);
  i.b[0] = EEPROM.read((location * 4) + 1);

  return i.ival;
}



/* Constructor */
ROLongParameter::ROLongParameter(String _label, uint8_t _location)
{
  label = _label;
  type = LONG;
  location = _location;    // Allocate space for up to 4 bytes of data
  RobotOpen.addParameter((ROParameter*)this);  // Register parameter with main RobotOpen class
}

// getter
long ROLongParameter::get() {
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



/* Constructor */
ROFloatParameter::ROFloatParameter(String _label, uint8_t _location)
{
  label = _label;
  type = FLOAT;
  location = _location;    // Allocate space for up to 4 bytes of data
  RobotOpen.addParameter((ROParameter*)this);  // Register parameter with main RobotOpen class
}

// getter
float ROFloatParameter::get() {
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