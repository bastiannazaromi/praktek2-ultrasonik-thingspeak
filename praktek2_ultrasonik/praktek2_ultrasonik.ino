// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "ThingSpeak.h"

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

unsigned long myChannelNumber = 2068881;
const char * myWriteAPIKey = "L6LMTIVHM23M8PGG";

const char* ssid = "Bas";   // your network SSID (name) 
const char* password = "12345678";   // your network password

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

// Sensor Ultrasonik
#define echoPin D7
#define trigPin D8

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, password); // Sesuaikan SSID dan password ini

  Serial.println();
  
  for (int u = 1; u <= 5; u++)
  {
    if ((WiFiMulti.run() == WL_CONNECTED))
    {
      Serial.println("Wifi konek");
      delay(1000);
    }
    else
    {
      Serial.println("Wifi belum konek");
      delay(1000);
    }
  }
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

void loop() {
  int durasi, jarak, pos=0;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  durasi = pulseIn(echoPin, HIGH);
  jarak = (durasi / 2) / 29.1;

  if (jarak < 0) {
    jarak = 0;
  } else if (jarak > 100) {
    jarak = 100;
  }

  Serial.print("Jarak : ");
  Serial.print(jarak);
  Serial.println(" cm");
  
  if ((millis() - lastTime) > timerDelay) {
    // set the fields with the values
    ThingSpeak.setField(1, jarak);
    
    // write to the ThingSpeak channel
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

    if (x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }

    lastTime = millis();
  }

  delay(1000);
}
