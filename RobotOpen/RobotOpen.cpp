/*
  RobotOpen.cpp - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, October 16, 2011.
*/

#include "Arduino.h"
#include "RobotOpen.h"
#include <SPI.h>
#include <Ethernet.h>

//Set the MAC address and static IP for the TCP/IP stack
static byte mac[] = { 0xD4, 0x40, 0x39, 0xFB, 0xE0, 0x33 };
static byte ip[]  = { 10, 0, 0, 22 };
#define WEBSERVER_PORT 80

// Store the data here
static unsigned char _joystick[76];             // Byte array of last valid joystick packet (up to 4 controllers)
static unsigned char _outgoingPacket[256];      // Data to publish to DS is stored into this array
static unsigned char _joystickCount = 0;
static unsigned char _outgoingPacketSize = 0;

// Robot specific stuff
static boolean _enabled = false;        // Tells us if the robot is enabled or disabled
static boolean _waitingPacket = false;	// There is a driverstation packet in the queue
static unsigned long _lastPacket = 0;   // Keeps track of the last time (ms) we received data
static unsigned long _lastMillis = 0;   // Keep track of time

// Networking instances
WebSocket wsServer;
EthernetServer server(WEBSERVER_PORT);

// Class constructor
RobotOpenClass RobotOpen;


void RobotOpenClass::sendStatusPacket() {
    // TODO: send the packet
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

      // TODO: parse out control data
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

    delay(100); // Give Ethernet time to get ready
}

void RobotOpenClass::pollDS() {
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

    // send out status packets frequently
    if (wsServer.isConnected() && (millis() - _lastMillis) > 500) {
      sendStatusPacket();
      _lastMillis = millis();
    }
}

void RobotOpenClass::outgoingDS() {
    _waitingPacket = true;
}

void RobotOpenClass::publishDS() {
    // TODO: publish DS
}

boolean RobotOpenClass::enabled() {
    return _enabled;
}

USBJoystick::USBJoystick(unsigned char bID)
{
  _bundleID = bID;
}

int USBJoystick::getIndex(int index)
{
    return 0;
}

unsigned int USBJoystick::makePWM(int index, char mode)
{
	return 127;
}

boolean USBJoystick::getBtn(int index, char mode) {
    return LOW;
}

boolean USBJoystick::getDpad(unsigned char compare, char mode) {
    return 0x00;
}