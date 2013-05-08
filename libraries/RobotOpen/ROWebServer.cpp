#include "RobotOpen.h"

// Initialize our http constants
const char *ROWebServer::http_open[7] = { "HTTP/1.1 200 OK\n",\
										  "Content-Type: text/html\n",
										  "Connection: close\n", "\n", \
							   			  "<!DOCTYPE HTML>\n",\
							   			  "<html>\n",\
							   			  "<meta http-equiv=\"refresh\" content=\"1\">\n"};
const char *ROWebServer::http_close = (char*)"</html>\n";


// clear our arrays and allocate
ROWebServer::ROWebServer() : server(80)
{
	fields =  new char*[NUM_FIELDS];
	datas = new char*[NUM_FIELDS];

	for(int i = 0; i < NUM_FIELDS; i++)
	{
		fields[i] =  new char[FIELD_LEN];
		datas[i] = new char[FIELD_LEN];

		strcpy(fields[i], "");
		strcpy(datas[i] , "");
	}
}


ROWebServer::ROWebServer(int port) : server(port)
{
	fields =  new char*[NUM_FIELDS];
	datas = new char*[NUM_FIELDS];

	for(int i = 0; i < NUM_FIELDS; i++)
	{
		fields[i] =  new char[FIELD_LEN];
		datas[i] = new char[FIELD_LEN];

		strcpy(fields[i], "");
		strcpy(datas[i] , "");
	}
}

// simple destructor
ROWebServer::~ROWebServer()
{
	for(int i = 0; i < NUM_FIELDS; i++)
	{
		delete fields[i];
		delete datas[i];
	}
	delete fields;
	delete datas;
}

// Add field and data, returns 1 on filled array
int ROWebServer::add_field(const char *field, const char *data, byte line)
{
	if(line < 23)
	{
		strcpy(fields[line], field);
		strcpy(datas[line], data);
		return 0;
	}
	return 1;
}

int ROWebServer::add_field(const char *label, int data, byte line)
{
	char tmp[6];
	sprintf(tmp, "%i", data);
	return add_field(label, tmp, line);
}

int ROWebServer::add_field(const char *label, double data, byte line)
{
	char tmp[10];
	sprintf(tmp, "%d", data);
	return add_field(label, tmp, line);
}

void ROWebServer::begin_server()
{
	server.begin();
}

void ROWebServer::webserver_loop()
{
	static int run_count = 0;
	static EthernetClient client;
	if(((run_count++)%35) == 0)
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
					wdt_reset();
					Serial.print("Request done, sending data\n");
					
					// send top of html page
					for(unsigned int i = 0; i < (sizeof(http_open)/sizeof(http_open[0])); i++)
					{
						client.print(http_open[i]);
						wdt_reset();
					}
					Serial.print("Sent http head\n");
					
					// send out our data
					for(int i = 0; i < NUM_FIELDS; i++)
					{
						wdt_reset();
						Serial.println(fields[i]);
						Serial.println(datas[i]);
						if((strlen(fields[i]) > 0 && strlen(fields[i]) < 128) && (strlen(datas[i]) > 0 && strlen(datas[i]) < 128))
						{
							client.print(fields[i]);
							client.print(": ");
							client.print(datas[i]);
							client.print("</br>");
							//client.print("\n");
							wdt_reset();
						}
					}
					Serial.print("Sent out data and fields\n");
					
					// closing </html>
					client.print(http_close);
					Serial.print("Sent out http close\n");
					
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
				wdt_reset();
			}
			client.stop(); //Disconnect from client
			Serial.print("Disconnecting from client\n");
		}
	}
}