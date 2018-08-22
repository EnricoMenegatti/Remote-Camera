
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char *ssid = "Vodafone-Menegatti";
const char *password = "Menegatti13";
const char *host = "192.168.4.2";

const char *ssid1 = "Remote-camera";
const char *password1 = "MyPasswordSERVER";
const char *host1 = "10.10.10.1";
ESP8266WebServer server(80);

int led = 2;
int blink_count = 0;
int blink_rate = 250;
int value_from_client = 0;
String client_to_server = "";

void handleRoot() 
{
  server.send(200, "text/html", "<html><body><h1>MyESPAP Home Page</h1>\r\n<a href=\"/frate\">Fast Rate</a><br>\r\n<a href=\"/srate\">Slow Rate</a><br><h2 href=\"/Msg\">num from client = </h2><br>\r\n</body></html>");
}

void handleMSG() 
{
  blink_rate =250;
  String num_from_client = server.arg("ClientNum"); 
  server.send(200, "text/html", "<html><head><script>window.onload =  function() { setInterval(function() {window.location.replace('/');}, 1000); };</script></head><body><h1>MSG mode</h1>Got " + num_from_client + " from client</body></html>");
  //Serial.println(num_from_client);
  String cloud = "AT#DWSEND=0,property.publish,key,gas,value," + num_from_client;
  Serial.println(cloud);
  delay(5);
  client_to_server = num_from_client;
  value_from_client=(num_from_client.toInt());
  //Serial.println(value_from_client);
}

int rate_toogle = 0;
int client_num_val = 0;

void setup() 
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  WiFi.softAP(ssid1); //access point generato
  Serial.println(WiFi.localIP());
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.mode(WIFI_AP_STA);
  WiFi.begin(ssid, password); //wifi a cui si deve connettere
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
   server.on("/Msg", handleMSG);
  server.begin();
}


void loop() {
  server.handleClient();
  delay(8000);
  if (rate_toogle == 0)
    rate_toogle = 1;
  else
    rate_toogle = 0;
  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
//  String url = "/frate";  
//  if (rate_toogle == 0)
//    url = "/srate";
//  Serial.print("Requesting URL: ");
//  Serial.println(url);
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
//  delay(10);
//    while(client.available()){
//    String line = client.readStringUntil('\r');
//    Serial.print(line);
//      }
int sensorValue = digitalRead(2);
Serial.println(sensorValue);
if(sensorValue==1)
{
   client_num_val = (sensorValue + client_num_val);
  Serial.println(client_num_val);
  }


  //String url1 = "/Msg";
  String url1 = "/gpio/1";
  //url1 = url1 + "?ClientNum=" + client_to_server;
  //url1 = url1 + " ?ClientNum= " + String(sensorValue);
  Serial.print("Requesting URL: ");
  Serial.println(url1);
  client.print(String("GET ") + url1 + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(10);
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
}
