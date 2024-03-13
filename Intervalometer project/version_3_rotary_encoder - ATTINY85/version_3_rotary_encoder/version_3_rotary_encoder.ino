#include <TinyWireM.h>
#include <LiquidCrystal_I2C.h>   
const int relayPin = 1;
const int SWPin = 5 ;
const int DTPin = 4 ;
const int CLKPin= 3 ;
const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;
LiquidCrystal_I2C lcd(0x27,20,4); 
int counter = 1;
int currentStateCLK;
int previousStateCLK;
int eventDuration = 1440; 
bool state = LOW;
bool trigger = LOW;
unsigned long previousTime = 0;
unsigned long currentTime = 0;

void setup() {
  pinMode(5, INPUT_PULLUP); //SWITCH
  pinMode(4, INPUT); //DT
  pinMode(3, INPUT); //CLK
  pinMode(1, OUTPUT); //optocoupler 
  lcd.begin(20,4);
  TinyWireM.begin();                    // initialize I2C lib
  lcd.init();                           // initialize the lcd 
  lcd.backlight();
  lcd.setCursor(0,0);lcd.print("Mode:");       lcd.setCursor(6,0); lcd.print("Intervalometer");
  lcd.setCursor(0,1);lcd.print("Time(s):");    lcd.setCursor(11,1);lcd.print(counter); 
  lcd.setCursor(0,2);lcd.print("24fps 1min 4MB 1440");
  lcd.setCursor(0,3);lcd.print("Duration(s):");lcd.setCursor(14,3);lcd.print(eventDuration);
  previousStateCLK = digitalRead(CLKPin);
}

void loop() {
//read Rotary encoder ||||||||||||||||||||||||||||||||||||||||||
currentStateCLK = digitalRead(CLKPin);
  if (currentStateCLK != previousStateCLK) {rotaryEncoder();}
  if (digitalRead(SWPin) == LOW){state = HIGH;trigger = HIGH;}
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
  if (digitalRead(DTPin) != currentStateCLK) {
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
    
    if (counter <=0){lcd.setCursor(11,1); lcd.print(0); }
    if (counter > 0){lcd.setCursor(11,1); lcd.print("     ");
                     lcd.setCursor(11,1); lcd.print(counter);
                     lcd.setCursor(14,3); lcd.print("      ");
                     lcd.setCursor(14,3); lcd.print(eventDuration);}                    
}
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
