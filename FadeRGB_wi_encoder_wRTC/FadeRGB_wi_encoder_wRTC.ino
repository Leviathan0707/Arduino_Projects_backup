#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <TimeLib.h>
#include <DS1307RTC.h>

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
const byte interruptPin = 2;
int SW = 5;             //Rotary encoder
int DT = 6;
int CLK = 7;
int ledR = 9;           // the PWM pin the LED is attached to
int ledG = 10;   
int ledB = 11;   
int brightnessR = 0;    // how bright the LED is
int brightnessG = 0;
int brightnessB = 0;
int colorSelect = 0;    // 0 for red, 1 for green, 2 for blue
int currentStateCLK;
int previousStateCLK;
int ledBuiltIn = 13; 

int SetHour     = 21;
int SetMinute   = 55;
int SetSecond   = 15;

const long intervalTimeUpdate = 1000; 


unsigned long previousMillis = 0;
int reading;
int buttonState;    
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

unsigned long previousMillisForTimeUpdate = 0;

void setup() {
  pinMode(SW, INPUT_PULLUP);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  pinMode(ledBuiltIn, OUTPUT);
  lcd.begin(20,4);
  lcd.setCursor(1,0); lcd.print(">");
  lcd.setCursor(2,0); lcd.print("R:"); lcd.setCursor(4,0); lcd.print(0);        //LCD for RGB led
  lcd.setCursor(9,0); lcd.print("G:"); lcd.setCursor(11,0);lcd.print(0);
  lcd.setCursor(15,0);lcd.print("B:"); lcd.setCursor(17,0);lcd.print(0);

  lcd.setCursor(0,1); lcd.print("Alarm: ");   //LCD for Alarm
  lcd.setCursor(9,1); lcd.print(":");
  lcd.setCursor(12,1);lcd.print(":");

  lcd.setCursor(7,1) ;lcd.print("  ");lcd.setCursor(7,1) ;lcd.print(SetHour);
  lcd.setCursor(10,1);lcd.print("  ");lcd.setCursor(10,1);lcd.print(SetMinute);     // Set alarm
  lcd.setCursor(13,1);lcd.print("  ");lcd.setCursor(13,1);lcd.print(SetSecond);

  lcd.setCursor(0,2); lcd.print("Time: ");   //LCD for Clock
  lcd.setCursor(9,2); lcd.print(":");
  lcd.setCursor(12,2);lcd.print(":");
  
  lcd.setCursor(0,3); lcd.print("Date: ");
  lcd.setCursor(9,3); lcd.print(":");
  lcd.setCursor(12,3);lcd.print(":");
  
  previousStateCLK = digitalRead(CLK);
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
                    }
    previousMillisForTimeUpdate = currentMillisForTimeUpdate;
                                                                                      }
  // Alarm ////////////////////////////////////////////////////////////////////////////////////////
//  if ( tm.Hour == SetHour && tm.Minute == SetMinute && tm.Second == SetSecond ){
//    digitalWrite(ledBuiltIn, HIGH);          
//    analogWrite(ledR, 0);
//    analogWrite(ledG, 20);
//    analogWrite(ledB, 10);                                                                        
//  }

  //Read Button ///////////////////////////////////////////////////////////////////////////////////
  reading = digitalRead(SW);
  if (reading != lastButtonState) {lastDebounceTime = millis();}
  if ((millis() - lastDebounceTime) > debounceDelay) { debounce();}
  lastButtonState = reading;

  //Read Encoder ///////////////////////////////////////////////////////////////////////////////////
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != previousStateCLK) {rotaryEncoder();}
}

void rotaryEncoder(){
  if (digitalRead(DT) != currentStateCLK) {
      if (colorSelect == 0 && brightnessR < 255){brightnessR ++;}
      if (colorSelect == 1 && brightnessG < 255){brightnessG ++;}
      if (colorSelect == 2 && brightnessB < 255){brightnessB ++;}
    }
    else {
      if (colorSelect == 0 && brightnessR > 0){brightnessR --;}
      if (colorSelect == 1 && brightnessG > 0){brightnessG --;}
      if (colorSelect == 2 && brightnessB > 0){brightnessB --;}
    }
    previousStateCLK = currentStateCLK;     
                        
    if (colorSelect == 0){analogWrite(ledR, brightnessR);
                         if (brightnessR <=0){lcd.setCursor(4,0); lcd.print(0); }
                         if (brightnessR > 0){lcd.setCursor(4,0); lcd.print("   ");
                         lcd.setCursor(4,0); lcd.print(brightnessR);}
                         }
    
    if (colorSelect == 1){analogWrite(ledG, brightnessG);
                         if (brightnessG <=0){lcd.setCursor(11,0); lcd.print(0); }
                         if (brightnessG > 0){lcd.setCursor(11,0); lcd.print("   ");
                         lcd.setCursor(11,0); lcd.print(brightnessG);}
                         }
    
    if (colorSelect == 2){analogWrite(ledB, brightnessB);
                         if (brightnessB <=0){lcd.setCursor(17,0); lcd.print(0); }
                         if (brightnessB > 0){lcd.setCursor(17,0); lcd.print("   ");
                         lcd.setCursor(17,0); lcd.print(brightnessB);}
                         }                
}

void debounce(){
if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        colorSelect++;
        if ( colorSelect >= 3 ){colorSelect = 0;}
        if (colorSelect == 0){lcd.setCursor(8,0);lcd.print(" ");
                              lcd.setCursor(14,0);lcd.print(" ");
                              lcd.setCursor(1,0);lcd.print(">");}
                             
        if (colorSelect == 1){lcd.setCursor(1,0);lcd.print(" ");
                              lcd.setCursor(14,0);lcd.print(" ");
                              lcd.setCursor(8,0);lcd.print(">");}
                             
        if (colorSelect == 2){lcd.setCursor(1,0);lcd.print(" ");
                              lcd.setCursor(8,0);lcd.print(" ");
                              lcd.setCursor(14,0);lcd.print(">");}
                              }
                            }
              }
