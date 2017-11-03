#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "I2Cdev.h"

#define OUTPUT_READABLE_ACCELGYRO
#define LED_PIN 13
bool blinkState = false;

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2


#define LOGO16_GLCD_HEIGHT 16 
#define LOGO16_GLCD_WIDTH  16 
static unsigned char PROGMEM const logo16_glcd_bmp[] =
{ B00000000, B11000000,
  B00000001, B11000000,
  B00000001, B11000000,
  B00000011, B11100000,
  B11110011, B11100000,
  B11111110, B11111000,
  B01111110, B11111111,
  B00110011, B10011111,
  B00011111, B11111100,
  B00001101, B01110000,
  B00011011, B10100000,
  B00111111, B11100000,
  B00111111, B11110000,
  B01111100, B11110000,
  B01110000, B01110000,
  B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int focus = 8;
const int shoot = 9;

int serial = 0;

void setup()   
{  
  
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif
                  
  Serial.begin(9600);

  Serial.println("Initializing I2C devices...");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  pinMode(focus, OUTPUT);
  pinMode(shoot, OUTPUT);
  
  display.display(); // show splashscreen
  delay(2000);
  display.clearDisplay();   // clears the screen and buffer
  
  display.display();

}

void loop() 
{
  // Send data only when you receive data
  if (Serial.available() > 0)
  {
    // Reading incoming bytes :
    serial = Serial.read();

    switch (serial)
    {
      case 'f':

        digitalWrite(focus, HIGH); // Focus..

        display.clearDisplay();   // clears the screen and buffer
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,20);
        display.println("Focus");
        display.display();
  
        delay(1000);
        
        display.clearDisplay();   // clears the screen and buffer
        display.display();
        
        digitalWrite(focus, LOW);

        break;

      case 's':

        digitalWrite(shoot, HIGH); // Shoot !!

        display.clearDisplay();   // clears the screen and buffer
        display.setTextSize(2);
        display.setTextColor(WHITE);
        display.setCursor(0,20);
        display.println("Shoot");
        display.display();
        
        delay(200);
        
        display.clearDisplay();   // clears the screen and buffer
        display.display();
        
        digitalWrite(shoot, LOW);

      break;

    }
  }
}
