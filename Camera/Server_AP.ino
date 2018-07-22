
void ESP_Setup() 
{
  WiFi.softAPConfig(IP, GTW, mask);
  WiFi.softAP(ssid, pass);

  Serial.println();
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  server.on("/",Respond);
  server.on("/H+",Home);
  server.on("/R+",Remoto);
  server.on("/A+",Audio);
  server.on("/L+",Laser);
  server.on("/T+",Lapse);
  server.on("/S+",Slider);
  server.begin();
  server.onNotFound([]()
  {
    command = server.uri();
    server.send(200,"text/plain",command);
  });

  Serial.println("Server setup OK");
}

void Respond()
{
  server.send(200,"text/html","<h1>Remote Camera</h1>");
}

/*void handleHome()
{
  Serial.println("handle Home");
}*/

void ESP_Command() 
{
  server.handleClient();
  
  if(last_command != command)
  {
    last_command = command;
    Serial.println(command);
    change_command = 1;
  }
}

