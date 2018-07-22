
void ESP_Setup() 
{
  WiFi.softAPConfig(IP, GTW, mask);
  WiFi.softAP(ssid);

  Serial.println();
  Serial.print("AP SSID: ");
  Serial.println(ssid);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());
  
  /*Serial.println();
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
  Serial.println("WiFi connected");*/
  
  server.on("/",Respond);
  server.begin();
  server.onNotFound([]()
  {
    command = server.uri();
    server.send(200,"text/plain",command);
  });

  Serial.print("STA IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Server setup OK");
}

void Respond()
{
  server.send(200,"text/html","<h1>Sider</h1>");
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

