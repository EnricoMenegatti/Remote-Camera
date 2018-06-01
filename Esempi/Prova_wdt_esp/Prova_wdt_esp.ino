#include <EEPROM.h>

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
/*
D0   = 16;
D1   = 5;
D2   = 4;
D3   = 0;
D4   = 2;
D5   = 14;
D6   = 12;
D7   = 13;
D8   = 15;
RX   = 3;
TX   = 1;*/

const int p_laser = D2;
const int p_DT = D3;//ENCODER
const int p_CLK = D4;//ENCODER
const int p_SW = D5;//ENCODER
const int p_audio = D6;
const int p_focus = D7;
const int p_shoot = D8;

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

void setup()
{
  
  Serial.begin(115200);
  Serial.println("Setup");

  ESP_Setup();

  Serial.println("Display");
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x64)

  Serial.println("pinmode");
  pinMode(p_audio, INPUT_PULLUP);
  pinMode(p_laser, INPUT_PULLUP);

  pinMode(p_CLK,INPUT);
  pinMode(p_DT,INPUT);
  pinMode(p_SW,INPUT);

  pinMode(p_focus, OUTPUT);
  pinMode(p_shoot, OUTPUT);
  
  EEPROM.begin(512);
  Eeprom_read();

}

void loop()
{
  server.handleClient();
  
  ESP_Test();

  Eeprom_save();

}


