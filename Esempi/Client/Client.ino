/*
 *  This sketch sends a message to a TCP server
 *
 */

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

//ESP8266WiFiMulti WiFiMulti;

char ssid[] = "Remote-camera";           // SSID of your AP
char pass[] = "123456789";         // password of your AP

IPAddress server(192,168,4,1);     // IP address of the AP
WiFiClient client;

void setup() {
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFi.mode(WIFI_STA);
    //WiFiMulti.addAP("Remote-camera");
    
    WiFi.begin(ssid, pass);           // connects to the WiFi AP
    Serial.println();
    Serial.println("Connection to the AP");
    while (WiFi.status() != WL_CONNECTED) 
    {
      Serial.print(".");
      delay(500);
    }

    Serial.println();
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
}


void loop() {
    client.connect(server, 80);

    // This will send the request to the server
    client.println("Send this data to server");

    //read back one line from server
    String line = client.readStringUntil('\r');
    Serial.println(line);

    Serial.println("closing connection");
    client.stop();
    
    //Serial.println("wait 5 sec...");
    delay(1000);
}

