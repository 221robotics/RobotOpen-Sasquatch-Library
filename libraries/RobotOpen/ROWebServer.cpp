#include "RobotOpen.h"
#include <stdlib.h>

// Initialize our http opening constant
const char *ROWebServer::http_open[7] = {"HTTP/1.1 200 OK\n", "Content-Type: text/html\n", "Connection: close\n", "\n", \
							   "<!DOCTYPE HTML>\n", "<html>\n", "<meta http-equiv=\"refresh\" content=\"2\">\n"};

EthernetServer ROWebServer::server(80);

// clear our arrays and allocate
ROWebServer::ROWebServer()
{
	f_index = 0;
	http_close = (char*)"</html>\n";
	fields =  (char**)malloc(23);
	datas = (char**)malloc(23);
	memset(fields, 0, 23);
	memset(datas, 0, 23);

	//server = new EthernetServer(80);
}

ROWebServer::ROWebServer(int port)
{
	f_index = 0;
	http_close = (char*)"</html>\n";
	fields =  (char**)malloc(23);
	datas = (char**)malloc(23);
	memset(fields, 0, 23);
	memset(datas, 0, 23);

	//server = new EthernetServer(port);
}

// simple destructor
ROWebServer::~ROWebServer()
{
	//delete server;
	delete fields;
	delete datas;
}

// Add field and data, returns 1 on filled array
int ROWebServer::add_field(const char *field, const char *data)
{
	if(f_index < 23)
	{
		f_index++;
		fields[f_index] = (char*)field;
		datas[f_index] = (char*)data;
	}
	return 1;
}

void ROWebServer::begin_server()
{
	server.begin();
}

void ROWebServer::webserver_loop()
{
	static int run_count = 0;
	static EthernetClient client;
	if((run_count%10) == 0)
	{
		client = server.available();
		if(client)
		{ // check if connected
			Serial.print("client connected\n");
			boolean line_blank = true; // keep track if http request is done

			while(client.connected()) // another connect check for loop
			{
				char c = client.read();
				Serial.print(c);

				if(c == '\n' && line_blank) // blank newline, http request done
				{
					Serial.print("Request done, sending data");
					// send top of html page
					for(unsigned int i = 0; i < (sizeof(http_open)/sizeof(http_open[0])); i++)
					{
						client.print(http_open[i]);
					}
					Serial.print("Send http head");
					// send out our data
					for(int i = 0; fields[i] != (char*)"" && i < 23; i++)
					{
						client.print(fields[i]);
						client.print(": ");
						client.print(datas[i]);
						client.print("</br>");
					}
					Serial.print("Sent out data and fields");
					// closing </html>
					client.print(http_close);
					Serial.print("Sent out http close");
					break;
				}
				if(c == '\n') // Check if line is done
				{
					line_blank = true;
				}
				else if (c != '\r') // If not newline, not a blank line
				{
					line_blank = false;
				}
			}
			client.stop(); //Disconnect from client
			Serial.print("Disconnecting from client");
			Serial.print("Fields and datas cleared");
			delay(3);
		}
	}
	memset(fields, 0, 23);
	memset(datas, 0, 23);
	delay(1);
	run_count++;
}