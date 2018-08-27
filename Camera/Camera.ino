
#include <Arduino.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>

#define ESP8266

#define ENCODER_USE_INTERRUPTS

#define OLED_RESET 3
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

const int p_laser = D0;
const int p_DT = D7;//ENCODER
const int p_CLK = D6;//ENCODER
const int p_SW = D5;//ENCODER
const int p_audio = D8;
const int p_focus = D3;
const int p_shoot = D4;

Encoder myEnc(p_DT, p_CLK);

const char* ssid = "Remote-camera";
const char* pass = "123456789";
const char* slider = "192.168.4.2";
String command, last_command, myStr;

IPAddress IP(192,168,4,1);
IPAddress GTW(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);

volatile boolean audio_ok, laser_ok;
volatile unsigned long time_1, time_2, time_0;

boolean selezione_ok, change_command;
int modalita, laser, t_pulsante, t_focus, t_shoot, i, EE_ind;
int Enc_cont, oldPosition  = -999, newPosition;

long this_time, last_time;

unsigned long d_focus, d_shoot, d_laser, d_audio, prev_millis, curr_millis;

char c[8];

void setup()
{

	Serial.begin(115200);

  Serial.println("Setup...");

  ESP_Setup();

	display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

	pinMode(p_audio, INPUT_PULLUP);
  pinMode(p_laser, INPUT_PULLUP);

  pinMode (p_CLK,INPUT);
  pinMode (p_DT,INPUT);
  pinMode (p_SW,INPUT_PULLUP);

	pinMode(p_focus, OUTPUT);
	pinMode(p_shoot, OUTPUT);

	//display.display(); //LOGO

  EEPROM.begin(512);
	Eeprom_read();

  //Serial.println(modalita);

  //Timer_2_Setup();

  Serial.println("Setup OK!");
}

void loop()
{
	switch (modalita)
	{
    case 0: //PAGINA HOME

      Home();

    break;

		case 1: //SCATTO REMOTO

		  Remoto();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		case 2: //TIMELAPSE

			Lapse();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		case 3: //FOTOTRAPPOLA LASER

			Laser();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		case 4: //FOTOTRAPPOLA AUDIO

			Audio();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

    case 5: //SLIDER

      Slider();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

    break;

		default:

			modalita = 0;

		break;
	}
  
	Eeprom_save();

  curr_millis = millis();
  if(curr_millis - prev_millis >= 1000) 
  {
    prev_millis = curr_millis;
    Serial.println("loop");
  }
  
  ESP_Command();
}

//--------------------------FUNZIONI------------------------

void c_modo()
{
  Serial.println("Cambio modo");

	if (c[0] == 'R')
	{
		modalita = 1;

		pagina(1);
		display.display();
	}

	else if (c[0] == 'T')
	{
		modalita = 2;

		pagina(2);
		display.display();
	}

	else if (c[0] == 'L')
	{
		modalita = 3;

		pagina(3);
		display.display();
	}

	else if (c[0] == 'A')
	{
		/*modalita = 4;

		pagina(4);
		display.display();*/
	}  
 
	else //if (c[0] == 'H')
  {
    modalita = 0;

    pagina(0);
    display.display();
  }
}

void encoder(int Max, int Min)
{
  newPosition = myEnc.read();

  if (newPosition > oldPosition)
  {
    if (newPosition % 4 == 0)
      Enc_cont ++;
      //Serial.print(Enc_cont);
      
      if (Enc_cont > Max)
      Enc_cont = Min;

    oldPosition = newPosition;
  }

  else if (newPosition < oldPosition)
  {
    if (newPosition % 4 == 0)
      Enc_cont --;
      //Serial.print(Enc_cont);
      
      if (Enc_cont < Min)
      Enc_cont = Max;

    oldPosition = newPosition;
  }
}

void verifica_comando()
{
  myStr = command.substring(1,8);
  myStr.toCharArray(c,9);
  Serial.println(c[0]);
  change_command = 0;

  for(int j = 0; j < 8; j++)
  {
    if (c[j] == '+') //FINE STRINGA E CAMBIO MODALITA'
    {
      c_modo();
    }
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
  Serial.println("aumento");
  
  while(1)
  {
    newPosition = myEnc.read();

    if (digitalRead(p_SW) == 0)
    {
      
      while (digitalRead(p_SW) == 0)//ATTENDO RILASCIO
      {
        yield();
      }

      Eeprom_save();
      pagina(3);
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

      pagina(3);
      selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
      display.display();
    }
    
    if (page == 4)
    {
      d_audio = Enc_cont;

      pagina(4);
      selezione(d_audio, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
      display.display();
    }
  yield();
  }
}

