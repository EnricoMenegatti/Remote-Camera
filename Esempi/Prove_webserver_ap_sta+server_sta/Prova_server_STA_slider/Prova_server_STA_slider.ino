/*
 *  This sketch demonstrates how to set up a simple HTTP-like server.
 *  The server will set a GPIO pin depending on the request
 *    http://server_ip/gpio/0 will set the GPIO2 low,
 *    http://server_ip/gpio/1 will set the GPIO2 high
 *  server_ip is the IP address of the ESP8266 module, will be 
 *  printed to Serial when the module is connected.
 */

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiClient.h>

const char* ssid = "Remote-camera";
const char* password = "your-password";
const char *camera = "192.168.4.1";

String command;

IPAddress IP(192,168,4,2);
IPAddress GTW(192,168,4,1);
IPAddress mask(255,255,255,0);
IPAddress DNS(192,168,4,1);

ESP8266WebServer server(80);

void Home() 
{
  server.send(200, "text/html", "<html><body><h1>MyESPAP Home Page</h1>\r\n<a href=\"/frate\">Fast Rate</a><br>\r\n<a href=\"/srate\">Slow Rate</a><br><h2 href=\"/Msg\">num from client = </h2><br>\r\n</body></html>");
}

void Blink() 
{
  Serial.print("connecting to ");
  Serial.println(camera);
  WiFiClient client;
  const int httpPort = 80;
  while (!client.connect(camera, httpPort)) 
  {
    delay(200);
    Serial.print(".");
  }
  String url = "/OK";
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Host: " + camera + "\r\n" + "Connection: close\r\n\r\n");
  Serial.println();
  Serial.print("Risposta: ");
  Serial.println(url);
  client.stop();
  
  while(1)
  {
    server.handleClient();
    yield();
    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
                                      // but actually the LED is on; this is because 
                                      // it is active low on the ESP-01)
    delay(500);                      // Wait for a second
    digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
    delay(500);                      // Wait for two seconds (to demonstrate the active low LED)
  }
}

void setup() 
{
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.config(IP, DNS, GTW, mask);
  WiFi.begin(ssid);
  
  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  
  // Start the server
  server.on("/", Home);
  server.on("/blink", Blink);
  server.begin();
  server.onNotFound([]()
  {
    //command=" ini data dari klien : ";
    command = server.uri();
    server.send(200,"text/plain",command);
  });
  
  Serial.println("Server started");

  // Print the IP address
  Serial.print("STA IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() 
{
  server.handleClient();
  // Check if a client has connected
  /*WiFiClient client = server.available();
  if (!client) {
    return;
  }
  
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  
  // Read the first line of the request
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  // Match the request
  int val;
  if (req.indexOf("/gpio/0") != -1)
    val = 0;
  else if (req.indexOf("/gpio/1") != -1)
    val = 1;
  else {
    Serial.println("invalid request");
    client.stop();
    return;
  }

  // Set GPIO2 according to the request
  digitalWrite(2, val);
  
  client.flush();

  // Prepare the response
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\nGPIO is now ";
  s += (val)?"high":"low";
  s += "</html>\n";

  // Send the response to the client
  client.print(s);
  delay(1);
  Serial.println("Client disonnected");

  // The client will actually be disconnected 
  // when the function returns and 'client' object is detroyed*/
}

