/*
  RobotOpen.cpp - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, September 27, 2012.
*/

#include "Arduino.h"
#include "RobotOpen.h"
#include <SPI.h>
#include <Ethernet.h>

/* Library Config */
#define PROTOCOL_VERSION 0x03
#define FIRMWARE_VERSION 0x01
#define DEVICE_ID 0xFE

//Set the MAC address and static IP for the TCP/IP stack
static byte mac[] = { 0xD4, 0x40, 0x39, 0xFB, 0xE0, 0x33 };
static byte ip[]  = { 192, 168, 1, 22 };
#define WEBSERVER_PORT 80

static int _total_joysticks = 0;
static char _joy1[18];
static char _joy2[18];
static char _joy3[18];
static char _joy4[18];

// Hold DS data
static char _outgoingPacket[256];      // Data to publish to DS is stored into this array
static unsigned char _outgoingPacketSize = 1;

// Robot specific stuff
static boolean _enabled = false;        // Tells us if the robot is enabled or disabled
static unsigned long _lastPacket = 0;   // Keeps track of the last time (ms) we received data
static unsigned long _lastXmit = 0;     // Keep track of last transmission

// Networking instances
WebSocket wsServer;
EthernetServer server(WEBSERVER_PORT);

// Class constructor
RobotOpenClass RobotOpen;


void RobotOpenClass::sendStatusPacket() {
    char sPacket[6];
    sPacket[0] = 's';               // status packet
    sPacket[1] = PROTOCOL_VERSION;  // robotopen protocol version

    if (_enabled)                   // robot enable state
        sPacket[2] = 0xFF;
    else
        sPacket[2] = 0x00;

    sPacket[3] = FIRMWARE_VERSION;  // User configured firmware version
    sPacket[4] = DEVICE_ID;         // Device ID of the hardware this is running on

    unsigned int uptime = (millis()/1000/60);
    if (uptime > 255)
        uptime = 255;

    sPacket[5] = (unsigned char)(uptime & 0xFF); // uptime in minutes (maxes out at 255)

    wsServer.send(sPacket, 6);
}

void onConnect(WebSocket &socket) {
  // ready to go
}

void onData(WebSocket &socket, char* dataString, byte frameLength) {
  switch (dataString[0]) {
    case 'h': // heartbeat
      _enabled = false;
      _lastPacket = millis();
      break;

    case 'c': // control packet
      _enabled = true;
      _lastPacket = millis();
      int i;

      // parse out control data
      if (frameLength > 1) {
          for (i = 0; i < 18; i++) {
              _joy1[i] = dataString[i+1];
          }
          _total_joysticks = 1;
      }
      if (frameLength > 19) {
          for (i = 0; i < 18; i++) {
              _joy2[i] = dataString[i+19];
          }
          _total_joysticks = 2;
      }
      if (frameLength > 37) {
          for (i = 0; i < 18; i++) {
              _joy3[i] = dataString[i+37];
          }
          _total_joysticks = 3;
      }
      if (frameLength > 55) {
          for (i = 0; i < 18; i++) {
              _joy4[i] = dataString[i+55];
          }
          _total_joysticks = 4;
      }
      break;

    default:
      // ignore the packet
      break;
    }
}

void onDisconnect(WebSocket &socket) {
    _enabled = false;
}

void RobotOpenClass::begin() {
    // Start Ethernet, UDP, and Serial
    Ethernet.begin(mac,ip);
    
    wsServer.registerConnectCallback(&onConnect);
    wsServer.registerDataCallback(&onData);
    wsServer.registerDisconnectCallback(&onDisconnect);  
    wsServer.begin();

    // fire up the webserver
    server.begin();

    Serial.begin(115200);	// This is used to talk to the coprocessor on the RobotOpen shield

    // setup packets
    _outgoingPacket[0] = 'd';

    delay(100); // Give Ethernet time to get ready
}

void RobotOpenClass::syncDS() {
    // listen for incoming clients
    EthernetClient client = server.available();
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
              client.println("<!DOCTYPE HTML><html><h2>Welcome to RobotOpen</h2></html>");
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
    }

    // Should be called for each loop.
    wsServer.listen();
  
    // detect disconnect
    if ((millis() > 500) && ((millis() - _lastPacket) > 200)) {  //Robot is disabled for first 500ms of runtime
        _enabled = false;
        if (wsServer.isConnected()) {
          wsServer.disconnectStream();
        }
	  }

    // send out status/DS packets frequently
    if (wsServer.isConnected() && (millis() - _lastXmit) > 100) {
      sendStatusPacket();
      publishDS();
      _lastXmit = millis();
    }
}

void RobotOpenClass::log(String data) {
    int dataLength = data.length();

    char logData[dataLength+1];
    logData[0] = 'p';
    for (int i=0; i < dataLength; i++) {
        logData[i+1] = data[i];
    }

    wsServer.send(logData, dataLength+1);
}

boolean RobotOpenClass::publishToDS(String id, boolean val) {
    if (_outgoingPacketSize+3+id.length() <= 256) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (3+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'b'; // type
        if (val == 0)
            _outgoingPacket[_outgoingPacketSize++] = 0;  // value
        else
            _outgoingPacket[_outgoingPacketSize++] = 1;
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

boolean RobotOpenClass::publishToDS(String id, char val) {
    if (_outgoingPacketSize+3+id.length() <= 256) {
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

boolean RobotOpenClass::publishToDS(String id, int val) {
    if (_outgoingPacketSize+4+id.length() <= 256) {
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

boolean RobotOpenClass::publishToDS(String id, long val) {
    if (_outgoingPacketSize+6+id.length() <= 256) {
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

boolean RobotOpenClass::publishToDS(String id, float val) {
    if (_outgoingPacketSize+6+id.length() <= 256) {
        _outgoingPacket[_outgoingPacketSize++] = 0xFF & (6+id.length());  // length
        _outgoingPacket[_outgoingPacketSize++] = 'f'; // type
        _outgoingPacket[_outgoingPacketSize++] = ((long)val >> 24) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = ((long)val >> 16) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = ((long)val >> 8) & 0xFF;  // value
        _outgoingPacket[_outgoingPacketSize++] = (long)val & 0xFF;  // value
        for (int i = 0; i < id.length(); i++) {
            _outgoingPacket[_outgoingPacketSize++] = id[i];   // identifier
        }
        return true;
    }

    return false;
}

char* getJoystick(char index) {
    if (index == 1 && _total_joysticks > 0)
        return _joy1;
    if (index == 2 && _total_joysticks > 1)
        return _joy2;
    if (index == 3 && _total_joysticks > 2)
        return _joy3;
    if (index == 4 && _total_joysticks > 3)
        return _joy4;
    else
        return 0;
}

void RobotOpenClass::publishDS() {
    wsServer.send(_outgoingPacket, _outgoingPacketSize);
    _outgoingPacketSize = 1;
}

boolean RobotOpenClass::enabled() {
    return _enabled;
}

int RobotOpenClass::numJoysticks() {
    return _total_joysticks;
}