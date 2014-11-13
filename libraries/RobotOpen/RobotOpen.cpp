/*
  RobotOpen.cpp - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#include "Arduino.h"
#include <SPI.h>
#include <Servo.h>
#include <SD.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <EEPROM.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "RobotOpen.h"


// Port config (UDP)
#define PORT 22211

// How often to push data to the SD card
#define LOGGING_INTERVAL_MS 1000

// The interval for timed tasks to run
#define TIMED_TASK_INTERVAL_MS 100

// The interval for publishing DS data
#define DS_INTERVAL_MS 100

// The number of milliseconds between SD card writes (faster writes will be dropped)
#define MAX_LOGGING_TIMEOUT 250

// Set the MAC address and static IP for the TCP/IP stack
static byte mac[] = { 0xD4, 0x40, 0x39, 0xFB, 0xE0, 0x33 };
static IPAddress ip(10, 0, 0, 22);

// joystick data
static int _total_joysticks = 0;
static char _joy1[24];
static char _joy2[24];
static char _joy3[24];
static char _joy4[24];

// SPI CS
const int chipSelect = 9;

// Pointers to loop callbacks
static LoopCallback *whileEnabled;
static LoopCallback *whileDisabled;
static LoopCallback *whileTimedTasks;

// Hold DS data
static boolean _dashboardPacketQueued = false;
static char _outgoingPacket[512];      // Data to publish to DS is stored into this array
static unsigned int _outgoingPacketSize = 1;

// Robot specific stuff
static boolean _enabled = false;            // Tells us if the robot is enabled or disabled
static boolean _enable_lock = false;
static unsigned long _lastPacket = 0;       // Keeps track of the last time (ms) we received data
static unsigned long _lastTimedLoop = 0;    // Keeps track of the last time the timed loop ran
static unsigned long _lastDSLoop = 0;       // Keeps track of the last time we published DS data
static unsigned long _lastSDWrite = 0;      // Keeps track of the last time we wrote to the SD card

// milliseconds without receiving DS packet before we consider ourselves 'disconnected'
static int connection_timeout = 200;

// Outputs that must be controlled via enable state
static Servo pwmChannels[16];
static boolean digitalOutputChannels[22] = 
{
    false,false,false,false,false,false,
    false,false,false,false,false,false,
    false,false,false,false,false,false,
    false,false,false,false
};

static ROParameter* params[100];
static unsigned char paramsLength = 0;
static boolean firstEnableLoop = true;

static boolean acceptingDebugData = false;



/* CRC lookup table */
PROGMEM static short crctab[] =
{
    0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
    0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
    0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
    0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
    0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
    0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
    0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
    0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
    0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
    0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
    0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
    0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
    0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
    0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
    0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
    0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
    0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
    0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
    0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
    0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
    0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
    0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
    0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
    0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
    0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
    0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
    0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
    0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
    0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
    0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
    0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
    0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};


// Networking support
static unsigned char _packetBuffer[512];
static unsigned int _packetBufferSize = 0;
static IPAddress _remoteIp;                     // holds received packet's originating IP
static unsigned int _remotePort = 0;            // holds received packet's originating port

// Class constructor
RobotOpenClass RobotOpen;

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// File on SD card to log to
File logFile;


void RobotOpenClass::setIP(IPAddress newIP) {
    ip = newIP;
}

void RobotOpenClass::setTimeout(int new_timeout) {
    connection_timeout = new_timeout;
}


void RobotOpenClass::begin(LoopCallback *enabledCallback, LoopCallback *disabledCallback, LoopCallback *timedtasksCallback) {
    // Setup callbacks
    whileEnabled = enabledCallback;
    whileDisabled = disabledCallback;
    whileTimedTasks = timedtasksCallback;

    // Start Ethernet, UDP, and Serial
    Ethernet.begin(mac,ip);
    Udp.begin(PORT);

    // setup serial for debugging
    Serial.begin(115200);

    // Solenoid outputs
    for (int i = 0; i < 8; i++) {
        pinMode(39+i, OUTPUT);
        digitalWrite(39+i, LOW);
    }

    // output on SPI SS
    pinMode(53, OUTPUT);

    // enable logging to SD
    if (!SD.begin(chipSelect)) {
        //Serial.println("Card failed, or not present");
    }

    // status LED config
    pinMode(4, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);

    // setup DS packet
    _outgoingPacket[0] = 'd';

    delay(250); // Give Ethernet time to get ready

    // watchdog go!
    wdt_enable(WDTO_250MS);
}

