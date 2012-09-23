#include <Servo.h>
#include <SPI.h>
#include <Ethernet.h>

// Here we define a maximum framelength to 64 bytes. Default is 256.
#define MAX_FRAME_LENGTH 64

#include <WebSocket.h>

byte mac[] = { 0x52, 0x4F, 0x43, 0x4B, 0x45, 0x54 };
byte ip[] = { 192, 168, 1 , 77 };

// Create a Websocket server
WebSocket wsServer;

Servo myservo;

void onConnect(WebSocket &socket) {
  Serial.println("onConnect called");
}


// You must have at least one function with the following signature.
// It will be called by the server when a data frame is received.
void onData(WebSocket &socket, char* dataString, byte frameLength) {
  
  /*Serial.print("Got data: ");
  Serial.write((unsigned char*)dataString, frameLength);
  Serial.println();*/

  int val1 = (dataString[0] - 48) * 100;
  int val2 = (dataString[1] - 48) * 10;
  int val3 = dataString[2] - 48;
  
  int pwmVal = val1 + val2 + val3;
  
  myservo.write(constrain(pwmVal, 0, 180));
  
  // Just echo back data for fun.
  //socket.send(dataString, strlen(dataString));
}

void onDisconnect(WebSocket &socket) {
  Serial.println("onDisconnect called");
}

void setup() {
  
  myservo.attach(9);
   
  Serial.begin(57600);
  Ethernet.begin(mac, ip);
  
  wsServer.registerConnectCallback(&onConnect);
  wsServer.registerDataCallback(&onData);
  wsServer.registerDisconnectCallback(&onDisconnect);  
  wsServer.begin();
  
  delay(100); // Give Ethernet time to get ready
}

void loop() {
  // Should be called for each loop.
  wsServer.listen();
  
  // Do other stuff here, but don't hang or cause long delays.
  //delay(100);
  //if (wsServer.isConnected()) {
    //wsServer.send("abc123", 6);
  //}
}
