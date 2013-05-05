#include <RobotOpen.h>
#include <Ethernet.h>

#ifndef ROWebServer_h
#define ROWebServer_h

class ROWebServer
{
	public:
	ROWebServer();
	~ROWebServer();

	int add_field(char *label, char *data);

	void begin_server();
	void webserver_loop();


	static const char *http_open[7];
	char *http_close;

	private:

	// New server
	int f_index;
	char **fields;
	char **datas;
	EthernetServer *server;
};

extern const char* http_open[7];

#endif