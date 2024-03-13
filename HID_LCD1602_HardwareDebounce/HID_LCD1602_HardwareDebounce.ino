#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keyboard.h>
#include <Mouse.h>

const int  en = 2, rw = 1, rs = 0, d4 = 4, d5 = 5, d6 = 6, d7 = 7, bl = 3;
const int i2c_addr = 0x27;      //0x27
LiquidCrystal_I2C lcd(i2c_addr, en, rw, rs, d4, d5, d6, d7, bl, POSITIVE);

const int encoder1A = 6; //CLK
const int encoder1B = 5; //DT
const int encoder1C = 3;
const int encoder2A = 14;//CLK
const int encoder2B = 16;//DT
const int encoder2C = 10;//SW

const int red_button = 7;
const int footSwitch1 = 8;
const int footSwitch2 = 9;

int profileSelect = 0;
int profileSelectReduce = 0;
int profileSelectAdvance = 0;
int profileGroup = 0;
int currentStateCLK;
int previousStateCLK;

//variable for toogle mode______________________________________________
int toggle1 = 0;
int toggle2 = 0;
int toggle3 = 0;
int toggle4 = 0;

//Foot switch ___________________________________________________________
const int SHORT_PRESS_TIME = 1000;
const int LONG_PRESS_TIME  = 1000;
//Foot switch 1 debounce________________________________________________(3)
int repeatLimiter1 = 0;   

//Foot switch 2 debounce________________________________________________(3.1)
int repeatLimiter2 = 0;               

//button debounce__________________long press_________ENCODER2__________(2)
int lastState_encoder2 = LOW;  // the previous state from the input pin
int currentState_encoder2;     // the current reading from the input pin
unsigned long pressedTime_ECD2  = 0;
unsigned long releasedTime_ECD2 = 0;
unsigned long ButtonHold_ECD2 = 0;

//turn off lcd backlight after 7 secconds________________________________(1)
unsigned long previousMillis = 0;
const long interval = 7000;
int toggleBackLight = 0;

void setup() {
  Serial.begin(9600);
  pinMode(encoder2A, INPUT_PULLUP);
  pinMode(encoder2B, INPUT_PULLUP);
  pinMode(encoder2C, INPUT_PULLUP);
  pinMode(red_button, INPUT_PULLUP);
  pinMode(footSwitch1, INPUT);
  pinMode(footSwitch2, INPUT);

  lcd.begin(16, 2);

  previousStateCLK = digitalRead(encoder2B);
}

void loop() {
  //turn off lcd backlight after 7 secconds______________________________(1)
  unsigned long currentMillis = millis();
  if (toggleBackLight == 0) {
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      lcd.noBacklight();
    }
  }

  //button debounce__________________long press_________ENCODER2__________(2)
  currentState_encoder2 = digitalRead(encoder2C);
  if (lastState_encoder2 == HIGH && currentState_encoder2 == LOW) {
    pressedTime_ECD2 = millis();
  }
  else if (lastState_encoder2 == LOW && currentState_encoder2 == HIGH) {
    releasedTime_ECD2 = millis();

    long pressDuration_ECD2 = releasedTime_ECD2 - pressedTime_ECD2;

    if ( pressDuration_ECD2 < SHORT_PRESS_TIME ) {
      profileGroup++;
      lcd.backlight();
      previousMillis = currentMillis;
      if (profileGroup >= 3) {
        profileGroup = 0;
      }
      Serial.print("profileGroup");
      Serial.println(profileGroup);
      print_profileGroup();
      profile_data();
    }
    if ( pressDuration_ECD2 > LONG_PRESS_TIME ) {
      Serial.println("A long press is detected");
      toggleBackLight++;
      if (toggleBackLight >> 1 ) {
        toggleBackLight = 0;
      }
      if (toggleBackLight == 1) {
        lcd.backlight();
      }
    }
  }
  lastState_encoder2 = currentState_encoder2;
  //______________________________________________________________________________

  //Foot switch 1 debounce________________________________________________________(3)
if (repeatLimiter1 == 0){
  if (digitalRead(footSwitch1) == 1){
    foot_switch1();
    Serial.println("switch 1 pressed");
  }
}

if (digitalRead(footSwitch1) == 0){
  repeatLimiter1 = 0;
  Keyboard.releaseAll();
  Serial.println("switch 1 released");
}

  //______________________________________________________________________________(3)

//foot switch 2 mode example_______
if (repeatLimiter2 == 0){
  if (digitalRead(footSwitch2) == 1){
    foot_switch2();
    Serial.println("switch 2 pressed");
  }
}

if (digitalRead(footSwitch2) == 0){
  repeatLimiter2 = 0;
  Keyboard.releaseAll();
  Serial.println("switch 2 released");
}


//_________________________________


  currentStateCLK = digitalRead(encoder2B);
  if (currentStateCLK != previousStateCLK) {
    if (digitalRead(encoder2A) != currentStateCLK) {
      profileSelectReduce++;
    }
    else {
      profileSelectAdvance++;
    }

    //use "profileSelectReduce&Advance to account for bouncing_________________________________________________
    if (profileSelectReduce >= 2) {
      profileSelect--;
      profileSelectReduce = 0;
      lcd.backlight();
      previousMillis = currentMillis;
      if (profileSelect > 3) {
        profileSelect = 0;
      }
      if (profileSelect < 0) {
        profileSelect = 3;
      }
      profile_data();
      Serial.print("profileSelect");
      Serial.println(profileSelect);
    }
    if (profileSelectAdvance >= 2) {
      profileSelect++;
      profileSelectAdvance = 0;
      lcd.backlight();
      previousMillis = currentMillis;
      if (profileSelect > 3) {
        profileSelect = 0;
      }
      if (profileSelect < 0) {
        profileSelect = 3;
      }
      profile_data();
      Serial.print("profileSelect");
      Serial.println(profileSelect);
    }
    //____________________________________________________________________

    previousStateCLK = currentStateCLK;
  }
}

