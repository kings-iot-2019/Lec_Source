#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#include "UbidotsMicroESP8266.h"
#define TOKEN "A1E-btnEp0we6d27oA5sRLjlexPvxL02ro"
#define WIFISSID "melon"
#define PASSWORD "deitcs3217"

#define DHTPIN D4
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27,16,2);
Ubidots client(TOKEN);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();

  // lcd init
  lcd.begin();
  // lcd back light on
  lcd.backlight();
  //lcd.print("Test");

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

  // LCD Display
  // LCD Cursor change to (0,0)
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temp);

  // LCD Cursor change to (0,1)
  lcd.setCursor(0,1);
  lcd.print("Humi: ");
  lcd.print(humi);

  client.add("Temperature", temp);
  client.add("Humidity", humi);
  client.sendAll(true);
   
  delay(1000);
}
