#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>

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

SoftwareSerial mySerial(11, 10); // RX, TX

const int p_focus = 8;
const int p_shoot = 9;

int serial = 0;
int d_shoot;

char c[8];
int i = 0;

void clean()
{

  display.clearDisplay();   // clears the screen and buffer
  display.display();
  
}

void ciclo()
{

  if (c[0] && c[1] == "FF")
  {
    digitalWrite(p_focus, HIGH); // Focus..

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Focus");
    mySerial.println("Focus");
    display.display();

    delay(1000);
    
    clean();
    
    digitalWrite(p_focus, LOW);

  }

  if (c[0] && c[1] == 'SS')
  {
    digitalWrite(p_shoot, HIGH); // Shoot !!

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Shoot");
    mySerial.println("Shoot");
    display.display();
    
    delay(d_shoot);
    
    clean();
    
    digitalWrite(p_shoot, LOW);
  }

  if (c[0] && c[1] == 'FS')
  {
    digitalWrite(p_focus, HIGH); // Focus..

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Focus");
    mySerial.println("Focus");
    display.display();

    delay(1000);
    
    digitalWrite(p_focus, LOW);

    digitalWrite(p_shoot, HIGH); // Shoot !!

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Shoot");
    mySerial.println("Shoot");
    display.display();
    
    delay(d_shoot);
    
    clean();
    
    digitalWrite(p_shoot, LOW);
  }
}

void setup()   
{  
  
  #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
      Wire.begin();
  #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
      Fastwire::setup(400, true);
  #endif

  Serial.begin(19200);
  mySerial.begin(19200);

  mySerial.println("Initializing I2C devices...");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  pinMode(p_focus, OUTPUT);
  pinMode(p_shoot, OUTPUT);

  clean();

}

void loop() 
{

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println(c);
    display.display();
    ciclo();
    
  if (mySerial.available() > 0)
  {
    // Reading incoming bytes :
    c[i] = mySerial.read();

    i = i + 1;

    if (i == 8)
    {
      ciclo();
      i = 0;
    }
  }
}
