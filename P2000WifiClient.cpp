#include "P2000WifiClient.h"

P2000WifiClient::P2000WifiClient()
{

}

P2000WifiClient::~P2000WifiClient()
{
}

bool P2000WifiClient::begin(char* ssid, char* password, char* host, uint16_t port)
{
	m_ssid = ssid;
	m_password = password;
	m_host = host;
	m_port = port;

	Serial.println("Connecting to: ");
	Serial.print(m_ssid);

	WiFi.begin(m_ssid, m_password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("Wifi connected");
	Serial.print("myIP: ");
	Serial.println(WiFi.localIP());
}

void P2000WifiClient::getData(String& string)
{
	if(tcpClient.available())
	{
		string = tcpClient.readStringUntil('\n');
	}
}

bool P2000WifiClient::available()
{
	if (tcpClient.available() > 0)
	{
		return(true);
	}
	else
	{
		return(false);
	}
}

bool P2000WifiClient::connect()
{
	if (!tcpClient.connected())
	{
		Serial.print("Connecting to: ");
		Serial.println(m_host);

		const int httpPort = m_port;
		if (!tcpClient.connect(m_host, m_port)) {
			Serial.println("connection failed");
			return(false);
		}
		else
		{
			Serial.println("connection successfull");
			return(true);
		}
	}
	else
	{
		return(true);
	}
}