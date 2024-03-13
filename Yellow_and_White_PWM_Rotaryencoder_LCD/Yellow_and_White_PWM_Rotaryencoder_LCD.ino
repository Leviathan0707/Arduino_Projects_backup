#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int SW = 4;             //Rotary encoder
int DT = 5;
int CLK = 6;
int ledY = 10;   // the PWM pin the LED is attached to
int ledW = 11;   
int brightnessY = 0;    // how bright the LED is
int brightnessW = 0;
int counter = 0;
int colorSelect = 0;    // 0 for yellow, 1 for white
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
  pinMode(ledY, OUTPUT);
  pinMode(ledW, OUTPUT);

  lcd.begin(20,4);
  lcd.setCursor(0,0);lcd.print("VALUE: "); lcd.setCursor(7,0);lcd.print(0);
  lcd.setCursor(0,1);lcd.print("COLOR: "); lcd.setCursor(7,1);lcd.print("YELLOW");
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
        if ( colorSelect >= 2 ){colorSelect = 0;}
        lcd.setCursor(7,1);lcd.print("     ");
        if (colorSelect == 0){lcd.setCursor(7,1);lcd.print("YELLOW");
                              if (brightnessY <=0){lcd.setCursor(7,0); lcd.print(0); }
                              if (brightnessY > 0){lcd.setCursor(7,0); lcd.print("      ");
                              lcd.setCursor(7,0); lcd.print(brightnessY);}
                             }
        if (colorSelect == 1){lcd.setCursor(7,1);lcd.print("WHITE ");
                              if (brightnessW <=0){lcd.setCursor(7,0); lcd.print(0); }
                              if (brightnessW > 0){lcd.setCursor(7,0); lcd.print("      ");
                              lcd.setCursor(7,0); lcd.print(brightnessW);}
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
      if (colorSelect == 0){brightnessY ++;}
      if (colorSelect == 1){brightnessW ++;}
    }
    else {
      if (colorSelect == 0){brightnessY --;}
      if (colorSelect == 1){brightnessW --;}

    }
    previousStateCLK = currentStateCLK;     
                        
    if (colorSelect == 0){analogWrite(ledY, brightnessY);
                         if (brightnessY <=0){lcd.setCursor(7,0); lcd.print(0); }
                         if (brightnessY > 0){lcd.setCursor(7,0); lcd.print("   ");
                         lcd.setCursor(7,0); lcd.print(brightnessY);}
                         }
    
    if (colorSelect == 1){analogWrite(ledW, brightnessW);
                         if (brightnessW <=0){lcd.setCursor(7,0); lcd.print(0); }
                         if (brightnessW > 0){lcd.setCursor(7,0); lcd.print("   ");
                         lcd.setCursor(7,0); lcd.print(brightnessW);}
                         }
              
}
