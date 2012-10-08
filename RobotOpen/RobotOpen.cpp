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
static byte ip[]  = { 10, 0, 0, 22 };
#define WEBSERVER_PORT 80

static int _total_joysticks = 0;
static char _joy1[18];
static char _joy2[18];
static char _joy3[18];
static char _joy4[18];

// Pointers to loop callbacks
static LoopCallback *whileEnabled;
static LoopCallback *whileDisabled;
static LoopCallback *whileTimedTasks;

// Hold DS data
static boolean _dashboardPacketQueued = false;
static char _outgoingPacket[255];      // Data to publish to DS is stored into this array
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



void onConnect(WebSocket &socket) {
    _lastPacket = millis();
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

      _total_joysticks = (int)(frameLength/18);

      for (i = 0; i < frameLength; i++) {
        if (i >= 1 && i < 19) {
            // 1st joystick
            _joy1[i-1] = dataString[i];
        }
        else if (i >= 19 && i < 37) {
            // 2nd joystick
            _joy1[i-19] = dataString[i];
        }
        else if (i >= 37 && i < 55) {
            // 3rd joystick
            _joy1[i-37] = dataString[i];
        }
        else if (i >= 55 && i < 73) {
            // 4th joystick
            _joy1[i-55] = dataString[i];
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

void onDisconnect(WebSocket &socket) {
    _enabled = false;
}

void RobotOpenClass::begin(LoopCallback *enabledCallback, LoopCallback *disabledCallback, LoopCallback *timedtasksCallback) {
    // Setup callbacks
    whileEnabled = enabledCallback;
    whileDisabled = disabledCallback;
    whileTimedTasks = timedtasksCallback;

    // Start Ethernet, UDP, and Serial
    Ethernet.begin(mac,ip);
    
    wsServer.registerConnectCallback(&onConnect);
    wsServer.registerDataCallback(&onData);
    wsServer.registerDisconnectCallback(&onDisconnect);  
    wsServer.begin();

    // fire up the webserver
    server.begin();

    // setup serial for debugging
    Serial.begin(115200);

    // setup packets
    _outgoingPacket[0] = 'd';

    delay(250); // Give Ethernet time to get ready
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
    if ((millis() - _lastPacket) > 200) {  // Disable the robot, drop the connection
        _enabled = false;
        if (wsServer.isConnected()) {
          wsServer.disconnectStream();
        }
	  }

    // Run user provided loops
    if (_enabled && whileEnabled)
        whileEnabled();
    if (!_enabled && whileDisabled)
        whileDisabled();
    if (whileTimedTasks)
        whileTimedTasks();

    // ensure we only accept values for the DS packet for one loop
    _dashboardPacketQueued = true;

    // send out status/DS packets frequently
    if (wsServer.isConnected() && (millis() - _lastXmit) > 100) {
        sendStatusPacket();
        publishDS();
        _dashboardPacketQueued = false;
        _lastXmit = millis();
    }
}

void RobotOpenClass::log(String data) {
    int dataLength = data.length();
    char logData[dataLength];

    for (int i=0; i < dataLength; i++) {
        logData[i] = data[i];
    }

    wsServer.sendText(logData, dataLength);
}

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

    wsServer.sendBinary(sPacket, 6);
}

boolean RobotOpenClass::publish(String id, boolean val) {
    if (_outgoingPacketSize+3+id.length() <= 255 && !_dashboardPacketQueued) {
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
    if (_outgoingPacketSize+3+id.length() <= 255 && !_dashboardPacketQueued) {
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
    if (_outgoingPacketSize+4+id.length() <= 255 && !_dashboardPacketQueued) {
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
    if (_outgoingPacketSize+6+id.length() <= 255 && !_dashboardPacketQueued) {
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
    if (_outgoingPacketSize+6+id.length() <= 255 && !_dashboardPacketQueued) {
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

void RobotOpenClass::publishDS() {
    wsServer.sendBinary(_outgoingPacket, _outgoingPacketSize);
    _outgoingPacketSize = 1;
}

boolean RobotOpenClass::enabled() {
    return _enabled;
}

int RobotOpenClass::numJoysticks() {
    return _total_joysticks;
}