#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2

const int p_focus = 8;
const int p_shoot = 9;
const int p_TX = 10;
const int p_RX = 11;
const int p_micro = A3;

int modalita;
int d_focus, d_shoot;
int micro = 0;

char c[8];
int i = 0;

SoftwareSerial mySerial(p_RX, p_TX); // RX, TX

void setup()   
{  

  Serial.begin(19200);
  mySerial.begin(19200);

  mySerial.println("Initializing I2C devices...");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  pinMode(p_focus, OUTPUT);
  pinMode(p_shoot, OUTPUT);

}

void loop() 
{
  switch (modalita)
  {

    case 1:
    break;

    case 2:
    break;

    case 3:
    break;

    case 4:
    break;

    defaul:
  }

  micro = analogRead(p_micro); 

  display.clearDisplay();   // clears the screen and buffer
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println(micro);
  display.display();
    
  if (mySerial.available() > 0)
  {
    // Reading incoming bytes :
    c[i] = mySerial.read();

    i = i + 1;

    if (c[i] == '*') //FINE STRINGA
    {
      ciclo();
      i = 0;
    }
  }
}

//--------------------------FUNZIONI------------------------
void ciclo()
{

  if (c[0] == 'F')
  {
    if (c[1] == 'F') //FOCUS
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
    }

    if (c[1] == 'S') //FOCUS + SHOOT
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

      digitalWrite(p_shoot, LOW);
    }
  }

  if (c[0] == 'S')
  {
    if (c[0] == 'S') //SHOOT
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
      
      digitalWrite(p_shoot, LOW);
    }  
  }
}

