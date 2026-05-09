#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// sample variables (for future GPS/GSM use)
String line1 = "SYSTEM READY";
String line2 = "WAITING DATA";

unsigned long lastUpdate = 0;

void setup() {

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("INITIALIZING");
  lcd.setCursor(0, 1);
  lcd.print("PLEASE WAIT");

  delay(2000);
  lcd.clear();
}

void loop() {

  updateLCD();
}

// ---------------- LCD UPDATE FUNCTION ----------------
void updateLCD() {

  // refresh every 1 second (non-blocking style)
  if (millis() - lastUpdate >= 1000) {
    lastUpdate = millis();

    lcd.setCursor(0, 0);
    lcd.print("                "); // clear line
    lcd.setCursor(0, 0);
    lcd.print(line1);

    lcd.setCursor(0, 1);
    lcd.print("                "); // clear line
    lcd.setCursor(0, 1);
    lcd.print(line2);
  }
}