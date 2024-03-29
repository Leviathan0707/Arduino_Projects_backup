//https://diyusthad.com/image2cpp
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET 4
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128

// 'arduino-logo-1 - Copy', 128x64px
const unsigned char arduino_logo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x00, 
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xc0, 0x03, 0xff, 0xff, 0xfc, 0x3f, 0xff, 0xff, 0x80, 
  0x01, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xe0, 0x07, 0xff, 0xff, 0x80, 0x01, 0xff, 0xff, 0x80, 
  0x03, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0x0f, 0xff, 0xfe, 0x00, 0x00, 0x7f, 0xff, 0xc0, 
  0x03, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xf8, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xe0, 
  0x07, 0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x1f, 0xff, 0xe0, 0x00, 0x00, 0x07, 0xff, 0xe0, 
  0x07, 0xff, 0xe0, 0x00, 0x00, 0x01, 0xff, 0xfe, 0x3f, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xf0, 
  0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xf8, 
  0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 
  0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xf8, 
  0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 
  0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0xfc, 
  0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0xfc, 
  0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xfe, 
  0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xfe, 
  0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x00, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xff, 
  0x7f, 0xf0, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x3f, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xff, 
  0x7f, 0xf8, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xfe, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xff, 
  0x7f, 0xf8, 0x01, 0xff, 0xff, 0xe0, 0x00, 0x7f, 0xff, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x00, 0xff, 0xff, 0xe0, 0x00, 0xff, 0xff, 0x00, 0x03, 0xff, 0xff, 0x80, 0x0f, 0xfe, 
  0x7f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0x80, 0x00, 0x0f, 0xc0, 0x00, 0x0f, 0xfe, 
  0x3f, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0xc0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xfe, 
  0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x03, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xfe, 
  0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xe0, 0x00, 0x0f, 0xc0, 0x00, 0x1f, 0xfe, 
  0x3f, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0xfc, 
  0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf8, 0x00, 0x0f, 0xc0, 0x00, 0x3f, 0xfc, 
  0x1f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xff, 0xfc, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 
  0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 
  0x0f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0xff, 0xf8, 
  0x0f, 0xff, 0xc0, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x3f, 0xff, 0x80, 0x00, 0x00, 0x01, 0xff, 0xf0, 
  0x07, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xfc, 0x3f, 0xff, 0xc0, 0x00, 0x00, 0x03, 0xff, 0xf0, 
  0x07, 0xff, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xfc, 0x1f, 0xff, 0xf0, 0x00, 0x00, 0x0f, 0xff, 0xe0, 
  0x03, 0xff, 0xfc, 0x00, 0x00, 0x1f, 0xff, 0xf8, 0x0f, 0xff, 0xf8, 0x00, 0x00, 0x1f, 0xff, 0xe0, 
  0x01, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xf0, 0x07, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xc0, 
  0x01, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0xe0, 0x03, 0xff, 0xff, 0x80, 
  0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x01, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 
  0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 
  0x00, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 
  0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 
  0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x07, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 
  0x00, 0x01, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xff, 0xff, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xff, 0xff, 0x80, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0xff, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xff, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xff, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x01, 0xff, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x07, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'a5970e2a977f9db1f8fc012508bc69e5', 128x64px
