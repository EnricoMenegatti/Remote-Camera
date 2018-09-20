void Laser()
{
laser_start://ETICHETTA PER GOTO

  Serial.println("++++++++++++Laser++++++++++++");
  modalita = 3;
  
  attachInterrupt(digitalPinToInterrupt(p_laser), f_laser, LOW);

  while (modalita == 3)
  {
    if (laser_ok == true) // SE INTERRUPT AVVENUTO
    {
      detachInterrupt(digitalPinToInterrupt(p_laser)); // BLOCCO ALTRI INTERRUPT

      time_2 = micros();
      laser_ok = false;
      delay(d_laser);

      digitalWrite(p_focus, HIGH);
      digitalWrite(p_shoot, HIGH); // Shoot !!
      
      delay(100);

      digitalWrite(p_shoot, LOW);
      digitalWrite(p_focus, LOW);

      time_0 = time_2 - time_1;//delay da quando viene riconosciuto l'interrupt a quando viene elaborato

      while (digitalRead(p_laser) == false)
      {
        delay(500);
      }
      
      attachInterrupt(digitalPinToInterrupt(p_laser), f_laser, LOW);
    }
    webSocket.loop();
    yield();
  }
}

void f_laser()
{
  laser_ok = true;
  time_1 = micros();
}

void t_laser()
{

  d_laser = (c[0] - 48) * 10000 + (c[1] - 48) * 1000 + (c[2] - 48) * 100 + (c[3] - 48) * 10 + (c[4] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  Eeprom_save();

}
