// Smart Light Controller
// LED, CDS(Photo Resistor), Ubidots

#include "UbidotsMicroESP8266.h"
#define DEVICE  "led-control"  // Put here your Ubidots device label
#define VARIABLE01  "led-value"  // Put here your Ubidots variable label
#define VARIABLE02 "light-value"
#define TOKEN  "A1E-NPfOekvBf8qTvOs3RWj3TnPrMAKOF8"  // Put here your Ubidots TOKEN
#define WIFISSID "melon"
#define PASSWORD "deitcs3217"
#define LED_PIN D4 

Ubidots client(TOKEN);

void setup() {
    Serial.begin(115200);
    client.wifiConnection(WIFISSID, PASSWORD);
    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, 1);
    client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() {
    float value = client.getValueWithDevice(DEVICE, VARIABLE01);
    if (value != ERROR_VALUE){
      Serial.print(F("value obtained: "));
      Serial.println(value);

      if(value == 1) { 
        digitalWrite(LED_PIN, HIGH);
        lightSensor();
      }
      else digitalWrite(LED_PIN, LOW);
      
    }else{
      Serial.println(F("Error getting value"));
    }
    delay(1000);
}

void lightSensor() {
    // read the input on analog pin 0:
    int sensorValue = analogRead(A0);
    int outValue = map(sensorValue, 0, 1023, 0, 255);
    Serial.println(outValue);
    analogWrite(LED_PIN, outValue);

    // use VARIABLE02 "light-value" -> ID
    client.add("5d0b3ea8c03f971d66c439ba", outValue);
    client.sendAll();
 }
