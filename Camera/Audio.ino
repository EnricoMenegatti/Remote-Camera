void Audio()
{
  Serial.println("++++++++++++Audio++++++++++++");
  
  attachInterrupt(digitalPinToInterrupt(p_audio), f_audio, LOW);

  while (modalita == 4)
  {
    if (audio_ok == true) // SE INTERRUPT AVVENUTO
    {
      detachInterrupt(digitalPinToInterrupt(p_audio)); // BLOCCO ALTRI INTERRUPT

      time_2 = micros();
      audio_ok = false;
      delay(d_audio);

      digitalWrite(p_focus, HIGH);
      digitalWrite(p_shoot, HIGH); // Shoot !!

      delay(100);

      digitalWrite(p_shoot, LOW);
      digitalWrite(p_focus, LOW);

      time_0 = time_2 - time_1;//delay da quando viene riconosciuto l'interrupt a quando viene elaborato

      while (digitalRead(p_audio) == false)
      {
        delay(500);
      }

      attachInterrupt(digitalPinToInterrupt(p_audio), f_audio, LOW);
    }
    webSocket.loop();
    yield();
  }
}

void f_audio()
{
	audio_ok = true;
	time_1 = micros();
}

void t_audio()
{

  d_audio = (c[0] - 48) * 10000 + (c[1] - 48) * 1000 + (c[2] - 48) * 100 + (c[3] - 48) * 10 + (c[4] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  Eeprom_save();

}
