#include "P2000WifiClient.h"

char* ssid = "BrandDebiel";
char* password = "BrandWeer841";
char* host = "192.168.178.13";
uint16_t port = 5050;

P2000WifiClient tcpClient;

void setup() 
{

	Serial.begin(1000000);
	delay(200);

	tcpClient.begin(ssid, password, host, port);


}

void loop() 
{
	if (!tcpClient.connect())
	{
		delay(2000);
	}
	else 
	{
		if (tcpClient.available())
		{
			String line;
			tcpClient.getData(line);
			Serial.println(line);
		}
	}

}

