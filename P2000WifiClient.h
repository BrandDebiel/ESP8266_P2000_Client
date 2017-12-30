#ifndef __P2000WIFICLIENT_H__
#define __P2000WIFICLIENT_H__

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

class P2000WifiClient
{
public:
	P2000WifiClient();
	~P2000WifiClient();

	bool begin(char* ssid, char* password, char* host, uint16_t port);
	void getData(char* receiveBuffer);
	bool connect();
	void disconnect();
	bool connected();
	bool available();
	void sendData(char* sendBuffer);
	uint32_t m_receiveBufferPayloadSize;

private:
	char* m_ssid;
	char* m_password;
	char* m_host;
	uint16_t m_port;
	uint32_t messageCounter;
	

	WiFiClient tcpClient;


};

#endif // __P2000WIFICLIENT_H__