#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

int ledW = 10;           // the PWM pin the LED is attached to
int ledY = 11;   
int solenoidValve = 12
int brightnessW = 0;    // how bright the LED is
int brightnessY = 0;

const int wateringDuration = 3000;

unsigned long PWMchangeCounterW = 0;
unsigned long PWMchangeCounterY = 0;

const long intervalTimeUpdate = 1000; 
unsigned long previousMillisForTimeUpdate = 0;

void setup() {
  pinMode(ledW, OUTPUT);
  pinMode(ledY, OUTPUT);
}

void loop() {
  unsigned long currentMillisForTimeUpdate = millis();
  tmElements_t tm;
  RTC.read(tm);
//  if (currentMillisForTimeUpdate - previousMillisForTimeUpdate >= intervalTimeUpdate) {
//    PWMchangeCounterW++;
//    PWMchangeCounterY++;
//    lcd.setCursor(8,0);lcd.print("    ");lcd.setCursor(8,0);lcd.print(brightnessW);
//    lcd.setCursor(8,1);lcd.print("    ");lcd.setCursor(8,1);lcd.print(brightnessY);
//                    }
//    previousMillisForTimeUpdate = currentMillisForTimeUpdate;
                                                                                     
// Yellow led & White led 
switch(tm.Hour){
  case 4:
    switch(tm.Minute){
      case 20:
        analogWrite(ledY, 20);
      break;

      case 40:
        analogWrite(ledY, 40);
      break;
    }    
  break;

  case 5:
    analogWrite(ledY, 60);
  break;

  case 9:
    analogWrite(ledY, 40);
    analogWrite(ledW, 20);
  break;

  case 10:
    analogWrite(ledY, 20);
    analogWrite(ledW, 40);
  break;

  case 11: 
    analogWrite(ledY, 0);
    analogWrite(ledW, 60);
  break;

  case 16:
    analogWrite(ledY, 20);
    analogWrite(ledW, 40);
  break;

  case 17:
    analogWrite(ledY, 40);
    analogWrite(ledW, 20);
  break;

  case 18:
    switch(tm.Minute){
      case 0:
        analogWrite(ledY, 60);
        analogWrite(ledW, 0);
      break;
      
      case 20:
        analogWrite(ledY, 40);
      break;

      case 40:
        analogWrite(ledY, 20);
      break;
    }
  break;

  case 19:
    analogWrite(ledY, 1);
  break;
}

//control solenoid valve open time
// water 3 times a day, 3s/time
switch (tm.Hour){
  case 7:
    digitalWrite(solenoidValve, HIGH);
    delay(wateringDuration);
    digitalWrite(solenoidValve, LOW);
  break;

  case 11:
    digitalWrite(solenoidValve, HIGH);
    delay(wateringDuration);
    digitalWrite(solenoidValve, LOW);
  break;

  case 17:
    digitalWrite(solenoidValve, HIGH);
    delay(wateringDuration);
    digitalWrite(solenoidValve, LOW);
  break;
}

    }


    
                                                                                    
//      if ( tm.Hour == 4 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 1;     
//    analogWrite(ledY, brightnessY);
//  }
//
//  if ( tm.Hour == 5 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 80;     
//    analogWrite(ledY, brightnessY);
//  }
//
//  if ( tm.Hour == 6 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 80;     
//    analogWrite(ledY, brightnessY);
//  }
//
//if ( tm.Hour == 7 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 80;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 8 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 80;     
//    analogWrite(ledY, brightnessY);
//  }
//
//
//if ( tm.Hour == 11 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 80;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 0;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 12 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 80;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 0;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 13 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 80;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 0;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 14 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 80;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 0;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 15 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 80;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 0;     
//    analogWrite(ledY, brightnessY);
//  }
//
//  if ( tm.Hour == 18 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 80;     
//    analogWrite(ledY, brightnessY);
//  }
//
//if ( tm.Hour == 19 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 1;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 20 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 1;     
//    analogWrite(ledY, brightnessY);
//  }
//  if ( tm.Hour == 21 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 1;     
//    analogWrite(ledY, brightnessY);
//  }
//if ( tm.Hour == 22 && tm.Minute == 0 && tm.Second == 0 ){
//    brightnessW = 0;
//    analogWrite(ledW, brightnessW);
//    brightnessY = 1;     
//    analogWrite(ledY, brightnessY);
//  }
//  
////White led control
//    if ( tm.Hour >= 8 && tm.Hour < 11 ){
//      if ( PWMchangeCounterW >= 135 ) {
//        brightnessW++;
//        analogWrite(ledW, brightnessW);
//        PWMchangeCounterW = 0;     
//      }
//    }
//
//    if ( tm.Hour >= 15 && tm.Hour < 18 ){
//      if ( PWMchangeCounterW >= 135 ) {
//        brightnessW--;
//        analogWrite(ledW, brightnessW);
//        PWMchangeCounterW = 0;     
//      }
//    }
//
// //Yellow led control
//    if ( tm.Hour >= 4 && tm.Hour < 5 ){
//      if ( PWMchangeCounterY >= 45 ) {
//        brightnessY++;
//        analogWrite(ledY, brightnessY);
//        PWMchangeCounterY = 0;     
//      }
//    }
//
//    if ( tm.Hour >= 8 && tm.Hour < 11 ){
//      if ( PWMchangeCounterY >= 135 ) {
//        brightnessY--;
//        analogWrite(ledY, brightnessY);
//        PWMchangeCounterY = 0;     
//      }
//    }
//
//if ( tm.Hour >= 15 && tm.Hour < 18 ){
//      if ( PWMchangeCounterY >= 135 ) {
//        brightnessY++;
//        analogWrite(ledY, brightnessY);
//        PWMchangeCounterY = 0;     
//      }
//    }
//    
//if ( tm.Hour >= 18 && tm.Hour < 19 ){
//      if ( PWMchangeCounterY >= 45 ) {
//        brightnessY--;
//        analogWrite(ledY, brightnessY);
//        PWMchangeCounterY = 0;     
//      }
//    }                               
