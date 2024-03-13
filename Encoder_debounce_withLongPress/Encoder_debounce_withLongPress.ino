//ADD A 1uF capacitor for switch

const int SW = 10;             //Rotary encoder
const int DT = 14;
const int CLK = 16;

int currentStateCLK;
int previousStateCLK;

const int SHORT_PRESS_TIME = 1000; // 1000 milliseconds
const int LONG_PRESS_TIME  = 1000; // 1000 milliseconds

// Variables will change:
int lastState = LOW;  // the previous state from the input pin
int currentState;     // the current reading from the input pin
unsigned long pressedTime  = 0;
unsigned long releasedTime = 0;

unsigned long lastButtonHold = 0;
unsigned long ButtonHold = 0;
unsigned long HoldDelay = 1000;

int counter = 0 ;
void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT_PULLUP);
  pinMode(DT, INPUT_PULLUP);
  pinMode(CLK, INPUT_PULLUP);
  previousStateCLK = digitalRead(CLK);
}

void loop() {
  //Read Button ///////////////////////////////////////////////////////////////////////////////////
  currentState = digitalRead(SW);

  if(lastState == HIGH && currentState == LOW)        // button is pressed
    pressedTime = millis();
  else if(lastState == LOW && currentState == HIGH) { // button is released
    releasedTime = millis();

    long pressDuration = releasedTime - pressedTime;

    if( pressDuration < SHORT_PRESS_TIME )
      Serial.println("A short press is detected");

    if( pressDuration > LONG_PRESS_TIME )
      Serial.println("A long press is detected");
  }

  // save the the last state
  lastState = currentState;

  //Read Encoder ///////////////////////////////////////////////////////////////////////////////////
  currentStateCLK = digitalRead(CLK);
  if (currentStateCLK != previousStateCLK) {
    rotaryEncoder();
  }
  previousStateCLK = currentStateCLK;
}

void rotaryEncoder() {
  if (digitalRead(DT) != currentStateCLK) {
    counter++;
  }
  else {
    counter--;
  }
  Serial.println(counter);
}

  
