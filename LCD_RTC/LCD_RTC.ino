#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <DS1307RTC.h>


const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

unsigned long previousMillis = 0;
const long interval = 1000; 


void setup() {
  pinMode(13, OUTPUT);
  lcd.begin(20,4);
  lcd.setCursor(0,2); lcd.print("Time: ");   //LCD for Clock
  lcd.setCursor(9,2); lcd.print(":");
  lcd.setCursor(12,2);lcd.print(":");
  
  lcd.setCursor(0,3); lcd.print("Date: ");
  lcd.setCursor(9,3); lcd.print(":");
  lcd.setCursor(12,3);lcd.print(":");
}

void loop() {
  unsigned long currentMillis = millis();
  tmElements_t tm;
  if (currentMillis - previousMillis >= interval) {
  if (RTC.read(tm)) {
    lcd.setCursor(7,2) ;lcd.print("  ");lcd.setCursor(7,2) ;lcd.print(tm.Hour);
    lcd.setCursor(10,2);lcd.print("  ");lcd.setCursor(10,2);lcd.print(tm.Minute);
    lcd.setCursor(13,2);lcd.print("  ");lcd.setCursor(13,2);lcd.print(tm.Second);

    lcd.setCursor(7,3) ;lcd.print("  ");lcd.setCursor(7,3) ;lcd.print(tm.Day);
    lcd.setCursor(10,3);lcd.print("  ");lcd.setCursor(10,3);lcd.print(tm.Month);
    lcd.setCursor(13,3);lcd.print("  ");lcd.setCursor(13,3);lcd.print(tmYearToCalendar(tm.Year));
                    }
    previousMillis = currentMillis;
                                                  }
            }
