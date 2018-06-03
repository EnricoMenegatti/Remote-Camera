
void ESP_Setup() 
{
  WiFi.softAP(ssid,pass);
  IPAddress IPserver = WiFi.softAPIP();
  Serial.print(" IP address server : ");
  Serial.println(IPserver);
  server.on("/",respond);
  server.begin();
  server.onNotFound([]()
  {
    //command=" ini data dari klien : ";
    command=server.uri();
    server.send(200,"text/plain",command);
  });

  Serial.println("Server setup");
}

void respond()
{
  server.send(200,"text/html","<h1>Remote Camera</h1>");
}

void ESP_Command() 
{
  //Serial.println("ESP_test");
  server.handleClient();
  
  if(last_command != command)
  {
    last_command = command;
    Serial.println(command);
    change_command = 1;
  }
}

