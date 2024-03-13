#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int ledW = 9;           // the PWM pin the LED is attached to
int ledY = 10;   
int ledB = 11;   
int brightnessW = 0;    // how bright the LED is
int brightnessY = 0;
unsigned long PWMchangeCounterW = 0;
unsigned long PWMchangeCounterY = 0;

const long intervalTimeUpdate = 1000; 
unsigned long previousMillisForTimeUpdate = 0;

void setup() {
  pinMode(ledW, OUTPUT);
  pinMode(ledY, OUTPUT);
  lcd.begin(20,4);
  lcd.setCursor(2,0); lcd.print("W:"); lcd.setCursor(4,0); lcd.print(0);        //LCD for White & Yellow led
  lcd.setCursor(9,0); lcd.print("Y:"); lcd.setCursor(11,0);lcd.print(0);

  lcd.setCursor(0,1); lcd.print("Frequency: ");   //LCD for Alarm

//  lcd.setCursor(7,1) ;lcd.print("  ");lcd.setCursor(7,1) ;lcd.print(SetHour1);
//  lcd.setCursor(10,1);lcd.print("  ");lcd.setCursor(10,1);lcd.print(SetMinute1);     // Set alarm
//  lcd.setCursor(13,1);lcd.print("  ");lcd.setCursor(13,1);lcd.print(SetSecond1);

  lcd.setCursor(0,2); lcd.print("Time: ");   //LCD for Clock
  lcd.setCursor(9,2); lcd.print(":");
  lcd.setCursor(12,2);lcd.print(":");
  
  lcd.setCursor(0,3); lcd.print("Date: ");
  lcd.setCursor(9,3); lcd.print("/");
  lcd.setCursor(12,3);lcd.print("/");

}

void loop() {
  unsigned long currentMillisForTimeUpdate = millis();
  tmElements_t tm;
  if (currentMillisForTimeUpdate - previousMillisForTimeUpdate >= intervalTimeUpdate) {
  if (RTC.read(tm)) {
    lcd.setCursor(7,2) ;lcd.print("  ");lcd.setCursor(7,2) ;lcd.print(tm.Hour);
    lcd.setCursor(10,2);lcd.print("  ");lcd.setCursor(10,2);lcd.print(tm.Minute);
    lcd.setCursor(13,2);lcd.print("  ");lcd.setCursor(13,2);lcd.print(tm.Second);

    lcd.setCursor(7,3) ;lcd.print("  ");lcd.setCursor(7,3) ;lcd.print(tm.Day);
    lcd.setCursor(10,3);lcd.print("  ");lcd.setCursor(10,3);lcd.print(tm.Month);
    lcd.setCursor(13,3);lcd.print("  ");lcd.setCursor(13,3);lcd.print(tmYearToCalendar(tm.Year));

    if ( tm.Hour >= 4 && tm.Hour < 17 ){
    PWMchangeCounterW++;
    PWMchangeCounterY++;
    }
                    }
    previousMillisForTimeUpdate = currentMillisForTimeUpdate;
                                                                                      }

// Control both LED at the marked time                                                                                      
  if ( tm.Hour == 4 && tm.Minute == 0 && tm.Second == 0 ){
    brightnessW = 0;
    analogWrite(ledW, brightnessW);
    lcd.setCursor(4,0); lcd.print(" "); lcd.setCursor(4,0); lcd.print(brightnessW);
    brightnessY = 100;     
    analogWrite(ledY, brightnessY);
    lcd.setCursor(11,0); lcd.print(" "); lcd.setCursor(11,0); lcd.print(brightnessY);  
  }

  if ( tm.Hour == 12 && tm.Minute == 0 && tm.Second == 0 ){
    brightnessW = 100;
    analogWrite(ledW, brightnessW);
    lcd.setCursor(4,0); lcd.print(" "); lcd.setCursor(4,0); lcd.print(brightnessW);
    brightnessY = 0;     
    analogWrite(ledY, brightnessY);
    lcd.setCursor(11,0); lcd.print(" "); lcd.setCursor(11,0); lcd.print(brightnessY);    
  }

//  if ( tm.Hour == 17 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    lcd.setCursor(4,0); lcd.print(" "); lcd.setCursor(4,0); lcd.print(brightnessW);
//    brightnessY = 100;     
//    analogWrite(ledY, brightnessY);
//    lcd.setCursor(11,0); lcd.print(" "); lcd.setCursor(11,0); lcd.print(brightnessY);    
//  }

    if ( tm.Hour >= 17 ){
        brightnessW = 0;
        analogWrite(ledW, brightnessW);
        lcd.setCursor(4,0); lcd.print("   "); lcd.setCursor(4,0); lcd.print(brightnessW);
        brightnessY = 100;     
        analogWrite(ledY, brightnessY);
        lcd.setCursor(11,0); lcd.print("   "); lcd.setCursor(11,0); lcd.print(brightnessY);
      }

//White led control
    if ( tm.Hour >= 4 && tm.Hour < 8 ){
      if ( PWMchangeCounterW >= 144 ) {
        brightnessW++;
        analogWrite(ledW, brightnessW);
        lcd.setCursor(4,0); lcd.print("   "); lcd.setCursor(4,0); lcd.print(brightnessW);
        PWMchangeCounterW = 0;     
      }
    }

    if ( tm.Hour >= 12 && tm.Hour < 17 ){
      if ( PWMchangeCounterW >= 180 ) {
        brightnessW--;
        analogWrite(ledW, brightnessW);
        lcd.setCursor(4,0); lcd.print("   "); lcd.setCursor(4,0); lcd.print(brightnessW);
        PWMchangeCounterW = 0;     
      }
    }

 //Yellow led control
    if ( tm.Hour >= 4 && tm.Hour < 12 ){
      if ( PWMchangeCounterY >= 288 ) {
        brightnessY--;
        analogWrite(ledY, brightnessY);
        lcd.setCursor(11,0); lcd.print("   "); lcd.setCursor(11,0); lcd.print(brightnessY);   
        PWMchangeCounterY = 0;     
      }
    }

    if ( tm.Hour >= 12 && tm.Hour < 17 ){
      if ( PWMchangeCounterY >= 180 ) {
        brightnessY++;
        analogWrite(ledY, brightnessY);
        lcd.setCursor(11,0); lcd.print("   "); lcd.setCursor(11,0); lcd.print(brightnessY);   
        PWMchangeCounterY = 0;     
      }
    }

    }
                                                                                    
                                     
