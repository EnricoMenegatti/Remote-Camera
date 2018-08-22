
void ESP_Setup() 
{
   Serial.println("Server setup");
  //--------------------Genera Access Point-------------------------------
  WiFi.softAPConfig(IP_AP, GTW_AP, mask);
  WiFi.softAP(ssid_AP);

  Serial.println();
  Serial.print("AP SSID: ");
  Serial.println(ssid_AP);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  //-----------Connessione a Remote-Camera se disponibile---------------
  /*Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.mode(WIFI_STA);
  WiFi.config(IP, DNS, GTW, mask);
  WiFi.begin(ssid);

  /*while (WiFi.status() != WL_CONNECTED) //attendo connessione
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");*/
  
  server.on("/",Respond);
  server.on("/favicon.ico",Favicon);
  server.begin();
  server.onNotFound([]()
  {
    command = server.uri();
    server.send(200,"text/plain",command);
    change_command = 1;
  });

  Serial.print("STA IP address: ");
  Serial.println(WiFi.localIP());
  
  Serial.println("Server setup OK");
}

void Respond()
{
  server.send(200,"text/html","<h1>Sider</h1>");
}

void Favicon()
{
  return;
}

void ESP_Command() 
{
  server.handleClient();
}

