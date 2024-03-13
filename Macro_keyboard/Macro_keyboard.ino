//https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
#include <Keyboard.h>
#include <Mouse.h>
const byte BUTTON1 = 14;
const byte BUTTON2 = 16;

void setup() {
  pinMode(BUTTON1, INPUT);
  pinMode(BUTTON2, INPUT);

}

void loop() {

  if (digitalRead(BUTTON1)) {
    Keyboard.press(KEY_LEFT_CTRL);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.write('n');
    Keyboard.releaseAll();
    delay(500);
    Keyboard.println("https://hentaiz.cc/");
    
    delay(500);
  }

    if (digitalRead(BUTTON2)) {
    Keyboard.println("https://hentaiz.cc/");
    delay(500);
  }
}






  //  COPY PASTE
  //    if (digitalRead(BUTTON2)){
  //          Keyboard.press(KEY_LEFT_CTRL);
  //          Keyboard.write('c');
  //          Keyboard.releaseAll();
  //          delay(500);
  //        }
  //
  //    if (digitalRead(BUTTON1)){
  //      Keyboard.press(KEY_LEFT_CTRL);
  //      Keyboard.write('v');
  //      Keyboard.releaseAll();
  //      delay(500);
  //    }


  //  if (digitalRead(BUTTON2)) {                                       //task manager
//    Keyboard.press(KEY_LEFT_CTRL);
//    Keyboard.press(KEY_LEFT_SHIFT);
//    Keyboard.press(KEY_ESC);
//    Keyboard.releaseAll();
//    delay(500);
//  }
