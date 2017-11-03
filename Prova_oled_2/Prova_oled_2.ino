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

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

const int focus = 8;
const int shoot = 9;

int serial = 0;

void clean()
{

  display.clearDisplay();   // clears the screen and buffer
  display.display();
  
}

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
  
  clean();

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
        
        //clean();
        
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
        
        //clean();
        
        digitalWrite(shoot, LOW);

      break;

    }
  }
}
