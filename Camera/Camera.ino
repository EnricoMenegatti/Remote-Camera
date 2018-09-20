 
#include <Arduino.h>
#include <EEPROM.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WebSocketsServer.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include <FS.h>

#define ESP8266

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
const int p_audio = D8;
const int p_focus = D3;
const int p_shoot = D4;

const char* HOME_ssid = "Vodafone-Menegatti";
const char* HOME_pass = "Menegatti13";
const char* ssid = "Remote-camera";
const char* pass = "123456789";
const char* slider = "192.168.4.2";

IPAddress IP(192,168,4,1);
IPAddress GTW(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

ESP8266WebServer server(80);
WebSocketsServer webSocket(81);
File fsUploadFile;

volatile boolean audio_ok, laser_ok;
volatile unsigned long time_1, time_2, time_0;

int modalita, laser, t_pulsante, t_focus, t_shoot, i, EE_ind;

long this_time, last_time;

unsigned long d_focus, d_shoot, d_laser, d_audio, prev_millis, curr_millis;

char c[8];

void setup()
{

	Serial.begin(115200);

  Serial.println("Setup...");

  ESP_Setup();
  //OTA_Setup();
  SPIFFS_Setup();

	pinMode(p_audio, INPUT_PULLUP);
  pinMode(p_laser, INPUT_PULLUP);

	pinMode(p_focus, OUTPUT);
	pinMode(p_shoot, OUTPUT);

  EEPROM.begin(512);
	Eeprom_read();

  Serial.println("Setup OK!");
  prev_millis = millis();
}

void loop()
{
  detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));
  
	switch (modalita)
	{
		case 3: //FOTOTRAPPOLA LASER

			Laser();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		case 4: //FOTOTRAPPOLA AUDIO

			Audio();
      //modalita = 0;//PROVISSORIO, FINO A FIX PIN PER AUDIO

		break;

		default:

			modalita = 0;

		break;
	}
  
	//Eeprom_save();

  curr_millis = millis();
  if(curr_millis - prev_millis >= 2000) 
  {
    prev_millis = curr_millis;
    Serial.println("loop");
  }
  
  webSocket.loop();
  //server.handleClient();
  ArduinoOTA.handle();
}

//--------------------------FUNZIONI------------------------

/*void verifica_comando()
{
  myStr = command.substring(1,8);
  myStr.toCharArray(c,9);
  Serial.println(c[0]);
  change_command = 0;
}*/

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
