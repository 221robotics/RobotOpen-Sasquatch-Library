#include <RobotOpen.h>
#include <Ethernet.h>
#include <avr/wdt.h>

#ifndef ROWebServer_h
#define ROWebServer_h

#define NUM_FIELDS 23
#define FIELD_LEN 20

class ROWebServer
{
	public:
	ROWebServer();
	ROWebServer(int port);
	
	~ROWebServer();

	int add_field(const char *label, const char *data, byte line);
	int add_field(const char *label, int data, byte line);
	int add_field(const char *label, double data, byte line);

	void begin_server();
	void webserver_loop();


	private:

	// some constants
	static const char *http_open[7];
	static const char *http_close;

	// data to be sent out to be displayed
	char **fields;
	char **datas;

	// ethernet server object
	EthernetServer server;
};

extern const char* http_open[7];
extern const char *http_close;

#endif