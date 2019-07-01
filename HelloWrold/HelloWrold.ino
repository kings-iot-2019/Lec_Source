void setup() {
  // put your setup code here, to run once:
  // Communication to PC via USB cable
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Hello World!\n");
}
