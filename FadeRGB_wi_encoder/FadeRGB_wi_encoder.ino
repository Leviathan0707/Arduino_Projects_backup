#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int SW = 6;             //Rotary encoder
int DT = 7;
int CLK = 8;
int ledR = 9;           // the PWM pin the LED is attached to
int ledG = 10;   
int ledB = 11;   
int brightnessR = 0;    // how bright the LED is
int brightnessG = 0;
int brightnessB = 0;
int counter = 0;
int colorSelect = 0;    // 0 for red, 1 for green, 2 for blue
int currentStateCLK;
int previousStateCLK;

unsigned long previousMillis = 0;
int buttonState;    
int lastButtonState = HIGH;
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;

void setup() {
  // declare pin 9 to be an output:
  pinMode(SW, INPUT_PULLUP);
  pinMode(DT, INPUT);
  pinMode(CLK, INPUT);
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  lcd.begin(20,4);
  lcd.setCursor(0,0);lcd.print("VALUE: "); lcd.setCursor(7,0);lcd.print(0);
  lcd.setCursor(0,1);lcd.print("COLOR: "); lcd.setCursor(7,1);lcd.print("RED");
  previousStateCLK = digitalRead(CLK);
}

void loop() {
  int reading = digitalRead(SW);
  if (reading != lastButtonState) {lastDebounceTime = millis();}
  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;
      if (buttonState == LOW) {
        colorSelect++;
        if ( colorSelect >= 3 ){colorSelect = 0;}
        lcd.setCursor(7,1);lcd.print("     ");
        if (colorSelect == 0){lcd.setCursor(7,1);lcd.print("RED");
                              if (brightnessR <=0){lcd.setCursor(7,0); lcd.print(0); }
                              if (brightnessR > 0){lcd.setCursor(7,0); lcd.print("   ");
                              lcd.setCursor(7,0); lcd.print(brightnessR);}
                             }
        if (colorSelect == 1){lcd.setCursor(7,1);lcd.print("GREEN");
                              if (brightnessG <=0){lcd.setCursor(7,0); lcd.print(0); }
                              if (brightnessG > 0){lcd.setCursor(7,0); lcd.print("   ");
                              lcd.setCursor(7,0); lcd.print(brightnessG);}
                             }
        if (colorSelect == 2){lcd.setCursor(7,1);lcd.print("BLUE");
                              if (brightnessB <=0){lcd.setCursor(7,0); lcd.print(0); }
                              if (brightnessB > 0){lcd.setCursor(7,0); lcd.print("   ");
                              lcd.setCursor(7,0); lcd.print(brightnessB);}
                             } 
  }
    }
  }
  lastButtonState = reading;

  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != previousStateCLK) {rotaryEncoder();}
}

void rotaryEncoder(){
  if (digitalRead(DT) != currentStateCLK) {
      if (colorSelect == 0){brightnessR ++;}
      if (colorSelect == 1){brightnessG ++;}
      if (colorSelect == 2){brightnessB ++;}
    }
    else {
      if (colorSelect == 0){brightnessR --;}
      if (colorSelect == 1){brightnessG --;}
      if (colorSelect == 2){brightnessB --;}
    }
    previousStateCLK = currentStateCLK;     
                        
    if (colorSelect == 0){analogWrite(ledR, brightnessR);
                         if (brightnessR <=0){lcd.setCursor(7,0); lcd.print(0); }
                         if (brightnessR > 0){lcd.setCursor(7,0); lcd.print("   ");
                         lcd.setCursor(7,0); lcd.print(brightnessR);}
                         }
    
    if (colorSelect == 1){analogWrite(ledG, brightnessG);
                         if (brightnessG <=0){lcd.setCursor(7,0); lcd.print(0); }
                         if (brightnessG > 0){lcd.setCursor(7,0); lcd.print("   ");
                         lcd.setCursor(7,0); lcd.print(brightnessG);}
                         }
    
    if (colorSelect == 2){analogWrite(ledB, brightnessB);
                         if (brightnessB <=0){lcd.setCursor(7,0); lcd.print(0); }
                         if (brightnessB > 0){lcd.setCursor(7,0); lcd.print("   ");
                         lcd.setCursor(7,0); lcd.print(brightnessB);}
                         }                
}
