// Wifi
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include "ThingSpeak.h"

ESP8266WiFiMulti WiFiMulti;
WiFiClient client;

unsigned long myChannelNumber = 2060361;
const char * myWriteAPIKey = "F2EI4OS6E8RUOSWQ";
//
//const char* ssid = "PoltekHarber";   // your network SSID (name) 
//const char* password = "poltekharber";   // your network password

// Timer variables
unsigned long lastTime = 0;
unsigned long timerDelay = 20000;

// Sensor DHT
#include <DHT.h>

#define DHTPIN D0
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("PoltekHarber", "poltekharber"); // Sesuaikan SSID dan password ini

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

  dht.begin();
}

void loop() {
  int suhu = dht.readTemperature();
  int udara = dht.readHumidity();

  if (isnan(udara) || isnan(suhu)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.println();

    if (suhu < 100 || udara < 100) {
      Serial.print("Suhu : ");
      Serial.println(suhu);
      Serial.print("Kelembapan Udara : ");
      Serial.println(udara);

      if ((millis() - lastTime) > timerDelay) {
        // set the fields with the values
        ThingSpeak.setField(1, suhu);
        ThingSpeak.setField(2, udara);
        
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
    } else {
      Serial.println("Failed to read from DHT sensor!");
    }
  }

  delay(1000);
}
