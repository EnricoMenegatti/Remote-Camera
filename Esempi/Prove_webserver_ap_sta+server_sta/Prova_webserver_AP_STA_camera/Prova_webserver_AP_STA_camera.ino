
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char *ssid = "Remote-camera";
const char *slider = "192.168.4.2";

IPAddress IP(192,168,4,1);
IPAddress GTW(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

ESP8266WebServer server(80);

int cont = 0;
String command;

void Home() 
{
  server.send(200, "text/html", "<html><body><h1>MyESPAP Home Page</h1>\r\n<a href=\"/frate\">Fast Rate</a><br>\r\n<a href=\"/srate\">Slow Rate</a><br><h2 href=\"/Msg\">num from client = </h2><br>\r\n</body></html>");
}

void Blink() 
{
  while(1)
  {
    server.handleClient();
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                      // but actually the LED is on; this is because 
                                      // it is active low on the ESP-01)
    delay(1000);                      // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(1000);                      // Wait for two seconds (to demonstrate the active low LED)
  }
}


int rate_toogle = 0;
int client_num_val = 0;

void setup() 
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  
  WiFi.softAPConfig(IP, GTW, mask);
  WiFi.softAP(ssid); //access point generato

  Serial.println();
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/", Home);
  server.on("/blink", Blink);
  server.begin();
  server.onNotFound([]()
  {
    //command=" ini data dari klien : ";
    command = server.uri();
    server.send(200,"text/plain",command);
    Serial.println(command);
  });
  
  Serial.println("HTTP WebServer started");
}

void loop() {
  server.handleClient();
  
  WiFiClient client;
  const int httpPort = 80;
  while (!client.connect(slider, httpPort)) 
  {
    delay(200);
    Serial.print(".");
  }
  
  if (cont == 0) 
  {
    String url = "/blink";
    Serial.println();
    Serial.print("Requesting URL: ");
    Serial.println(url);
    client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + slider + "\r\n" + "Connection: close\r\n\r\n");
    delay(10);
    
    cont = 1;
  }
  client.stop();

  while(client.available())
  {
    String line = client.readStringUntil('\r');
    Serial.println(line);
  }
  /*delay(8000);
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
  Serial.println("closing connection");*/
}