const unsigned char sifu_logo [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x07, 0xe0, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x10, 0x01, 0xff, 0x90, 0x00, 0x04, 0x03, 0xf8, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x18, 0x07, 0xff, 0xe0, 0x00, 0x06, 0x01, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x39, 0xcf, 0xff, 0xe0, 0x00, 0x0e, 0x00, 0xff, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x39, 0xff, 0xff, 0x80, 0x00, 0x3e, 0x00, 0x7f, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x10, 0x79, 0xff, 0xff, 0x00, 0x00, 0x3e, 0x00, 0x7f, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x38, 0x79, 0xff, 0xfc, 0x00, 0x00, 0x7e, 0x00, 0x3f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x78, 0xf9, 0xff, 0xf8, 0x00, 0x00, 0x7e, 0x00, 0x1f, 0xf8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xfc, 0xf3, 0xff, 0xe0, 0x0e, 0x00, 0xfe, 0x00, 0x0f, 0xfc, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0xff, 0xf3, 0xff, 0xc0, 0x1e, 0x01, 0xfc, 0x00, 0x0f, 0xfe, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xf3, 0xff, 0x80, 0x7f, 0x01, 0xf8, 0x00, 0x07, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x01, 0xff, 0xf3, 0xff, 0x81, 0xff, 0x83, 0xf0, 0x01, 0xe7, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xff, 0xf3, 0xff, 0x03, 0xff, 0x83, 0xe0, 0x00, 0x7f, 0xff, 0xc0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xe1, 0xee, 0x0f, 0xff, 0x87, 0xc0, 0x00, 0x3f, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xff, 0xe0, 0xce, 0x3f, 0xff, 0x87, 0x80, 0x00, 0x0f, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xff, 0xe8, 0x06, 0xff, 0xff, 0x80, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xff, 0xc0, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x20, 0x7f, 0xf0, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xff, 0xc7, 0xfc, 0x3f, 0xbf, 0xff, 0xfe, 0x3f, 0x00, 0x1f, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xff, 0x8f, 0xfe, 0x3f, 0xbf, 0xff, 0xfe, 0x3f, 0x90, 0x07, 0xf8, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0xff, 0xbf, 0xff, 0x3f, 0xbf, 0xff, 0xfe, 0x3f, 0xa0, 0x00, 0xfc, 0x00, 0x00, 
  0x00, 0x00, 0xff, 0xbf, 0x3f, 0xff, 0xbf, 0xbf, 0xff, 0xfe, 0x3f, 0x80, 0x00, 0x3c, 0x00, 0x00, 
  0x00, 0x01, 0xff, 0x7f, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x03, 0xfe, 0x7f, 0x3f, 0x3f, 0xff, 0xbf, 0xff, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x07, 0xfc, 0xff, 0x7f, 0xf8, 0x3f, 0xbf, 0x80, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x0f, 0xf0, 0xfe, 0x7f, 0xfe, 0x3f, 0xbf, 0xfe, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x1f, 0x01, 0xfe, 0x3f, 0xff, 0xbf, 0xbf, 0xfe, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x18, 0x01, 0xfc, 0x3f, 0xff, 0xff, 0xbf, 0xfe, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xfc, 0x0f, 0xff, 0xff, 0xbf, 0xfe, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x03, 0xfc, 0x03, 0xff, 0xff, 0xbf, 0xfe, 0xfe, 0x3f, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xf8, 0x7f, 0xff, 0xff, 0xbf, 0xfc, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x07, 0xf8, 0x7f, 0xff, 0xff, 0xbf, 0x80, 0x7f, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xf8, 0x7f, 0xff, 0xff, 0xbf, 0x80, 0x7f, 0xff, 0x30, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x0f, 0xf0, 0x3f, 0xff, 0xbf, 0xbf, 0x80, 0x3f, 0xff, 0x70, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xf0, 0x1f, 0xfe, 0x3f, 0xbf, 0x80, 0x1f, 0xfe, 0x7c, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x1f, 0xe0, 0x07, 0xfc, 0x3f, 0xbf, 0x00, 0x4f, 0xf8, 0xfe, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xe0, 0x00, 0x01, 0x00, 0x00, 0x00, 0xe0, 0x03, 0xff, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0xc0, 0x0c, 0x0f, 0x86, 0x40, 0x01, 0xfe, 0x01, 0xff, 0x80, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x3f, 0x80, 0x0e, 0x1f, 0x87, 0xe0, 0x07, 0xff, 0x00, 0xff, 0xc0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7f, 0x00, 0x0e, 0x1f, 0x83, 0xe0, 0x0f, 0xfe, 0x00, 0xff, 0xe0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x7e, 0x00, 0x04, 0x1f, 0x81, 0xc0, 0x1f, 0xfe, 0x00, 0x7f, 0xf0, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfc, 0x00, 0x04, 0x1f, 0x81, 0xc0, 0x3f, 0xfc, 0x00, 0x3f, 0xf8, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xfc, 0x00, 0x00, 0x1f, 0x81, 0xe0, 0x7f, 0xf8, 0x00, 0x1f, 0xfe, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0xf8, 0x00, 0x00, 0x1f, 0x80, 0xc0, 0xff, 0xe0, 0x00, 0x1f, 0xff, 0x00, 0x00, 0x00, 
  0x00, 0x01, 0xf0, 0x00, 0x00, 0x1f, 0x80, 0x01, 0xff, 0x00, 0x00, 0x0f, 0xff, 0x80, 0x00, 0x00, 
  0x00, 0x01, 0xe0, 0x00, 0x00, 0x1f, 0x80, 0x03, 0xf8, 0x00, 0x00, 0x07, 0xff, 0xe0, 0x00, 0x00, 
  0x00, 0x01, 0xc0, 0x00, 0x00, 0x1f, 0x80, 0x0f, 0xe0, 0x00, 0x00, 0x03, 0xff, 0xf0, 0x00, 0x00, 
  0x00, 0x03, 0x80, 0x00, 0x00, 0x1f, 0x80, 0x0f, 0x00, 0x00, 0x00, 0x01, 0xff, 0xf8, 0x00, 0x00, 
  0x00, 0x03, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x1c, 0x00, 0x00, 0x00, 0x00, 0xff, 0xfe, 0x00, 0x00, 
  0x00, 0x06, 0x00, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xff, 0x00, 0x00, 
  0x00, 0x04, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3f, 0xff, 0xc0, 0x00, 
  0x00, 0x04, 0x00, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f, 0xff, 0xf0, 0x00, 
  0x00, 0x08, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0xff, 0xc0, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  testdrawbitmap();    // Draw the required image 
}

void loop() {
}

void testdrawbitmap(void) {
//  display.clearDisplay();
//
//  display.drawBitmap(
//    (display.width()  - LOGO_WIDTH ) / 2,
//    (display.height() - LOGO_HEIGHT) / 2,
//    arduino_logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
//  display.display();
//  delay(1000);

  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    sifu_logo, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
//  delay(1000);  
}
