void Slider()
{
  Serial.println("Slider");
  modalita = 0;

  while (modalita == 0)
  {
    // Check if a client has connected
    WiFiClient client = server1.available();
    if (!client)
    {
      yield();
      //return;
    }
  
    digitalWrite(D2, LOW);
    //ricevi richiesta da client
    String Richiesta = client.readStringUntil('\r');
    Serial.println("********************************");
    Serial.println("Richiesta: " + Richiesta);
    client.flush();
    //rispondi a client
    client.println("OK\r");
    digitalWrite(D2, HIGH);
  }
}