// This gets called once when the robot becomes disconnected or disabled
void RobotOpenClass::onDisable() {
    // PWM outputs
    for (int i = 0; i < 16; i++) {
        pwmChannels[i].detach();
    }
    // Solenoid outputs
    for (int i = 0; i < 8; i++) {
        digitalWrite(39+i, LOW);
    }
    // Digital outputs
    for (int i = 0; i < 22; i++) {
        if (digitalOutputChannels[i] == true) {
            if (i < 3)
                digitalWrite(47+i, LOW);
            else
                digitalWrite(51+i, LOW);
        }
    }
}

void RobotOpenClass::detachPWM(byte pwmChannel) {
    if (pwmChannel >= 0 && pwmChannel < 16) {
        pwmChannels[pwmChannel].detach();
    }
}

void RobotOpenClass::attachPWM(byte pwmChannel) {
    if (pwmChannel >= 0 && pwmChannel < 16) {
        pwmChannels[pwmChannel].attach(23+pwmChannel);
        pwmChannels[pwmChannel].write(90);
    }
}

void RobotOpenClass::syncDS() {
    // feed watchdog
    wdt_reset();
  
    // detect disconnect
    if ((millis() - _lastPacket) > connection_timeout && !_enable_lock) {  // Disable the robot, drop the connection
        _enabled = false;
        // NO CONNECTION -- blue LED
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, HIGH);
        if (!firstEnableLoop) {
            onDisable();
            firstEnableLoop = true;
        }
	}
    else if (_enabled == true || _enable_lock) {
        // ENABLED -- green LED
        digitalWrite(4, LOW);
        digitalWrite(5, HIGH);
        digitalWrite(6, LOW);
        // reattach servos
        if (firstEnableLoop) {
            for(int i = 0; i < 16; i++) {
                pwmChannels[i].attach(23+i);
                pwmChannels[i].write(90);
            }
            firstEnableLoop = false;
        }
    }
    else {
        // DISABLED -- red LED
        digitalWrite(4, HIGH);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
        if (!firstEnableLoop) {
            onDisable();
            firstEnableLoop = true;
        }
    }

    // Process any data sitting in the buffer
    handleData();

    // Run user provided loops
    if (whileTimedTasks)
        whileTimedTasks();
    if (_enabled && whileEnabled)
        whileEnabled();
    if (!_enabled && whileDisabled)
        whileDisabled();

    // run timed tasks
    if ((millis() - _lastTimedLoop) > TIMED_TASK_INTERVAL_MS) {
        acceptingDebugData = true;
        _lastTimedLoop = millis();
    } else {
        acceptingDebugData = false;
    }

    // ensure we only accept values for the DS packet for one debug loop and that data was actually published
    if (_outgoingPacketSize > 1)
        _dashboardPacketQueued = true;

    // publish DS data
    if ((millis() - _lastDSLoop) > DS_INTERVAL_MS) { 
        if (_outgoingPacketSize == 1 || _dashboardPacketQueued)
            publishDS();
        _lastDSLoop = millis();
    }
}

void RobotOpenClass::log(String data) {
    if (acceptingDebugData) {
        int dataLength = data.length();
        char logData[dataLength+1];

        logData[0] = 'p';

        for (int i=0; i < dataLength; i++) {
            logData[i+1] = data[i];
        }

        if (_remotePort != 0) {
            Udp.beginPacket(_remoteIp, _remotePort);
            Udp.write((uint8_t *)logData, dataLength+1);
            Udp.endPacket();
        }
    }
}

void RobotOpenClass::logToSD(String data) {
    if ((millis() - _lastSDWrite) > MAX_LOGGING_TIMEOUT) {
        logFile = SD.open("robolog.txt", FILE_WRITE);
        if (logFile) {
            logFile.println(data);
            logFile.close();
        }
        // update last write time
        _lastSDWrite = millis();
    }
}

unsigned int RobotOpenClass::calc_crc16(unsigned char *buf, unsigned short len) {
    unsigned short crc = 0;
    unsigned short i;
    for (i=0; i<len; i++)
        crc = ((crc >> 8) & 0xff) ^ pgm_read_word_near(crctab + (unsigned int)((crc ^ *buf++) & 0xff));
    return (crc);
}

