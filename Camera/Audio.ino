void Audio()
{
  Serial.println("++++++++++++Audio++++++++++++");
  modalita = 0;
  
  attachInterrupt(digitalPinToInterrupt(p_audio), f_audio, LOW);
  detachInterrupt(digitalPinToInterrupt(p_laser));

  Enc_cont = 0;
  selezione_ok = 0;

  pagina(4);
  display.display();

  while (modalita == 4)
  {
    encoder(1, 0);//VALORE MAX, MIN

    switch (Enc_cont)
    {
      case 0:

        pagina(4);
        display.display();

      break;

      case 1:

        selezione(d_audio, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
        display.display();

      break;

      default:

        pagina(4);
        display.display();

      break;
    }

    if (audio_ok == true) // SE INTERRUPT AVVENUTO
    {
      detachInterrupt(digitalPinToInterrupt(p_audio)); // BLOCCO ALTRI INTERRUPT

      time_2 = micros();
      audio_ok = false;
      delay(d_audio);

      digitalWrite(p_focus, HIGH);
      digitalWrite(p_shoot, HIGH); // Shoot !!

      print_audio_1();
      delay(100);

      digitalWrite(p_shoot, LOW);
      digitalWrite(p_focus, LOW);

      time_0 = time_2 - time_1;//delay da quando viene riconosciuto l'interrupt a quando viene elaborato

      while (digitalRead(p_audio) == false)
      {
        delay(500);
      }

      print_audio_2();
      attachInterrupt(digitalPinToInterrupt(p_audio), f_audio, LOW);

    }

    else if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME SE PREMUTO PER PIU DI 2 SECONDI
    {
      last_time = millis();
      t_pulsante = 0;
      
      while (digitalRead(p_SW) == 0)//ATTENDO RILASCIO
      {
        t_pulsante = millis() - last_time;
        Serial.print(t_pulsante);
        yield();
      }
            
      if (t_pulsante < 2000)//2000 = 2 SECONDI
      {
        if (selezione_ok == 0)
        {
          selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
          display.display();
        }

        else
        {
          pagina(4);
          display.display();
        }

        selezione_ok = !selezione_ok;
      }

      else 
        modalita = 0;
        
    }

    /*else if (change_command == 1)
    {
      verifica_comando();
    }*/

    else if (Serial.available() > 0)
    {
      i = i + 1;

      // Reading incoming bytes :
      c[i-1] = Serial.read();

      if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
      {
        c_modo();
        i = 0;
      }

      else if (c[i-1] == '*') //FINE STRINGA E CICLO
      {
        t_audio();
        i = 0;

        pagina(4);
        display.display();
      }
    }
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
