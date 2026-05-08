#include <SoftwareSerial.h>

// GSM SIM900A
SoftwareSerial gsmSerial(7, 8); // RX, TX

void setup() {
  Serial.begin(9600);
  gsmSerial.begin(9600);

  Serial.println("GSM TEST START");

  delay(2000);

  gsmSerial.println("AT");
  delay(1000);

  gsmSerial.println("AT+CMGF=1"); // SMS mode
  delay(1000);

  gsmSerial.println("AT+CSQ"); // signal check
}

void loop() {

  if (gsmSerial.available()) {
    Serial.write(gsmSerial.read());
  }
}