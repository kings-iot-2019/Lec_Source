/*
 * NodeMCU, DHT11, Adafruit 16x30 OLED Display
 */
 
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define DHTPIN D6
#define DHTTYPE DHT11
//#define OLED_RESET 4

#define OLED_RESET    -1 //4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
//Adafruit_SSD1306 display(OLED_RESET);

// Initialize DHT sensor
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  Wire.begin();
  dht.begin();
  //display.begin(SSD1306_SWITCHCAPVCC, 0x3C);// initialize with the I2C addr 0x3C
}

void displayTempHumid(){
  delay(2000);
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    display.clearDisplay(); // clearing the display
    display.setTextColor(WHITE); //setting the color
    display.setTextSize(1); //set the font size
    display.setCursor(5,0); //set the cursor coordinates
    display.print("Failed to read from DHT sensor!");
    return;
  }

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  
  display.setCursor(0,0);
  display.print("Humidity: "); 
  display.print(h);
  display.print(" %");
  display.setCursor(0,10);
  display.print("Tempreature: "); 
  display.print(t);
  display.print(" C"); 
  display.setCursor(0,20);
  display.print("Tempreature: "); 
  display.print(f);
  display.print(" F");

  display.display();
  //display.startscrollright(0x00, 0x00);
}

void loop() {
  displayTempHumid();
  display.display();
}
