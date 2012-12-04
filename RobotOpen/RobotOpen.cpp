/*
  RobotOpen.cpp - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#include "Arduino.h"
#include <SPI.h>
#include <SD.h>
#include <Ethernet.h>
#include <EthernetUdp.h>
#include <avr/pgmspace.h>
#include <avr/wdt.h>
#include "RobotOpen.h"

/* Library Config */
#define PROTOCOL_VERSION 0x03
#define FIRMWARE_VERSION 0x01
#define DEVICE_ID 0xFE

// Port config (UDP & WEB)
#define PORT 22211
#define WEBSERVER_PORT 80

// How often to push data to the SD card
#define LOGGING_INTERVAL_MS 250

// The interval for timed tasks to run
#define TIMED_TASK_INTERVAL_MS 50

// Set the MAC address and static IP for the TCP/IP stack
static byte mac[] = { 0xD4, 0x40, 0x39, 0xFB, 0xE0, 0x33 };
static byte ip[]  = { 10, 0, 0, 22 };

// joystick data
static int _total_joysticks = 0;
static char _joy1[18];
static char _joy2[18];
static char _joy3[18];
static char _joy4[18];

// SPI CS
const int chipSelect = 4;

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
static unsigned long _lastPacket = 0;       // Keeps track of the last time (ms) we received data
static unsigned long _lastLog = 0;          // Keeps track of the last time we wrote to the log
static unsigned long _lastTimedLoop = 0;    // Keeps track of the last time the timed loop ran

// Webserver instance
EthernetServer server(WEBSERVER_PORT);


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
static unsigned char _packetBuffer[UDP_TX_PACKET_MAX_SIZE];
static unsigned int _packetBufferSize = 0;
static IPAddress _remoteIp;                     // holds received packet's originating IP
static unsigned int _remotePort = 0;            // holds received packet's originating port


// Class constructor
RobotOpenClass RobotOpen;

// A UDP instance to let us send and receive packets over UDP
EthernetUDP Udp;

// File on SD card to log to
File logFile;




void RobotOpenClass::begin(LoopCallback *enabledCallback, LoopCallback *disabledCallback, LoopCallback *timedtasksCallback) {
    // Setup callbacks
    whileEnabled = enabledCallback;
    whileDisabled = disabledCallback;
    whileTimedTasks = timedtasksCallback;

    // Start Ethernet, UDP, and Serial
    Ethernet.begin(mac,ip);
    Udp.begin(PORT);

    // fire up the webserver
    server.begin();

    // setup serial for debugging
    Serial.begin(115200);

    // output on SPI SS
    pinMode(53, OUTPUT);

    // enable logging to SD
    if (!SD.begin(chipSelect)) {
        Serial.println("Card failed, or not present");
    }

    // status LED config
    pinMode(73, OUTPUT);
    pinMode(74, OUTPUT);
    pinMode(75, OUTPUT);

    digitalWrite(73, LOW);
    digitalWrite(74, LOW);
    digitalWrite(75, LOW);

    // setup DS packet
    _outgoingPacket[0] = 'd';

    delay(250); // Give Ethernet time to get ready

    // watchdog go!
    wdt_enable(WDTO_250MS);
}

void RobotOpenClass::syncDS() {
    // feed watchdog
    wdt_reset();

    // listen for incoming clients
    /*EthernetClient client = server.available();
    if (client) {
        // an http request ends with a blank line
        boolean currentLineIsBlank = true;
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
            if (c == '\n' && currentLineIsBlank) {
              // send a standard http response header
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connnection: close");
              client.println();
              client.println("<!DOCTYPE HTML><html><h2>RobotOpen Controller</h2></html>");
              break;
            }
            if (c == '\n') {
              // you're starting a new line
              currentLineIsBlank = true;
            } 
            else if (c != '\r') {
              // you've gotten a character on the current line
              currentLineIsBlank = false;
            }
          }
        }

        client.stop();
    }*/

    // status LED
    if (_enabled == true) {
        digitalWrite(73, HIGH);
        digitalWrite(74, LOW);
        digitalWrite(75, LOW);
    }
    else {
        digitalWrite(73, LOW);
        digitalWrite(74, LOW);
        digitalWrite(75, HIGH);
    }
  
    // detect disconnect
    if ((millis() - _lastPacket) > 200) {  // Disable the robot, drop the connection
        _enabled = false;
        digitalWrite(73, LOW);
        digitalWrite(74, HIGH);
        digitalWrite(75, LOW);
	}

    // Process any data sitting in the buffer
    handleData();

    // Run user provided loops
    if (_enabled && whileEnabled)
        whileEnabled();
    if (!_enabled && whileDisabled)
        whileDisabled();

    // run timed tasks
    if ((millis() - _lastTimedLoop) > TIMED_TASK_INTERVAL_MS) { 
        if (whileTimedTasks)
            whileTimedTasks();
        _lastTimedLoop = millis();
    }

    // ensure we only accept values for the DS packet for one debug loop and that data was actually published
    if (_outgoingPacketSize > 1)
        _dashboardPacketQueued = true;

    // log data to SD card
    if ((millis() - _lastLog) > LOGGING_INTERVAL_MS) { 
        logToSD();
        _lastLog = millis();
    }
}

