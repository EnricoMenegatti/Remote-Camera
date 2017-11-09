#include <SPI.h>
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
const int p_laser = A2;
const int p_micro = A3;

int modalita = 1;
unsigned long d_focus, d_shoot;
int micro, laser, mul_d;

char c[8];
int i;

SoftwareSerial mySerial(p_RX, p_TX); // RX, TX

void setup()   
{  

  Serial.begin(19200);
  mySerial.begin(19200);
  
  mySerial.println("Initializing I2C devices...");

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)
  // init done

  pinMode(p_focus, OUTPUT);
  pinMode(p_shoot, OUTPUT);

}

void loop() 
{
  switch (modalita)
  {
    case 1: //SCATTO REMOTO

      if (mySerial.available() > 0)
      {

        i = i + 1;
        
        // Reading incoming bytes :
        c[i-1] = mySerial.read();

        if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
        {
          c_modo();
          i = 0;
        }
        else if (c[i-1] == '*') //FINE STRINGA E CICLO
        {
          scatto();
          i = 0;
        }
      }
  
    break;

    case 2: //TIMELAPSE

      if (mySerial.available() > 0)
      {

        i = i + 1;
        
        // Reading incoming bytes :
        c[i-1] = mySerial.read();

        if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
        {
          c_modo();
          i = 0;
        }
        else if (c[i-1] == '*') //FINE STRINGA E CICLO
        {

          i = 0;
        }
      }
      
    break;

    case 3: //FOTOTRAPPOLA LASER

      if (mySerial.available() > 0)
      {

        i = i + 1;
        
        // Reading incoming bytes :
        c[i-1] = mySerial.read();

        if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
        {
          c_modo();
          i = 0;
        }
        else if (c[i-1] == '*') //FINE STRINGA E CICLO
        {
          
          i = 0;
        }
      }

      laser = analogRead(p_laser); 

      display.clearDisplay();   // clears the screen and buffer
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,20);
      display.println(laser);
      display.display();
      
    break;

    case 4: //FOTOTRAPPOLA ACUSTICA

      if (mySerial.available() > 0)
      {

        i = i + 1;
        
        // Reading incoming bytes :
        c[i-1] = mySerial.read();

        if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
        {
          c_modo();
          i = 0;
        }
        else if (c[i-1] == '*') //FINE STRINGA E CICLO
        {
          
          i = 0;
        }
      }
      
      micro = analogRead(p_micro); 

      display.clearDisplay();   // clears the screen and buffer
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,20);
      display.println(micro);
      Serial.println(micro);
      display.display();
      
    break;

    //defaul:
  } 
}

//--------------------------FUNZIONI------------------------

void c_modo()
{
  if (c[0] == 'S')
  {
    modalita = 1;
  }

  else if (c[0] == 'T')
  {
    modalita = 2;
  }

  else if (c[0] == 'L')
  {
    modalita = 3;
  }

  else if (c[0] == 'A')
  {
    modalita = 4;
  }
}

void scatto()
{
  if (c[0] == 'F' && c[1] == 'F') //FOCUS
  {

    if (c[2] != '-') //IMPOSTA TEMPO FUOCO
    {
      d_focus = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

      if (c[6] == 'm')
      {
        mul_d = 1;
      }
      else if (c[6] == 'S')
      {
        mul_d = 1000;
      }
      else if (c[6] == 'M')
      {
        mul_d = 60000;
      }

      d_focus = d_focus * mul_d; //TRASFORMA IN MILLISECONDI
    }

    display.clearDisplay();   // clears the screen and buffer
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Focus");
    mySerial.println("Focus");
    display.display();
    
    digitalWrite(p_focus, HIGH); // Focus..  
    
    if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
    {
      delay(d_focus);
    }
    else //FUOCO CON TEMPO STANDARD
    {
      delay(1000);
    } 
    
    digitalWrite(p_focus, LOW);
  }

  if (c[0] == 'F' && c[1] == 'S') //FOCUS //FOCUS + SHOOT
  {
    
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Focus");
    mySerial.println("Focus");
    display.display();
    
    digitalWrite(p_focus, HIGH); // Focus.. 
    delay(1000);      

    display.clearDisplay(); 
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Shoot");
    mySerial.println("Shoot");
    display.display();
    
    digitalWrite(p_shoot, HIGH); // Shoot !!     
    delay(50);
    digitalWrite(p_focus, LOW);
    digitalWrite(p_shoot, LOW);
  }


  if (c[0] == 'S' && c[1] == 'S') //SHOOT
  {
    if (c[2] != '-') //IMPOSTA TEMPO BULB
    {
      d_shoot = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
      
      if (c[6] == 'm')
      {
        mul_d = 1;
      }
      else if (c[6] == 'S')
      {
        mul_d = 1000;
      }
      else if (c[6] == 'M')
      {
        mul_d = 60000;
      }

      d_shoot = d_shoot * mul_d; //TRASFORMA IN MILLISECONDI

    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(WHITE);
    display.setCursor(0,20);
    display.println("Shoot");
    mySerial.println("Shoot");
    display.display();

    digitalWrite(p_focus, HIGH);
    digitalWrite(p_shoot, HIGH); // Shoot !!
    
    if (c[2] != '-') //SCATTA CON TEMPO BULB
    {
      delay(d_shoot);
    }
    else //SCATTA CON TEMPO MACCHINA
    {
      delay(100);
    }
    
    digitalWrite(p_shoot, LOW);
    digitalWrite(p_focus, LOW);
   
  }
}

