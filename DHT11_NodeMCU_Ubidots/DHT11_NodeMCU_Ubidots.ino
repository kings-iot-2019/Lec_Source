// NodeMCU, DHT11, Ubidots
#include <DHT.h>
#include "UbidotsMicroESP8266.h"
#define TOKEN "A1E-btnEp0we6d27oA5sRLjlexPvxL02ro"
#define WIFISSID "melon"
#define PASSWORD "deitcs3217"

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
Ubidots client(TOKEN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  client.wifiConnection(WIFISSID, PASSWORD);
}

void loop() {
  // put your main code here, to run repeatedly:
  float temp = dht.readTemperature();
  float humi = dht.readHumidity();
  Serial.print("Temp: ");
  Serial.print(temp);
  Serial.print("  Humi: ");
  Serial.println(humi);

  client.add("Temperature", temp);
  client.add("Humidity", humi);
  client.sendAll(true);
   
  delay(1000);
}
