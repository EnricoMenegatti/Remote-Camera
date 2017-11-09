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

/*static const unsigned char PROGMEM page_1[] =
{ B11111111, B00000000,
  B11111111, B00000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11000000, B11000000,
  B11111111, B00000000,
  B11111111, B00000000,
  B11001100, B00000000,
  B11001100, B00000000,
  B11000011, B00000000,
  B11000011, B00000000,
  B11000000, B11000000,
  B11000000, B11000000};*/

const int p_focus = 8;
const int p_shoot = 9;
const int p_TX = 10;
const int p_RX = 11;
const int p_laser = A2;
const int p_micro = A3;

int modalita = 1;
unsigned long d_focus, d_shoot;
int micro, laser, mul_d, t_focus = 1, t_shoot = 100;

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
  
  display.clearDisplay();

  pagina_1();
  display.display();

}

void loop() 
{
  switch (modalita)
  {
    case 1: //SCATTO REMOTO

      pagina_1();
      
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

      pagina_2();
      
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

      pagina_3();
      
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

      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,20);
      display.println(laser);
      display.display();
      
    break;

    case 4: //FOTOTRAPPOLA ACUSTICA

      pagina_4();

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

      micro = micro / 10;
      micro = micro * 10;

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
      t_focus = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

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

      d_focus = t_focus * mul_d; //TRASFORMA IN MILLISECONDI
    }

    display.setTextColor(BLACK, WHITE);
    display.setTextSize(3);
    display.drawLine(36, 24, 54, 24, WHITE); //LINEE ORIZZONTALI
    display.drawLine(35, 23, 54, 23, WHITE);
    display.drawLine(34, 22, 54, 22, WHITE);
    display.drawLine(36, 24, 36, 48, WHITE); //LINEE VERTICALI
    display.drawLine(35, 23, 35, 48, WHITE);
    display.drawLine(34, 22, 34, 48, WHITE);
    display.setCursor(37,25);
    display.write(70);
    mySerial.println("Focus");
    
    digitalWrite(p_focus, HIGH); // Focus..  
    
    if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
    {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(33,53);
      display.println(t_focus);
      display.setCursor(50,53);
      display.println(c[6]);
      display.display();
      
      delay(d_focus);
    }
    else //FUOCO CON TEMPO STANDARD
    {
      t_focus = 1;
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(33,53);
      display.println(t_focus);
      display.setCursor(50,53);
      display.println(c[6]);
      display.display();
      
      delay(1000);
    } 

    pagina_1();
    display.display();
    
    digitalWrite(p_focus, LOW);
  }

  if (c[0] == 'F' && c[1] == 'S') //FOCUS //FOCUS + SHOOT
  {
    
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(3);
    display.drawLine(36, 24, 54, 24, WHITE); //LINEE ORIZZONTALI
    display.drawLine(35, 23, 54, 23, WHITE);
    display.drawLine(34, 22, 54, 22, WHITE);
    display.drawLine(36, 24, 36, 48, WHITE); //LINEE VERTICALI
    display.drawLine(35, 23, 35, 48, WHITE);
    display.drawLine(34, 22, 34, 48, WHITE);
    display.setCursor(37,25);
    display.write(70);
    mySerial.println("Focus");
    
    digitalWrite(p_focus, HIGH); // Focus.. 
    
    t_focus = 1;
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(33,53);
    display.println(t_focus);
    display.setCursor(50,53);
    display.println(c[6]);
    display.display();
      
    delay(1000); 

    display.setTextColor(BLACK, WHITE);
    display.setTextSize(3);
    display.drawLine(76, 24, 94, 24, WHITE); //LINEE ORIZZONTALI
    display.drawLine(75, 23, 94, 23, WHITE);
    display.drawLine(74, 22, 94, 22, WHITE);
    display.drawLine(76, 24, 76, 48, WHITE); //LINEE VERTICALI
    display.drawLine(75, 23, 75, 48, WHITE);
    display.drawLine(74, 22, 74, 48, WHITE);
    display.setCursor(77,25);
    display.write(83);
    mySerial.println("Shoot");
    
    digitalWrite(p_shoot, HIGH); // Shoot !!  

    t_shoot = 100;
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(73,53);
    display.println(t_shoot);
    display.setCursor(90,53);
    display.println(c[6]);
    display.display();
       
    delay(100);

    pagina_1();
    display.display();
    
    digitalWrite(p_focus, LOW);
    digitalWrite(p_shoot, LOW);
  }


  if (c[0] == 'S' && c[1] == 'S') //SHOOT
  {
    if (c[2] != '-') //IMPOSTA TEMPO BULB
    {
      t_shoot = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
      
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

      d_shoot = t_shoot * mul_d; //TRASFORMA IN MILLISECONDI

    }
    display.setTextColor(BLACK, WHITE);
    display.setTextSize(3);
    display.drawLine(76, 24, 94, 24, WHITE); //LINEE ORIZZONTALI
    display.drawLine(75, 23, 94, 23, WHITE);
    display.drawLine(74, 22, 94, 22, WHITE);
    display.drawLine(76, 24, 76, 48, WHITE); //LINEE VERTICALI
    display.drawLine(75, 23, 75, 48, WHITE);
    display.drawLine(74, 22, 74, 48, WHITE);
    display.setCursor(77,25);
    display.write(83);
    mySerial.println("Shoot");

    digitalWrite(p_focus, HIGH);
    digitalWrite(p_shoot, HIGH); // Shoot !!
    
    if (c[2] != '-') //SCATTA CON TEMPO BULB
    {
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(73,53);
      display.println(t_shoot);
      display.setCursor(90,53);
      display.println(c[6]);
      display.display();
      
      delay(d_shoot);
    }
    else //SCATTA CON TEMPO MACCHINA
    {
      t_shoot = 100;
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(73,53);
      display.println(t_shoot);
      display.setCursor(90,53);
      display.println(c[6]);
      display.display();
      
      delay(100);
    }

    pagina_1();
    display.display();
    
    digitalWrite(p_shoot, LOW);
    digitalWrite(p_focus, LOW);
   
  }
}

void pagina_1()
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(29,0);
  display.println("REMOTO");
  
  display.setTextSize(3);
  display.setCursor(37,25);
  display.write(70);
  display.setCursor(77,25);
  display.write(83);

}

void pagina_2()
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("TIMELAPSE");

}

void pagina_3()
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(20,0);
  display.println("LASER");

}

void pagina_4()
{

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(10,0);
  display.println("ACUSTICO");

}