void profile_data() {
  switch (profileGroup) {
    case 0:                           //work profile
      switch (profileSelect) {
        case 0:                         //Arduino
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Arduino   ");

          break;
        case 1:                         //MSword
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Word      ");

          break;
        case 2:
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Excell    ");

          break;
        case 3:
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Powerpoint");

          break;
      }
      break;

    case 1:                           //game profile
      switch (profileSelect) {
        case 0:                         //sifu
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Sifu      ");

          break;
        case 1:                         //valorant
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Valorant");

          break;
        case 2:                         //farcry 4
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Farcry 4");

          break;
        case 3:
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Forza Horizon 4");

          break;
      }
      break;

    case 2:                           //account manager
          break;
        case 3:                         //discord
          lcd.setCursor(0, 1); lcd.print("                "); lcd.setCursor(0, 1); lcd.print("Discord");

          break;
      }
      break;
  }
}

void print_profileGroup(){
  switch(profileGroup){
    case 0:         //work profile
      lcd.setCursor(0,0); lcd.print("                "); lcd.setCursor(0,0); lcd.print("Work");
    break;
    case 1:         //game profile
      lcd.setCursor(0,0); lcd.print("                "); lcd.setCursor(0,0); lcd.print("Video game");
    break;
    case 2:         //password manager profile
      lcd.setCursor(0,0); lcd.print("                "); lcd.setCursor(0,0); lcd.print("Password manager");
    break;
  }
}


void foot_switch1() {
  switch (profileGroup) {
    case 0:                           //work profile
      switch (profileSelect) {
        case 0:                         //Arduino
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.press('t');
          Keyboard.releaseAll();
          repeatLimiter2 = 1;
          break;
        case 1:                         //MSword

          break;
        case 2:

          break;
        case 3:

          break;
      }
      break;

    case 1:                           //game profile
      switch (profileSelect) {
        case 0:                         //sifu
          //          Keyboard.press('w');
          //          delay(20);
          //          Keyboard.releaseAll();
          //          Keyboard.press('w');
          //          delay(20);
          //          Keyboard.releaseAll();
          //          Mouse.press();
          //          delay(20);
          //          Mouse.release();

          Mouse.press(MOUSE_RIGHT);
          delay(50);
          Mouse.release(MOUSE_RIGHT);
          Mouse.press();
          delay(50);
          Mouse.release();
          break;
        case 1:                         //valorant
          toggle1++;
          if (toggle1 >= 2) {
            toggle1 = 0;
          }
          switch (toggle1) {
            case 0:
              Keyboard.release('v');
              break;
            case 1:
              Keyboard.press('v');
              break;
          }
          break;
        case 2:                         //farcry 4

          break;
        case 3:                         //forza horizon 4
          Keyboard.press('p');
          Keyboard.release('p');
          break;
      }
      break;
  }
}

void foot_switch2() {
  switch (profileGroup) {
    case 0:                           //work profile
      switch (profileSelect) {
        case 0:                         //Arduino
          Keyboard.press(KEY_LEFT_CTRL);
          Keyboard.write('/');
          Keyboard.releaseAll();
          repeatLimiter2 = 1;
          break;
          
        case 1:                         //MSword

          break;
        case 2:

          break;
        case 3:

          break;
      }
      break;

    case 1:                           //game profile
      switch (profileSelect) {
        case 0:                         //sifu
          Keyboard.press('s');
          delay(20);
          Keyboard.releaseAll();
          Keyboard.press('w');
          delay(20);
          Keyboard.releaseAll();
          Mouse.click(MOUSE_RIGHT);
        break;
        
        case 1:                         //valorant
          Keyboard.press(KEY_LEFT_SHIFT);
        break;
        
        case 2:                         //farcry 4

          break;
        case 3:                         //forza horizon 4
          Keyboard.press('t');
          Keyboard.release('t');
          repeatLimiter2 = 1;
          break;
      }
      break;

    case 2:                           //account manager
    switch (profileSelect) {
        case 0:                         //Gmail

        break;
        
        case 1:                         //Gelbooru

        break;
        
        case 2:                         //Facebook

          break;
        case 3:                         //Discord

          break;
      }
    break;
  }
}

//void foot_switch2() {
//  switch (profileGroup) {
//    case 0:                           //work profile
//      switch (profileSelect) {
//        case 0:                         //Arduino
//          Keyboard.press(KEY_LEFT_CTRL);
//          Keyboard.write('/');
//          Keyboard.releaseAll();
//          break;
//        case 1:                         //MSword
//
//          break;
//        case 2:
//
//          break;
//        case 3:
//
//          break;
//      }
//      break;
//
//    case 1:                           //game profile
//      switch (profileSelect) {
//        case 0:                         //sifu
//          Keyboard.press('s');
//          delay(20);
//          Keyboard.releaseAll();
//          Keyboard.press('w');
//          delay(20);
//          Keyboard.releaseAll();
//          Mouse.click(MOUSE_RIGHT);
//          break;
//        case 1:                         //valorant
//          toggle2++;
//          if (toggle2 >= 2) {
//            toggle2 = 0;
//          }
//          switch (toggle2) {
//            case 0:
//              Keyboard.release(',');
//              break;
//            case 1:
//              Keyboard.press(',');
//              break;
//          }
//          break;
//        case 2:                         //farcry 4
//
//          break;
//        case 3:                         //forza horizon 4
//          Keyboard.press('t');
//          Keyboard.release('t');
//          break;
//      }
//      break;
//  }
//}sw
