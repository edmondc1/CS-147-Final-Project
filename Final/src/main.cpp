#include <Arduino.h>
#include <WiFi.h>
#include <HttpClient.h>
#include <DFRobot_DHT20.h>
#include <string>
#include <analogWrite.h>

#define SOIL 33
#define LIGHT 32
DFRobot_DHT20 dht20;
char ssid[] = "ALPINE2877";    // your network SSID (name) 
char pass[] = "2R1h579$"; // your network password (use for WPA, or use as key for WEP)
const char kHostname[] = "13.56.16.33";

void setup(){
  Serial.begin(115200);
  pinMode(SOIL, INPUT);
  dht20.begin();
  pinMode(LIGHT, INPUT);


  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("MAC address: ");
  Serial.println(WiFi.macAddress());
}

void loop(){
  float dirt = analogRead(SOIL);
  dirt = ((4096-dirt)/2096)*100;

  float temp = dht20.getTemperature();
  float hum = dht20.getHumidity()*100;
  float light = analogRead(LIGHT);
  light = (light/4096)*100;
  char s[50];
  sprintf(s, "/data/?var=%.2f,%.2f,%.2f,%.2f", dirt, temp, hum, light);

  WiFiClient c;
  HttpClient http(c);

  int err = http.get(kHostname,5000,s);
  Serial.println(err);
  
  Serial.println(dirt);
  Serial.println(temp);
  Serial.println(hum);
  Serial.println(light);

  delay(500);
}