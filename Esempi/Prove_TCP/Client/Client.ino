/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>

//ESP8266WiFiMulti WiFiMulti;

char ssid[] = "Remote-camera";           // SSID of your AP
char pass[] = "123456789";         // password of your AP

int ledPin = 2;

IPAddress server(192,168,4,1);     // IP address of the AP
WiFiClient client;

void setup() 
{
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);

  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid);           // connects to the WiFi AP
  Serial.println();
  Serial.println("Connection to the AP");
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() 
{
  client.connect(server, 80);

  digitalWrite(ledPin, LOW);

  // This will send the request to the server
  client.println("Send data\r");

  //read back one line from server
  String line = client.readStringUntil('\r');
  Serial.println(line);
  
  client.flush();

  Serial.println("closing connection");
  Serial.println("********************************");
  client.stop();

  digitalWrite(ledPin, HIGH);
  
  delay(1000);
}

