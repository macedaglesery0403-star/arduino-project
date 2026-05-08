#include <SoftwareSerial.h>

// ---------------- GPS ----------------
SoftwareSerial gpsSerial(4, 3); // RX, TX

// ---------------- DATA ----------------
String gpsLine = "";
String latitude = "NO GPS FIX";
String longitude = "NO GPS FIX";

bool gpsFix = false;

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);

  Serial.println("GPS MODULE STARTED");
}

void loop() {
  readGPS();

  if (gpsFix) {
    Serial.print("LAT: ");
    Serial.println(latitude);

    Serial.print("LON: ");
    Serial.println(longitude);

    Serial.println("-------------------");
  }

  delay(1000);
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
      latitude = lat;
      longitude = lon;
      gpsFix = true;
    }
  }
}