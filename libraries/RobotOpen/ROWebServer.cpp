#include "RobotOpen.h"
#include <stdlib.h>

// Initialize our http opening constant
const char *ROWebServer::http_open[7] = {"HTTP/1.1 200 OK\n", "Content-Type: text/html\n", "Connection: close\n", "\n", \
							   "<!DOCTYPE HTML>\n", "<html>\n", "<meta http-equiv=\"refresh\" content=\"2\">\n"};

// clear our arrays and allocate
ROWebServer::ROWebServer()
{
	f_index = 0;
	http_close = (char*)"</html>\n";
	fields =  (char**)malloc(23);
	datas = (char**)malloc(23);
	memset(fields, 0, 23);
	memset(datas, 0, 23);

	server = new EthernetServer(80);
}

ROWebServer::ROWebServer(int port)
{
	f_index = 0;
	http_close = (char*)"</html>\n";
	fields =  (char**)malloc(23);
	datas = (char**)malloc(23);
	memset(fields, 0, 23);
	memset(datas, 0, 23);

	server = new EthernetServer(port);
}

// simple destructor
ROWebServer::~ROWebServer()
{
	delete server;
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
	server->begin();
}

void ROWebServer::webserver_loop()
{
	EthernetClient client = server->available();
	if(client)
	{ // check if connected
		boolean line_blank = true; // keep track if http request is done
		while(client.connected()) // another connect check for loop
		{
			char c = client.read();
			if(c == '\n' && line_blank) // blank newline, http request done
			{
				// send top of html page
				for(unsigned int i = 0; i < (sizeof(http_open)/sizeof(http_open[0])); i++)
				{
					client.print(http_open[i]);
				}
				
				// send out our data
				for(int i = 0; fields[i] != (char*)"" && i < 23; i++)
				{
					client.print(fields[i]);
					client.print(": ");
					client.print(datas[i]);
					client.print("</br>");
				}
				
				// closing </html>
				client.print(http_close);
				break;
			}
			if(c == '\n') // Check if line is done
			{
				line_blank = true;
			}
			else // If not newline, not a blank line
			{
				line_blank = false;
			}
		}
		client.stop(); //Disconnect from client

		for(unsigned int i = 0; i < (sizeof(fields)/sizeof(fields[0])); i++)
		{
			// Clears out fields so that add_fields can be used in loop
			fields[i] = (char*)"";
			datas[i] = (char*)"";
		}
	}
}