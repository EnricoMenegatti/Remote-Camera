
#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>

const char* ssid = "Remote-camera";
const char* password = "thereisnospoon";

int ledPin = 2;

IPAddress IP(192,168,4,1);
IPAddress mask = (255, 255, 255, 0);

WiFiServer server(80);

void setup() 
{
  Serial.begin(115200);

  Serial.println();
  Serial.println("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAP(ssid);
  WiFi.softAPConfig(IP, IP, mask);
  server.begin();
  
  pinMode(ledPin, OUTPUT);
  
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  Serial.println("HTTP server started");
}

void loop() 
{
  // Check if a client has connected
  WiFiClient client = server.available();
  if (client) 
  {
    digitalWrite(ledPin, LOW);
    
    // Read the first line of the request
    String req = client.readStringUntil('\r');
    Serial.println(req);
    
    client.flush();
    
    client.println(req + "_OK" + "\r");
    Serial.println("********************************");
    
    digitalWrite(ledPin, HIGH);
  }
}
