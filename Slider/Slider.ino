
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>
#include <AccelStepper.h>

#define ESP8266

const int pDir = D4;
const int pStep = D3;
const int pLed = 2;

const char* ssid = "Remote-camera";
const char* password = "123456789";
const char* ssid_AP = "Remote-slider";
const char* camera = "192.168.4.1";
String command, last_command, myStr, S_Dir, S_Vel, S_Step;

IPAddress IP(192,168,4,2);
IPAddress GTW(192,168,4,1);
IPAddress mask(255,255,255,0);
IPAddress DNS(192,168,4,1);

IPAddress IP_AP(192,168,3,1);
IPAddress GTW_AP(192,168,3,1);

ESP8266WebServer server(80);

AccelStepper stepper(1, pStep, pDir);

boolean change_command, toggle;
int run_step = 0;
 
void setup() 
{
  Serial.begin(115200);

  ESP_Setup();
  Stepper_Setup();

  pinMode(pLed, OUTPUT);
}

void loop() 
{
  //stepper.runSpeed();
  ESP_Command();
  if(change_command == 1)
    Verifica_Comando();

  if(run_step == 1)
  {
    //Serial.print("RUNNING...");
    stepper.runSpeed();
    //run_step = 0;
  }
}

void Verifica_Comando()
{
  Serial.println("Ver_comando");

  //if(command == "/favicon.ico")
    //goto ignora_comm;
    
  S_Dir = command.substring(1,2);//(from,to)
  S_Vel = command.substring(3,7);//(from,to)
  S_Step = command.substring(8);//(from,to)
  //myStr.toCharArray(c,9);
  //Serial.println(c[0]);

  Serial.println(S_Dir);
  Serial.println(S_Vel);
  Serial.println(S_Step);

  Stepper_Run(S_Dir, S_Vel, S_Step);
  
ignora_comm://etichetta di salto

  change_command = 0;
}



  
