#include <Ethernet.h>
#include <SPI.h>
#include <SD.h>

/************ ETHERNET STUFF ************/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 10, 0, 0, 22 };
EthernetServer server(80);

File webFile;

void setup()
{
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Ethernet.begin(mac, ip);
  server.begin();

  Serial.print("Initializing SD card...");
  // On the Ethernet Shield, CS is pin 4. It's set as an output by default.
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
   pinMode(53, OUTPUT);
   
  if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");
  
  // fire up the webserver
  Ethernet.begin(mac, ip);
  server.begin();
}

// How big our line buffer should be. 100 is plenty!
#define BUFSIZ 100

void loop()
{
  char clientline[BUFSIZ];
  int index = 0;
  
  EthernetClient client = server.available();
  if (client) {
    // an http request ends with a blank line
    boolean current_line_is_blank = true;
    
    // reset the input buffer
    index = 0;
    
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        
        // If it isn't a new line, add the character to the buffer
        if (c != '\n' && c != '\r') {
          clientline[index] = c;
          index++;
          // are we too big for the buffer? start tossing out data
          if (index >= BUFSIZ) 
            index = BUFSIZ -1;
          
          // continue to read more data!
          continue;
        }
        
        // got a \n or \r new line, which means the string is done
        clientline[index] = 0;
        
        if (strstr(clientline, "GET / ") != 0) {
          Serial.println("index requested");
          
          webFile = SD.open("ds/index.htm");
        }
        else {
          char *filename;
          clientline[2] = 'd';
          clientline[3] = 's';
          filename = clientline + 2; // look after the "GET /" (5 chars)
          
          // we only want the filename
          (strstr(clientline, " HTTP"))[0] = 0;
          
          webFile = SD.open(filename);
        }
        
        if (webFile) {
          // FILE WAS FOUND         
          client.println("HTTP/1.1 200 OK");
          
          // handle mime types
          if (strstr(clientline, ".css") != 0)
            client.println("Content-Type: text/css");
          else if (strstr(clientline, ".js") != 0) 
            client.println("Content-Type: application/javascript");
          else if (strstr(clientline, ".txt") != 0) 
            client.println("Content-Type: text/plain");
          else if (strstr(clientline, ".jpg") != 0) 
            client.println("Content-Type: image/jpeg");
          else if (strstr(clientline, ".png") != 0) 
            client.println("Content-Type: image/png");
          else
            client.println("Content-Type: text/html");
          
          client.println();
          
          // read from the file until there's nothing else in it:
          while (webFile.available()) {
            client.print((char)webFile.read());
          }
          
          // close the file:
          webFile.close();
        } else {
          client.println("HTTP/1.1 404 Not Found");
          client.println("Content-Type: text/html");
          client.println();
          if (strstr(clientline, "GET / ") != 0)
            client.println("<h2>driverstation not found - check SD card</h2>");
          else
            client.println("<h2>File Not Found!</h2>");
        }

        break;
      }
    }
    // give the web browser time to receive the data
    delay(1);
    client.stop();
  }
}
