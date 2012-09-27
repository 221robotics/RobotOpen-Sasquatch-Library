/*
  RobotOpen.cpp - Library implementation of the RobotOpen Hardware found at www.RobotOpen.biz
  Created by Eric Barch, October 16, 2011.
*/

#include "Arduino.h"
#include "RobotOpen.h"
#include <SPI.h>
#include <Ethernet.h>

  // Here we define a maximum websocket framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 256

//Set the MAC address and static IP for the TCP/IP stack
static byte mac[] = { 0xD4, 0x40, 0x39, 0xFB, 0xE0, 0x33 };
static byte ip[]  = { 10, 0, 0, 22 };
#define WEBSERVER_PORT 80

// Store the data here
static unsigned char _joystick[256];            // Byte array of last valid joystick packet
static unsigned char _outgoingPacket[256];      // Data to publish to DS is stored into this array
static unsigned char _joystickPacketSize = 0;
static unsigned char _outgoingPacketSize = 0;

// Robot specific stuff
static boolean _enabled = false;      // Tells us if the robot is enabled or disabled
static boolean _waitingPacket = false;	// There is a driverstation packet in the queue
static unsigned long _lastUpdate = 0;  // Keeps track of the last time (ms) we received data

static unsigned long _lastMillis = 0;

// General vars
static IPAddress _remoteIp;          // holds received packet's originating IP
static unsigned int _remotePort = 0; // holds received packet's originating port

// Networking instances
WebSocket wsServer;
EthernetServer server(WEBSERVER_PORT);


// Class constructor
RobotOpenClass RobotOpen;


void onConnect(WebSocket &socket) {
  Serial.println("onConnect called");
}

void onData(WebSocket &socket, char* dataString, byte frameLength) {
  Serial.println("onData called");
}

void onDisconnect(WebSocket &socket) {
  Serial.println("onDisconnect called");
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
            // if you've gotten to the end of the line (received a newline
            // character) and the line is blank, the http request has ended,
            // so you can send a reply
            if (c == '\n' && currentLineIsBlank) {
              // send a standard http response header
              client.println("HTTP/1.1 200 OK");
              client.println("Content-Type: text/html");
              client.println("Connnection: close");
              client.println();
              client.println("<!DOCTYPE HTML>");
              client.println("<script language=\"javascript\" type=\"text/javascript\">");
              client.println("function writeToScreen(message) {");
              client.println("var pre = document.createElement(\"p\");");
              client.println("pre.style.wordWrap = \"break-word\";");
              client.println("pre.innerHTML = message;");
              client.println("document.getElementById(\"output\").appendChild(pre); }");
              client.println("function socketTest() {");
              client.println("var socket = new WebSocket(\"ws://10.0.0.22:8000\");");
              client.println("socket.onmessage = function(evt) { writeToScreen('<span>'+evt.data+'</span>'); }}");
              client.println("window.addEventListener(\"load\", socketTest, false);</script>");
              client.println("<h2>WebSocket Test</h2>  <div id=\"output\"></div>  </html>");
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

    // Process any data sitting in the buffer
    // handleData();
  
    //Only allow robot to be enabled if we've received data in the last 250ms and robot is set to enabled
    if (((millis() - _lastUpdate) <= 250) && (millis() > 500)) {  //Robot is disabled for first 500ms of runtime
        _enabled = true;
	}
    else {
        _enabled = false;
    }

    if (wsServer.isConnected()) {
        if (millis() - _lastMillis > 100) {
            wsServer.send("hello!", 6);
            _lastMillis = millis();
        }
    }
}

void RobotOpenClass::outgoingDS() {
    _waitingPacket = true;
}

void RobotOpenClass::publishDS() {
    // publish DS
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