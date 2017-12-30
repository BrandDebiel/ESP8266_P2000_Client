#include "P2000WifiClient.h"

P2000WifiClient::P2000WifiClient()
{
	messageCounter = 0;
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

void P2000WifiClient::getData(char* receiveBuffer)
{
	if(tcpClient.available())
	{
		if (m_receiveBufferPayloadSize == 0)
		{
			char bufferIn[4];			
			tcpClient.readBytes(bufferIn, 4);
			memcpy(&m_receiveBufferPayloadSize, bufferIn, sizeof m_receiveBufferPayloadSize);
		}
		else
		{
			tcpClient.readBytes(receiveBuffer, m_receiveBufferPayloadSize);
			//tcpClient.readBytesUntil('\n', receiveBuffer, m_receiveBufferPayloadSize);	
			Serial.print("<<Payloadsize: "); 
			Serial.println(m_receiveBufferPayloadSize);
			Serial.print("<<Payload: ");  
			Serial.print(messageCounter++);
			Serial.print(" - ");
			Serial.println(receiveBuffer);
			m_receiveBufferPayloadSize = 0;
		}		
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

void P2000WifiClient::disconnect()
{
	tcpClient.stop();
	Serial.println("Connection stopped");
}

void P2000WifiClient::sendData(char* sendBuffer)
{	
	uint32_t payload = strlen(sendBuffer);
	char payloadSize[4];
	sprintf(payloadSize, "%lu", payload);

	tcpClient.write((const uint8_t *)payloadSize, 4);
	tcpClient.write((const uint8_t *)sendBuffer, payload);
	Serial.print(">>Payloadsize: ");
	Serial.println(payloadSize); 
	Serial.print(">>Payload: ");
	Serial.println(sendBuffer);

}

bool P2000WifiClient::connected()
{
	return(connect());
}