
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char *ssid = " Remote-camera";
const char *pass = "123456789";
String command, last_command;
ESP8266WebServer server(80);

void respond(){
  server.send(200,"text/html","<h1>Anda sudah terkoneksi</h1>");
}

void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(BUILTIN_LED,OUTPUT);
Serial.println(" memulai konfigurasi aksees Point");
WiFi.softAP(ssid,pass);
IPAddress IPserver = WiFi.softAPIP();
Serial.println(" IP address server : ");
Serial.println(IPserver);
server.on("/",respond);
server.begin();
server.onNotFound([](){
  //command=" ini data dari klien : ";
  command=server.uri();
  server.send(200,"text/plain",command);
});
}

void loop() 
{
  // put your main code here, to run repeatedly:
  server.handleClient();
  
  if(last_command != command)
  {
    last_command = command;
    Serial.println(last_command);
  }
}
