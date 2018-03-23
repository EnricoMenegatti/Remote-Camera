void Audio()
{
  attachInterrupt(digitalPinToInterrupt(p_audio), f_audio, LOW);
  detachInterrupt(digitalPinToInterrupt(p_laser));

  Enc_cont = 0;
  
  pagina_4();
  display.display();

  while (modalita == 4)
  {
    encoder(1, 0);//VALORE MAX, MIN

    switch (Enc_cont)
    {
      case 0:

        pagina_4();
        display.display();

      break;

      case 1:

        selezione(d_audio, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
        display.display();

      break;

      default:

        pagina_4();
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

    else if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME
    {
      while (digitalRead(p_SW) == 0);//ATTENDO RILASCIO

      modalita = 0;
    }

    else if (mySerial.available() > 0)
    {
      i = i + 1;

      // Reading incoming bytes :
      c[i-1] = mySerial.read();

      if (c[i-1] == '+') //FINE STRINGA E CAMBIO MODALITA'
      {
        c_modo();
        i = 0;
      }

      else if (c[i-1] == '*') //FINE STRINGA E CICLO
      {
        t_audio();
        i = 0;

        pagina_4();
        display.display();
      }
    }
  }
}

void f_audio()
{
	audio_ok = true;
	time_1 = micros();
}

void t_audio()
{

  d_audio = (c[0] - 48) * 1000000 + (c[1] - 48) * 100000 + (c[2] - 48) * 10000 + (c[3] - 48) * 1000 + (c[4] - 48) * 100 + (c[5] - 48) * 10 + (c[6] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  save_ee();

}

void pagina_4()
{

	display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(80,30);
  display.write(65);//A
	display.setTextSize(2);
	display.setCursor(30,0);
	display.println("AUDIO");
  display.setCursor(10,20);
  display.println(d_audio);

}

void print_audio_1()
{
  display.clearDisplay();

  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(80,30);
  display.setCursor(80,30);
  display.write(65);//A

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(30,0);
  display.println("AUDIO");
  display.setCursor(10,20);
  display.println(d_audio);
  display.display();
}

void print_audio_2()
{
	pagina_4();
	display.setCursor(10,40);
	display.println(time_0);
	display.display();
}
