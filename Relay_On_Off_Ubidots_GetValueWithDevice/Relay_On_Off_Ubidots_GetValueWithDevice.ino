#include "UbidotsMicroESP8266.h"

#define DEVICE  "relay"  // Put here your Ubidots device label
#define VARIABLE "relayvalue"  // Put here your Ubidots variable label

// Put here your Ubidots TOKEN
#define TOKEN  "A1E-btnEp0we6d27oA5sRLjlexPvxL02ro" 

#define WIFISSID "melon"
#define PASSWORD "deitcs3217"
#define REALY_PIN D2

Ubidots client(TOKEN);

void setup() {
    Serial.begin(115200);
    client.wifiConnection(WIFISSID, PASSWORD);
    pinMode(REALY_PIN, OUTPUT);
    client.setDebug(true); // Uncomment this line to set DEBUG on
}

void loop() {
    float value = client.getValueWithDevice(DEVICE, VARIABLE);
    
    if (value != ERROR_VALUE){
      Serial.print(F("value obtained: "));
      Serial.println(value);

      // send back to Ubidots
      client.add("ledValue", value);
      client.sendAll(true);

      if(value == 1)  {
        digitalWrite(REALY_PIN, HIGH);
      } else {
        digitalWrite(REALY_PIN, LOW);
      }
      
    }else{
      Serial.println(F("Error getting value"));
    }
    delay(1000);
}
