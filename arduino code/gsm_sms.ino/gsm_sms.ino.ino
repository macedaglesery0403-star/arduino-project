#include <SoftwareSerial.h>

SoftwareSerial gsmSerial(7, 8);

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

  delay(2000);

  gsmSerial.println("AT");
  delay(1000);

  gsmSerial.println("AT+CMGF=1");
  delay(1000);

  gsmSerial.println("AT+CMGS=\"+639XXXXXXXXX\"");
  delay(1000);

  gsmSerial.print("Hello! GSM working test");
  gsmSerial.write(26); // CTRL+Z
}

void loop() {
}