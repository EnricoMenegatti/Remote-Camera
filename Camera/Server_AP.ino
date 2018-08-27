
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
  
  server.on("/",Respond);
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
  server.begin();
  
  Serial.println("Server setup OK");
}

void Respond()
{
  server.send(200,"text/html","<h1>Remote Camera</h1>");
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
      Serial.printf("[%u] get Text: %s\n", num, payload);
      if (payload[0] == '#') // we get RGB data
      {            
        uint32_t rgb = (uint32_t) strtol((const char *) &payload[1], NULL, 16);   // decode rgb data
      } 
      else if (payload[0] == 'R') 
      {                      // the browser sends an R when the rainbow effect is enabled

      } 
      else if (payload[0] == 'N') 
      {                      // the browser sends an N when the rainbow effect is disabled

      }
    break;
  }
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

