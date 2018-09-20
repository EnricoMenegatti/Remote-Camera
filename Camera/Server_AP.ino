
void ESP_Setup() 
{
  WiFi.softAPConfig(IP, GTW, mask);
  WiFi.softAP(ssid, pass);

  Serial.println();
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  webSocket.begin();                 // start the websocket server
  webSocket.onEvent(webSocketEvent); // if there's an incomming websocket message, go to function 'webSocketEvent'

  Start_Server();
  /*server.on("/",Respond);
  server.on("/H+",Home);
  server.on("/R+",Remoto);
  server.on("/A+",Audio);
  server.on("/L+",Laser);
  server.on("/T+",Lapse);
  server.on("/S+",Slider);
  server.onNotFound([]()
  {
    command = server.uri();
    server.send(200,"text/plain",command);
  });
  server.begin();*/
  
  Serial.println("Server setup OK");
}

void Start_Server() // Start a HTTP server with a file read handler and an upload handler
{
  server.on("/Edit.html", HTTP_POST, []() 
  {
    server.send(200, "text/plain", "");
  }, handleFileUpload); // go to 'handleFileUpload'
  
  server.onNotFound(handleNotFound); // if someone requests any other file or page, go to function 'handleNotFound'
                                     // and check if the file exists
  server.begin(); // start the HTTP server
}

void handleNotFound() // if the requested file or page doesn't exist, return a 404 not found error
{
  if(!handleFileRead(server.uri())) // check if the file exists in the flash memory (SPIFFS), if so, send it
  {
    server.send(404, "text/plain", "404: File Not Found");
  }
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t lenght) { // When a WebSocket message is received
  switch (type) 
  {
    case WStype_DISCONNECTED:             // if the websocket is disconnected
      Serial.printf("[%u] Disconnected!\n", num);
    break;
      
    case WStype_CONNECTED: 
    {              // if a new websocket connection is established
      IPAddress ip = webSocket.remoteIP(num);
      Serial.printf("[%u] Connected from %d.%d.%d.%d url: %s\n", num, ip[0], ip[1], ip[2], ip[3], payload);
    }
    break;
    
    case WStype_TEXT:                     // if new text data is received

      char* c2;
      c2 = ((char*) &payload);
      strcpy(c, c2);
      /*for (int i = 0; i > 7; i++)
      {
        c[i] = (char) &payload[i];
      }*/
      
      Serial.printf("[%u] get Text: %s\n", num, payload);
      Serial.printf("%s",c2);
    break;
  }
}

String getContentType(String filename) // determine the filetype of a given filename, based on the extension
{ 
  if (filename.endsWith(".html")) return "text/html";
  else if (filename.endsWith(".css")) return "text/css";
  else if (filename.endsWith(".js")) return "application/javascript";
  else if (filename.endsWith(".ico")) return "image/x-icon";
  else if (filename.endsWith(".gz")) return "application/x-gzip";
  return "text/plain";
}

/*void handleHome()
{
  Serial.println("handle Home");
}*/

void ESP_Command() 
{
  webSocket.loop();
  server.handleClient();
  
  if(last_command != command)
  {
    last_command = command;
    Serial.println(command);
    change_command = 1;
  }
}
