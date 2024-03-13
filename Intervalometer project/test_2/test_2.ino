const int ledPin =  13;// the number of the LED pin
const int relayPin = 12;
volatile byte state = LOW;
volatile byte byte0 = LOW;
volatile byte byte1 = LOW;
volatile byte byte2 = LOW;
volatile byte byte3 = LOW;
volatile byte byte4 = LOW;
volatile byte byte5 = LOW;
volatile byte byte6 = LOW;
volatile byte byte7 = LOW;
volatile byte trigger = LOW;
volatile unsigned long SUM = 1;
volatile unsigned long previousTime = 0;        // will store last time LED was updated

volatile long interval = 1000;
volatile long endinterval = 1500;
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), readinput, FALLING );
  pinMode(3, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(3), bulbmode,  FALLING);
  pinMode(relayPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT_PULLUP);
  pinMode(A2, INPUT_PULLUP);
  pinMode(A3, INPUT_PULLUP);
  pinMode(A4, INPUT_PULLUP);
  pinMode(A5, INPUT_PULLUP);
  pinMode(A6, INPUT_PULLUP);
  pinMode(A7, INPUT_PULLUP);

  lcd.noBacklight();
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void bulbmode() {
  state = !state;
  if (state){
    Serial.println("Bulb mode Activated");
    digitalWrite(ledPin, HIGH);
    digitalWrite(relayPin, HIGH);
    trigger = HIGH;
    } 
    else {
      Serial.println("Bulb mode Deactivated");
      digitalWrite(ledPin, LOW);
      digitalWrite(relayPin, LOW);
      }   
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
void readinput() {
  byte0 = !digitalRead(A0) * 1;                                             //byte0 = !digitalRead(A0) * 10000;    
  byte1 = !digitalRead(A1) * 2;                                             //byte1 = !digitalRead(A1) * 20000;    
  byte2 = !digitalRead(A2) * 2 * 2;                                         //byte2 = !digitalRead(A3) * 30000;    
  byte3 = !digitalRead(A3) * 2 * 2 * 2;                                     //byte3 = !digitalRead(A4) * 40000;    
  byte4 = !digitalRead(A4) * 2 * 2 * 2 * 2;                                 //byte4 = !digitalRead(A5) * 50000;    
  byte5 = !digitalRead(A5) * 2 * 2 * 2 * 2 * 2;                             //byte5 = !digitalRead(A6) * 60000;    
  if (analogRead(A6)<=300){byte6 = 2 * 2 * 2 * 2 * 2 * 2;}                    
    else {byte6 = 0;}
  if (analogRead(A7)<=300){byte7 = 2 * 2 * 2 * 2 * 2 * 2 * 2;}
    else {byte7 = 0;}
  SUM   = byte0 + byte1 + byte2 + byte3 + byte4 + byte5 + byte6 + byte7;    
  interval = SUM * 1000;                                                    //endinterval = SUM;
  endinterval = interval + 500;                                             //endinterval = interval + 500;
  Serial.println(SUM);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////
void loop() {
volatile unsigned long currentTime = millis();
if (!state){
  if (currentTime - previousTime >= interval) {
    digitalWrite(relayPin, HIGH);
  }
  if (currentTime - previousTime >= endinterval) {
    previousTime = currentTime;
    digitalWrite(relayPin, LOW);
  }
}
if (state){
  if (trigger == HIGH){ previousTime = currentTime; trigger = LOW; }
  if (currentTime - previousTime >= interval){
    Serial.println("Bulb mode Deactivated");
    digitalWrite(relayPin, LOW);
    digitalWrite(ledPin, LOW);
    previousTime = currentTime;
    state = !state;
    }
}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
