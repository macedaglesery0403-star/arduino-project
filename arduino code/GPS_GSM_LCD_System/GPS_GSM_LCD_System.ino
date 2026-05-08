#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- GPS ----------------
SoftwareSerial gpsSerial(4, 3);

// ---------------- GSM ----------------
SoftwareSerial gsmSerial(7, 8);

// ---------------- DATA ----------------
String gpsLine = "";
String latitude = "NO GPS";
String longitude = "NO GPS";

bool gpsFix = false;

unsigned long lastSMS = 0;
const long smsInterval = 30000;

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  gpsSerial.begin(9600);
  gsmSerial.begin(9600);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("SYSTEM STARTING");
  delay(2000);
  lcd.clear();

  gsmSerial.println("AT");
  delay(1000);
  gsmSerial.println("AT+CMGF=1");
  delay(1000);
}

// ---------------- LOOP ----------------
void loop() {

  readGPS();
  displayLCD();
  sendSMS();

}

// ---------------- GPS READ ----------------
void readGPS() {
  while (gpsSerial.available()) {
    char c = gpsSerial.read();
    gpsLine += c;

    if (c == '\n') {
      if (gpsLine.indexOf("$GPGGA") >= 0) {
        parseGPS(gpsLine);
      }
      gpsLine = "";
    }
  }
}

// ---------------- GPS PARSER ----------------
void parseGPS(String data) {

  int comma1 = data.indexOf(',');
  int comma2 = data.indexOf(',', comma1 + 1);
  int comma3 = data.indexOf(',', comma2 + 1);
  int comma4 = data.indexOf(',', comma3 + 1);

  if (comma2 > 0 && comma4 > 0) {

    String lat = data.substring(comma2 + 1, comma3);
    String lon = data.substring(comma3 + 1, comma4);

    if (lat.length() > 0 && lon.length() > 0) {
      latitude = "LAT:" + lat;
      longitude = "LON:" + lon;
      gpsFix = true;
    }
  }
}

// ---------------- LCD DISPLAY ----------------
void displayLCD() {

  lcd.setCursor(0, 0);
  lcd.print("GPS TRACKER    ");

  lcd.setCursor(0, 1);
  lcd.print(latitude);
}

// ---------------- GSM SMS ----------------
void sendSMS() {

  if (gpsFix && millis() - lastSMS > smsInterval) {

    lastSMS = millis();

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("SENDING SMS");

    gsmSerial.println("AT");
    delay(1000);

    gsmSerial.println("AT+CMGF=1");
    delay(1000);

    gsmSerial.println("AT+CMGS=\"+639XXXXXXXXX\"");
    delay(1000);

    gsmSerial.print("GPS LOCATION:\n");
    gsmSerial.print(latitude);
    gsmSerial.print("\n");
    gsmSerial.print(longitude);

    gsmSerial.write(26);

    delay(3000);

    lcd.clear();
    lcd.print("SMS SENT");
    delay(2000);
    lcd.clear();
  }
}