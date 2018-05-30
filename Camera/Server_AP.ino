
void ESP_Setup() 
{
  pinMode(BUILTIN_LED,OUTPUT);
  WiFi.softAP(ssid,pass);
  IPAddress IPserver = WiFi.softAPIP();
  Serial.println(" IP address server : ");
  Serial.println(IPserver);
  server.on("/",respond);
  server.begin();
  server.onNotFound([]()
  {
    //command=" ini data dari klien : ";
    command=server.uri();
    server.send(200,"text/plain",command);
  });
}

void respond()
{
  server.send(200,"text/html","<h1>Remote Camera</h1>");
}

void ESP_Test() 
{
  // put your main code here, to run repeatedly:
  
  if(last_command != command)
  {
    last_command = command;
    Serial.println(last_command);
  }
}