boolean RobotOpenClass::publish(String id, unsigned char val) {
    if (_outgoingPacketSize+3+id.length() <= 512 && !_dashboardPacketQueued) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (3+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'c'; // type
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & val;  // value
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

boolean RobotOpenClass::publish(String id, int val) {
    if (_outgoingPacketSize+4+id.length() <= 512 && !_dashboardPacketQueued) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (4+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'i'; // type
        _outgoingPacket[_outgoingPacketSize++] = (val >> 8) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = val & 0xFF;  // value
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

boolean RobotOpenClass::publish(String id, long val) {
    if (_outgoingPacketSize+6+id.length() <= 512 && !_dashboardPacketQueued) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (6+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'l'; // type
        _outgoingPacket[_outgoingPacketSize++] = (val >> 24) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = (val >> 16) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = (val >> 8) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = val & 0xFF;  // value
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

boolean RobotOpenClass::publish(String id, float val) {
    union u_tag {
        byte b[4];
        float fval;
    } u;
    u.fval = val;

    if (_outgoingPacketSize+6+id.length() <= 512 && !_dashboardPacketQueued) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (6+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'f'; // type
        _outgoingPacket[_outgoingPacketSize++] = u.b[3];  // value
        _outgoingPacket[_outgoingPacketSize++] = u.b[2];  // value
        _outgoingPacket[_outgoingPacketSize++] = u.b[1];  // value
        _outgoingPacket[_outgoingPacketSize++] = u.b[0];  // value
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

char* RobotOpenClass::getJoystick(char index) {
    if (index == 1 && _total_joysticks > 0)
        return _joy1;
    else if (index == 2 && _total_joysticks > 1)
        return _joy2;
    else if (index == 3 && _total_joysticks > 2)
        return _joy3;
    else if (index == 4 && _total_joysticks > 3)
        return _joy4;
    else
        return 0;
}

// This function's purpose is to receive data and prepare it for parsing
void RobotOpenClass::handleData() {
    _packetBufferSize = Udp.parsePacket();
    
    // If there's data, read the packet in
    if (_packetBufferSize > 0) {
        _remotePort = Udp.remotePort();
        _remoteIp = Udp.remoteIP();
        Udp.read(_packetBuffer, 100);
        parsePacket();  // Data is all set, time to parse through it
    }
}

void RobotOpenClass::parsePacket() {
    // calculate crc16
    unsigned int crc16_recv = (_packetBuffer[_packetBufferSize - 2] << 8) | _packetBuffer[_packetBufferSize - 1];
    
    if (calc_crc16(_packetBuffer, _packetBufferSize - 2) == crc16_recv) {
        // control packet is 'c' + joystick data + crc16
        int frameLength = (_packetBufferSize - 3);
        int numParameters;
        int paramCount = 0;

        // VALID PACKET
        switch (_packetBuffer[0]) {
            case 'h': // heartbeat
              _enabled = false;
              _lastPacket = millis();
              break;

            case 'l': // enable lock
              _enable_lock = true;
              _lastPacket = millis();
              break;

            case 'u': // enable unlock
              _enable_lock = false;
              _lastPacket = millis();
              break;

            case 'c': // control packet
              _enabled = true;
              _lastPacket = millis();
              _total_joysticks = (int)(frameLength/24);
              int i;

              for (i = 0; i < frameLength; i++) {
                if (i >= 0 && i < 24) {
                    // 1st joystick
                    _joy1[i] = _packetBuffer[i+1];
                }
                else if (i >= 24 && i < 48) {
                    // 2nd joystick
                    _joy2[i-24] = _packetBuffer[i+1];
                }
                else if (i >= 48 && i < 72) {
                    // 3rd joystick
                    _joy3[i-48] = _packetBuffer[i+1];
                }
                else if (i >= 72 && i < 96) {
                    // 4th joystick
                    _joy4[i-72] = _packetBuffer[i+1];
                }
                else {
                    break;
                }      
              }
              break;

            case 's': // set parameter packet
              numParameters = frameLength / 5;
              for (paramCount = 0; paramCount < numParameters; paramCount++) {
                writeParameter((uint8_t)_packetBuffer[(paramCount*5)+1], ((paramCount*5)+2));
              }
              break;

            case 'g': // get parameters packet
              sendParameters();
              break;

            default:
              // ignore the packet
              break;
        }
    }
}

void RobotOpenClass::publishDS() {
    if (_remotePort != 0) {
        Udp.beginPacket(_remoteIp, _remotePort);
        Udp.write((uint8_t *)_outgoingPacket, _outgoingPacketSize);
        Udp.endPacket();
    }

    _outgoingPacketSize = 1;
    _dashboardPacketQueued = false;
}

void RobotOpenClass::writePWM(byte channel, byte pwmVal) {
    if (_enabled && channel < 16) {
        pwmChannels[channel].write((int)map(pwmVal, 0, 255, 544, 2400));
    }
}

void RobotOpenClass::writeSolenoid(byte channel, uint8_t state) {
    if (channel < 8) {
        digitalWrite(39+channel, state);
    }
}

void RobotOpenClass::writeDigital(byte channel, uint8_t state) {
    if (channel < 22 && digitalOutputChannels[channel] == true) {
        if (channel < 3)
            digitalWrite(47+channel, state);
        else
            digitalWrite(51+channel, state);
    }
}

void RobotOpenClass::makeOutput(byte channel) {
    if (channel < 22) {
        if (channel < 3) {
            pinMode(47+channel, OUTPUT);
            digitalWrite(47+channel, LOW);
        }
        else {
            pinMode(51+channel, OUTPUT);
            digitalWrite(51+channel, LOW);
        }
        digitalOutputChannels[channel] = true;
    }
}

void RobotOpenClass::makeInput(byte channel) {
    if (channel < 22) {
        if (channel < 3)
            pinMode(47+channel, INPUT);
        else
            pinMode(51+channel, INPUT);
        digitalOutputChannels[channel] = false;
    }
}

void RobotOpenClass::setPullup(byte channel, boolean pullUp) {
    if (channel < 22 && digitalOutputChannels[channel] == false) {
        uint8_t state = LOW;
        if (pullUp)
            state = HIGH;
        if (channel < 3)
            digitalWrite(47+channel, state);
        else
            digitalWrite(51+channel, state);
    }
}

void RobotOpenClass::addParameter(ROParameter* param) {
    params[paramsLength++] = param;
}

void RobotOpenClass::writeParameter(uint8_t location, unsigned int firstByte) {
    if (!_enabled) {
        EEPROM.write((location * 4), _packetBuffer[firstByte]);
        EEPROM.write((location * 4) + 1, _packetBuffer[firstByte+1]);
        EEPROM.write((location * 4) + 2, _packetBuffer[firstByte+2]);
        EEPROM.write((location * 4) + 3, _packetBuffer[firstByte+3]);
    }
}

void RobotOpenClass::sendParameters() {
    _outgoingPacket[0] = 'r';
    _outgoingPacketSize = 1;

    for (int i = 0; i < paramsLength; i++) {
        ROParameter prm = *params[i];

        if (_outgoingPacketSize+7+prm.label.length() <= 512) {
            _outgoingPacket[_outgoingPacketSize++] = 0xFF & (7+prm.label.length());         // length
            _outgoingPacket[_outgoingPacketSize++] = 0xFF & (prm.location);                 // address (0-99)
            _outgoingPacket[_outgoingPacketSize++] = prm.type;                              // type
            _outgoingPacket[_outgoingPacketSize++] = EEPROM.read(prm.location * 4);         // val1
            _outgoingPacket[_outgoingPacketSize++] = EEPROM.read((prm.location * 4) + 1);   // val2
            _outgoingPacket[_outgoingPacketSize++] = EEPROM.read((prm.location * 4) + 2);   // val3
            _outgoingPacket[_outgoingPacketSize++] = EEPROM.read((prm.location * 4) + 3);   // val4
            for (int j = 0; j < prm.label.length(); j++) {
                _outgoingPacket[_outgoingPacketSize++] = prm.label[j];                      // identifier
            }
        } else {
            break;
        }
    }

    // xmit
    if (_remotePort != 0) {
        Udp.beginPacket(_remoteIp, _remotePort);
        Udp.write((uint8_t *)_outgoingPacket, _outgoingPacketSize);
        Udp.endPacket();
    }

    // reset the outgoing packet vars
    _outgoingPacketSize = 1;
    _dashboardPacketQueued = false;
    _outgoingPacket[0] = 'd';
}

boolean RobotOpenClass::enabled() {
    return _enabled;
}

void RobotOpenClass::enableLock(boolean lock) {
    _enable_lock = lock;
}

int RobotOpenClass::numJoysticks() {
    return _total_joysticks;
}