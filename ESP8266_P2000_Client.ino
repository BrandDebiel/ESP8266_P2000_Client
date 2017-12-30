#include "P2000WifiClient.h"

char* ssid = "BrandDebiel";
char* password = "BrandWeer841";
char* host = "192.168.178.13";
uint16_t port = 5050;

P2000WifiClient tcpClient;
bool request = true;

#define timeIntervalIndex 0
#define previousMillisIndex 1
uint32_t intervalHeartbeat[2] = { 1000,0 };
uint32_t intervalReconnect[2] = { 5000,0 };
uint32_t intervalLedIndicator[2] = { 200,0 };
char dataToGet[255];

bool isNewMessage = false;

void setup() 
{
	Serial.begin(1000000);
	delay(200);

	pinMode(LED_BUILTIN, OUTPUT);
	tcpClient.begin(ssid, password, host, port);
}

void loop() 
{
	if (tcpClient.available())
	{	
		char *begin = dataToGet;
		char *end = begin + sizeof(dataToGet);
		std::fill(begin, end, 0);
		tcpClient.getData(dataToGet);
		isNewMessage = true;
		
	}

	unsigned long currentMillis = millis();
	//Send heartbeat
	if (currentMillis - intervalHeartbeat[previousMillisIndex] >= intervalHeartbeat[timeIntervalIndex]) {
		intervalHeartbeat[previousMillisIndex] = currentMillis;

		if (tcpClient.connected())
		{
			char* dataToSend = "P2000CLIENT;;COMMAND";
			tcpClient.sendData(dataToSend);
		}
	}
	//Check for connection
	if (currentMillis - intervalReconnect[previousMillisIndex] >= intervalReconnect[timeIntervalIndex]) {
		intervalReconnect[previousMillisIndex] = currentMillis;

		tcpClient.connect();
	}
	//Flash LED
	if ((currentMillis - intervalLedIndicator[previousMillisIndex] >= intervalLedIndicator[timeIntervalIndex])) {
		intervalLedIndicator[previousMillisIndex] = currentMillis;

		if (isNewMessage)
		{
			digitalWrite(LED_BUILTIN, !isNewMessage);
			isNewMessage = false;
		}
		else
		{
			digitalWrite(LED_BUILTIN, !isNewMessage);
		}
	}

}