void RobotOpenClass::log(String data) {
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

void RobotOpenClass::logToSD() {
    logFile = SD.open("datalog.txt", FILE_WRITE);
    if (logFile) {
        logFile.print(millis());
        logFile.print("ms -- System Alive");
        if (_enabled)
            logFile.println(" [ENABLED]");
        else
            logFile.println(" [DISABLED]");
        logFile.close();
  }
}

unsigned int RobotOpenClass::calc_crc16(unsigned char *buf, unsigned short len) {
    unsigned short crc = 0;
    unsigned short i;
    for (i=0; i<len; i++)
        crc = ((crc >> 8) & 0xff) ^ pgm_read_word_near(crctab + (unsigned int)((crc ^ *buf++) & 0xff));
    return (crc);
}

void RobotOpenClass::sendStatusPacket() {
    char sPacket[6];
    sPacket[0] = 's';               // status packet
    sPacket[1] = PROTOCOL_VERSION;  // robotopen protocol version

    if (_enabled)                   // robot enable state
        sPacket[2] = 0xFF;
    else
        sPacket[2] = 0xFE;

    sPacket[3] = FIRMWARE_VERSION;  // User configured firmware version
    sPacket[4] = DEVICE_ID;         // Device ID of the hardware this is running on

    unsigned int uptime = (millis()/1000/60);
    if (uptime > 255)
        uptime = 255;

    sPacket[5] = (unsigned char)(uptime & 0xFF); // uptime in minutes (maxes out at 255)

    if (_remotePort != 0) {
        Udp.beginPacket(_remoteIp, _remotePort);
        Udp.write((uint8_t *)sPacket, 6);
        Udp.endPacket();
    }
}

boolean RobotOpenClass::publish(String id, boolean val) {
    if (_outgoingPacketSize+3+id.length() <= 512 && !_dashboardPacketQueued) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (3+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'b'; // type
        if (val == 0)
            _outgoingPacket[_outgoingPacketSize++] = 0;  // value
        else
            _outgoingPacket[_outgoingPacketSize++] = 0xFF;
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

boolean RobotOpenClass::publish(String id, char val) {
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
    if (_outgoingPacketSize+6+id.length() <= 512 && !_dashboardPacketQueued) {
        long conVal = (long)val;
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (6+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'f'; // type
        _outgoingPacket[_outgoingPacketSize++] = (conVal >> 24) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = (conVal >> 16) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = (conVal >> 8) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = conVal & 0xFF;  // value
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
        Udp.read(_packetBuffer, UDP_TX_PACKET_MAX_SIZE);
        parsePacket();  // Data is all set, time to parse through it
    }
}

void RobotOpenClass::parsePacket() {
    // calculate crc16
    unsigned int crc16_recv = (_packetBuffer[_packetBufferSize - 2] << 8) | _packetBuffer[_packetBufferSize - 1];
    
    if (calc_crc16(_packetBuffer, _packetBufferSize - 2) == crc16_recv) {
        // control packet is 'c' + joystick data + crc16
        int frameLength = (_packetBufferSize - 3);

        // VALID PACKET
        switch (_packetBuffer[0]) {
            case 'h': // heartbeat
              _enabled = false;
              _lastPacket = millis();
              break;

            case 'c': // control packet
              _enabled = true;
              _lastPacket = millis();
              _total_joysticks = (int)(frameLength/18);
              int i;

              for (i = 0; i < frameLength; i++) {
                if (i >= 0 && i < 18) {
                    // 1st joystick
                    _joy1[i] = _packetBuffer[i+1];
                }
                else if (i >= 18 && i < 36) {
                    // 2nd joystick
                    _joy2[i-18] = _packetBuffer[i+19];
                }
                else if (i >= 36 && i < 54) {
                    // 3rd joystick
                    _joy3[i-36] = _packetBuffer[i+37];
                }
                else if (i >= 54 && i < 72) {
                    // 4th joystick
                    _joy4[i-54] = _packetBuffer[i+55];
                }
                else {
                    break;
                }      
              }
              break;

            default:
              // ignore the packet
              break;
        }
    }

    sendStatusPacket();
    if (_dashboardPacketQueued)
        publishDS();
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

boolean RobotOpenClass::enabled() {
    return _enabled;
}

int RobotOpenClass::numJoysticks() {
    return _total_joysticks;
}