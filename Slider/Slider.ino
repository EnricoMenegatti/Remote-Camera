
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const int pDir = D4;
const int pStep = D3;

const char* ssid = "Remote-camera";
const char* password = "123456789";
const char* camera = "192.168.4.1";
String command, last_command, myStr, S_Dir, S_Vel, S_Step;

IPAddress IP(192,168,4,2);
IPAddress GTW(192,168,4,1);
IPAddress mask(255,255,255,0);
IPAddress DNS(192,168,4,1);

ESP8266WebServer server(80);

boolean change_command;
 
const int numStepMotore = 200; //E' il numero di step per rotazione del motore (potrebbe differire in base al modello)
const long velocita = 500; //Si tratta di microsecondi tra un impulso e l'altro sul pin STEP
 
void setup() 
{
  Serial.begin(115200);

  ESP_Setup();
  
  pinMode(pStep, OUTPUT);
  pinMode(pDir, OUTPUT);
}

void loop() 
{
  ESP_Command();
  if(change_command == 1)
    Verifica_Comando();
}

void Verifica_Comando()
{
  S_Dir = command.substring(1,2);//(from,to)
  S_Vel = command.substring(3,7);//(from,to)
  S_Step = command.substring(8);//(from,to)
  //myStr.toCharArray(c,9);
  //Serial.println(c[0]);
  change_command = 0;

  Serial.println(S_Dir);
  Serial.println(S_Vel);
  Serial.println(S_Step);
}


  
