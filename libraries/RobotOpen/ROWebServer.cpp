#include "RobotOpen.h"
#include <stdlib.h>


const char *ROWebServer::http_open[7] = {"HTTP/1.1 200 OK\n", "Content-Type: text/html\n", "Connection: close\n", "\n", \
							   "<!DOCTYPE HTML>\n", "<html>\n", "<meta http-equiv=\"refresh\" content=\"2\">\n"};

ROWebServer::ROWebServer()
{
	f_index = 0;
	http_close = "</html>\n";
	fields =  (char**)malloc(23);
	datas = (char**)malloc(23);
	memset(fields, 0, 23);
	memset(datas, 0, 23);

	server = new EthernetServer(80);
}

ROWebServer::~ROWebServer()
{
	delete server;
	delete fields;
	delete datas;
}

int ROWebServer::add_field(char *field, char *data)
{
	if(f_index < 23)
	{
		f_index++;
		fields[f_index] = field;
		datas[f_index] = data;
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
		while(client.connected()) // another connect check
		{
			char c = client.read();
			if(c == '\n' && line_blank) // blank newline, http request done
			{
				for(int i = 0; i < sizeof(http_open); i++)
				{
					client.print(http_open[i]);
				}
				
				for(int i = 0; fields[i] != "" || i < 23; i++)
				{
					client.print(fields[i]);
					client.print(": ");
					client.print(datas[i]);
					client.print("</br>");
				}
				
				client.print(http_close);
				break;
			}
			if(c == '\n')
			{
				line_blank = true;
			}
			else
			{
				line_blank = false;
			}
		}
		client.stop();
		for(int i = 0; i < sizeof(fields)/sizeof(fields[1]); i++)
		{
			fields[i] = "";
			datas[i] = "";
		}
	}
}