#include <Arduino.h>
#include <ESP8266WiFi.h>

const char* ssid     = "security-by-obscurity";
const char* password = "blablub";
#define BAUDRATE 115200
#define FRW D6
#define BKW D0

WiFiClient client;

void setup() {
    Serial.begin(BAUDRATE);
    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
       would try to act as both a client and an access-point and could cause
       network-issues with your other WiFi-devices on your WiFi-network. */
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    pinMode(FRW,INPUT_PULLUP);
    digitalWrite(FRW,HIGH);
    pinMode(BKW,INPUT_PULLUP);
    digitalWrite(BKW,HIGH);
}

void loop() {
	if (client.connect("pixelfun.fd",6600)){
		//client.println("next");
		if (!digitalRead(FRW)){
			client.println("next");
			Serial.println("forward");
		}
		if (!digitalRead(BKW)){
			client.println("previous");
			Serial.println("back");
		}
		client.stop();
		delay(500);
	}
}
