

#include <Arduino.h>
#include <EEPROM.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

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

const int p_laser = 2;
const int p_DT = 3;//ENCODER
const int p_CLK = 4;//ENCODER
const int p_SW = 5;//ENCODER
const int p_audio = 7;
const int p_focus = 8;
const int p_shoot = 9;
const int p_TX = 10;
const int p_RX = 11;

Encoder myEnc(p_DT, p_CLK);

const char *ssid = "Remote-camera";
const char *pass = "123456789";
String command, last_command;
ESP8266WebServer server(80);

volatile boolean audio_ok, laser_ok;
volatile unsigned long time_1, time_2, time_0;

boolean selezione_ok;
int modalita, laser, t_pulsante, t_focus, t_shoot, i, EE_ind;
int Enc_cont, oldPosition  = -999, newPosition;

long this_time, last_time;

unsigned long d_focus, d_shoot, d_laser, d_audio;

char c[8];

SoftwareSerial mySerial(p_RX, p_TX); // RX, TX

void setup()
{

	Serial.begin(115200);
	mySerial.begin(115200);

	mySerial.println("Initializing I2C devices...");

  ESP_Setup();

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

	pinMode(p_audio, INPUT_PULLUP);
  pinMode(p_laser, INPUT_PULLUP);

  pinMode (p_CLK,INPUT);
  pinMode (p_DT,INPUT);
  pinMode (p_SW,INPUT);

	pinMode(p_focus, OUTPUT);
	pinMode(p_shoot, OUTPUT);

	//display.display(); //LOGO

	EE_ind = 0;
  EEPROM.get(EE_ind, modalita);
	EE_ind += sizeof(modalita);

  EEPROM.get(EE_ind, d_focus);
	EE_ind += sizeof(d_focus);

  EEPROM.get(EE_ind, d_shoot);
	EE_ind += sizeof(d_shoot);

  EEPROM.get(EE_ind, d_laser);
	EE_ind += sizeof(d_laser);

  EEPROM.get(EE_ind, d_audio);
	EE_ind += sizeof(d_audio);

  //mySerial.println(modalita);

  //Timer_2_Setup();
}

void loop()
{
  server.handleClient();
	switch (modalita)
	{
    case 0: //PAGINA HOME

      Home();

    break;

		case 1: //SCATTO REMOTO

			Remoto();

		break;

		case 2: //TIMELAPSE

			Lapse();

		break;

		case 3: //FOTOTRAPPOLA LASER

			Laser();

		break;

		case 4: //FOTOTRAPPOLA AUDIO

			//Audio();
      modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		default:

			modalita = 0;

		break;
	}

  ESP_Test();
  
	save_ee();

}

//--------------------------FUNZIONI------------------------

void c_modo()
{
  if (c[0] == 'H')
  {
    modalita = 0;

    pagina_0();
    display.display();
  }

	if (c[0] == 'R')
	{
		modalita = 1;

		pagina_1();
		display.display();
	}

	else if (c[0] == 'T')
	{
		modalita = 2;

		pagina_2();
		display.display();
	}

	else if (c[0] == 'L')
	{
		modalita = 3;

		pagina_3();
		display.display();
	}

	else if (c[0] == 'A')
	{
		/*modalita = 4;

		pagina_4();
		display.display();*/
	}
}

void save_ee()
{

  EE_ind = 0;
  EEPROM.put(EE_ind, modalita);//scrive valore su eeprom solo se viene modificato
  EE_ind += sizeof(modalita);

  EEPROM.put(EE_ind, d_focus);
  EE_ind += sizeof(d_focus);

  EEPROM.put(EE_ind, d_shoot);
  EE_ind += sizeof(d_shoot);

  EEPROM.put(EE_ind, d_laser);
  EE_ind += sizeof(d_laser);

  EEPROM.put(EE_ind, d_audio);
  EE_ind += sizeof(d_audio);

}

void encoder(int Max, int Min)
{
  newPosition = myEnc.read();

  if (newPosition > oldPosition)
  {
    if (newPosition % 4 == 0)
      Enc_cont ++;

      if (Enc_cont > Max)
      Enc_cont = Min;

    oldPosition = newPosition;
  }

  else if (newPosition < oldPosition)
  {
    if (newPosition % 4 == 0)
      Enc_cont --;

      if (Enc_cont < Min)
      Enc_cont = Max;

    oldPosition = newPosition;
  }
}

void selezione(long var, int x, int y)//FUNZIONE PER CREARE LINEA DI SELEZIONE SOTTO A VARIABILE. SI UTILIZZA "dim_var".
{
	display.drawLine(x, y + 17, x + (11 * dim_var(var)), y + 17, WHITE); //LINEA ORIZZONTALE SOTTO A VARIABILE
}

int dim_var(long var)//FUNZIONE PER DETERMINARE LUNGHEZZA VARIABILE
{
  if (var >= 0 && var < 10)//0-9ms = 1 CIFRA
    return 1;

  else if (var >= 10 && var < 100)//10-99ms = 2 CIFRE
    return 2;

  else if (var >= 100 && var < 1000)//100-999ms = 3 CIFRE
    return 3;

  else if (var >= 1000 && var < 10000)//1000-9999ms = 4 CIFRE
    return 4;

  else if (var >= 10000 && var < 100000)//10000-99999ms = 5 CIFRE
    return 5;
}

void Aumento_var(long var, int page)
{
  Enc_cont = var;
  mySerial.print("aumento");
  
  while(1)
  {
    newPosition = myEnc.read();

    if (digitalRead(p_SW) == 0)
    {
      
      while (digitalRead(p_SW) == 0);//ATTENDO RILASCIO

      save_ee();
      pagina_3();
      display.display();
      return;
    }
    
    else if (newPosition > oldPosition)
    {
      if (newPosition % 4 == 0)
        Enc_cont ++;
  
      oldPosition = newPosition;
    }
  
    else if (newPosition < oldPosition)
    {
      if (newPosition % 4 == 0)
        Enc_cont --;
  
      oldPosition = newPosition;
    }

    if (page == 3)
    {
      d_laser = Enc_cont;

      pagina_3();
      selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
      display.display();
    }
    
    if (page == 4)
    {
      d_audio = Enc_cont;

      pagina_4();
      selezione(d_audio, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
      display.display();
    }
  }
}

void linee_mancanti(int X, int Y)
{
  display.drawLine(X - 1, Y - 1, X + 17, Y - 1, WHITE); //LINEE ORIZZONTALI
  display.drawLine(X - 2, Y - 2, X + 17, Y - 2, WHITE);
  display.drawLine(X - 3, Y - 3, X + 17, Y - 3, WHITE);
  display.drawLine(X - 1, Y - 1, X - 1, Y + 23, WHITE); //LINEE VERTICALI
  display.drawLine(X - 2, Y - 2, X - 2, Y + 23, WHITE);
  display.drawLine(X - 3, Y - 3, X - 3, Y + 23, WHITE);
}
