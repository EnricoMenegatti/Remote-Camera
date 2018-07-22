/*  Accesspoint - station communication without router
 *  see: https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-class.rst
 *       https://github.com/esp8266/Arduino/blob/master/doc/esp8266wifi/soft-access-point-examples.rst
 *       https://github.com/esp8266/Arduino/issues/504
 *  Works with: station_bare_01.ino
 */ 


#include <ESP8266WiFi.h>

WiFiServer server(80);
IPAddress IP(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

byte ledPin = 2;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP("Remote-camera");
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  pinMode(ledPin, OUTPUT);
  Serial.println();
  Serial.println("accesspoint_bare_01.ino_AP_STA");
  Serial.println("Server started.");
  Serial.print("IP: ");     Serial.println(WiFi.softAPIP());
  Serial.print("MAC:");     Serial.println(WiFi.softAPmacAddress());
}

void loop() {
  WiFiClient client = server.available();
  //if (!client) {return;}
  if (client) 
  {
    digitalWrite(ledPin, LOW);
    String request = client.readStringUntil('\r');
    Serial.println("********************************");
    Serial.println("From the station: " + request);
    client.flush();
    Serial.print("Byte sent to the station: ");
    Serial.println(client.println(request + "ca" + "\r"));
    digitalWrite(ledPin, HIGH);
  }
  
}
