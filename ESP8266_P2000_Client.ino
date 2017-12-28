#include <ESP8266WiFi.h>
#include <WiFiClient.h>

char* ssid = "BrandDebiel";
const char* password = "BrandWeer841";

const char* host = "192.168.178.13";
const char* streamId = "....................";
const char* privateKey = "....................";
uint32_t messageCounter = 0;

WiFiClient client;

void setup() {

	Serial.begin(1000000);
	delay(200);

	Serial.println("Connecting to: ");
	Serial.print(ssid);

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.print(".");
	}

	Serial.println("");
	Serial.println("Wifi connected");
	Serial.print("myIP: ");
	Serial.println(WiFi.localIP());

}

void loop() {

	while (client.available()) {

		String line = client.readStringUntil('\n');
		Serial.print(messageCounter);
		Serial.print(" - ");
		Serial.println(line);
		messageCounter++;
	}

	if (!client.connected())
	{
		delay(2000);
		Serial.print("Connecting to: ");
		Serial.println(host);

		const int httpPort = 5050;
		if (!client.connect(host, httpPort)) {
			Serial.println("connection failed");
			messageCounter = 0;
		}
		else
		{
			Serial.println("connection successfull");
		}
	}
}

