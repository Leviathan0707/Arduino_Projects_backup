#include <Wire.h>
#include <LiquidCrystal_I2C.h>
const int relayPin = 13;
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);
int counter = 1;
int currentStateCLK;
int previousStateCLK;
int eventDuration = 1440; 
String encdir = " ";
volatile bool state = LOW;
volatile bool trigger = LOW;
unsigned long previousTime = 0;
volatile unsigned long currentTime = 0;

void setup() {
  pinMode(3, INPUT_PULLUP); //SWITCH
  attachInterrupt(digitalPinToInterrupt(3), rotaryEncoderButton, FALLING);
  pinMode(4, INPUT); //DT
  pinMode(5, INPUT); //CLK
  pinMode(13, OUTPUT); //optocoupler
  lcd.begin(20,4);
  lcd.setCursor(0,0);lcd.print("Mode:");       lcd.setCursor(6,0); lcd.print("Intervalometer");
  lcd.setCursor(0,1);lcd.print("Time(s):");    lcd.setCursor(11,1);lcd.print(counter); 
  lcd.setCursor(0,2);lcd.print("24fps 1min 4MB 1440");
  lcd.setCursor(0,3);lcd.print("Duration(s):");lcd.setCursor(14,3);lcd.print(eventDuration);
  previousStateCLK = digitalRead(5);
}

void loop() {
//read Rotary encoder ||||||||||||||||||||||||||||||||||||||||||
currentStateCLK = digitalRead(5);
  if (currentStateCLK != previousStateCLK) {rotaryEncoder();}
// Bulb mode |||||||||||||||||||||||||||||||||||||||||||||||||||
if (state){bulbMode();}

//Intervalometer mode ||||||||||||||||||||||||||||||||||||||||||
currentTime = millis();
if (!state){
  if (currentTime - previousTime >= counter*1000) {
    digitalWrite(relayPin, HIGH);
  }
  if (currentTime - previousTime >= counter*1000+500) {
    previousTime = currentTime;
    digitalWrite(relayPin, LOW);
  }
}
}

// Rotary encoder function ||||||||||||||||||||||||||||||||||||
void rotaryEncoder(){
  if (digitalRead(4) != currentStateCLK) {
      counter ++;
      previousTime = currentTime;
    }
    else {
      counter --;
      previousTime = currentTime;
      state = LOW; 
      trigger = LOW;
      digitalWrite(relayPin,LOW);      
      lcd.setCursor(6,0); lcd.print("Intervalometer");
    }
    previousStateCLK = currentStateCLK;

    eventDuration = counter * 1440;
    
    lcd.setCursor(11,2); lcd.print(encdir);
    if (counter <=0){lcd.setCursor(11,1); lcd.print(0); }
    if (counter > 0){lcd.setCursor(11,1); lcd.print("     ");
                     lcd.setCursor(11,1); lcd.print(counter);
                     lcd.setCursor(14,3); lcd.print("      ");
                     lcd.setCursor(14,3); lcd.print(eventDuration);}                    
}
// Rotary encoder button (Interrupt Service Routine) |||||||||||
void rotaryEncoderButton(){state = HIGH;trigger = HIGH;}
//Bulb mode function||||||||||||||||||||||||||||||||||||||||||||
void bulbMode(){
  if (trigger == HIGH){ 
    digitalWrite(relayPin,HIGH);
    previousTime = currentTime;
    lcd.setCursor(6,0); lcd.print("Bulb mode     "); 
    trigger = LOW; 
    }
  if (currentTime - previousTime >= counter*1000){
    digitalWrite(relayPin, LOW);
    previousTime = currentTime;
    lcd.setCursor(6,0); lcd.print("Intervalometer");
    state = LOW;
    }
}
