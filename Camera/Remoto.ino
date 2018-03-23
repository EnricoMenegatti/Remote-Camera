void Remoto()
{
  //detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  pagina_1();
  display.display();

  if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME
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
    else if (c[i-1] == '*') //FINE STRINGA E CICLO DI SCATTO
    {
      scatto();
      i = 0;
    }
  }
}

void pagina_1()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(29,0);
	display.println("REMOTO");

	display.setTextSize(3);
	display.setCursor(37,25);
	display.write(70);//F
	display.setCursor(77,25);
	display.write(83);//S

}

void scatto()
{
	if (c[0] == 'F' && c[1] == 'F') //FOCUS
	{
		F_nera();

		digitalWrite(p_focus, HIGH); // Focus..

		if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
		{
      time_remoto(d_focus);//CALCOLA TEMPO DI FUOCO

			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(33,53);
			display.println(d_focus);
			display.setCursor(50,53);
			display.println(c[6]);
			display.display();

			delay(d_focus);
		}
		else //FUOCO CON TEMPO STANDARD
		{
			d_focus = 1000;

			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(33,53);
			display.println(d_focus);
			display.setCursor(50,53);
			display.println(c[6]);
			display.display();

			delay(1000);
		}

		pagina_1();
		display.display();

		digitalWrite(p_focus, LOW);
	}

	if (c[0] == 'F' && c[1] == 'S') //FOCUS //FOCUS + SHOOT
	{
		F_nera();

		digitalWrite(p_focus, HIGH); // Focus..

		d_focus = 1;

		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(33,53);
		display.println(d_focus);
		display.setCursor(50,53);
		display.println(c[6]);
		display.display();

		delay(1000);

		S_nera();

		digitalWrite(p_shoot, HIGH); // Shoot !!

		d_shoot = 100;

		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(73,53);
		display.println(d_shoot);
		display.setCursor(90,53);
		display.println(c[6]);
		display.display();

		delay(100);

		pagina_1();
		display.display();

		digitalWrite(p_focus, LOW);
		digitalWrite(p_shoot, LOW);
	}


	if (c[0] == 'S' && c[1] == 'S') //SHOOT
	{
    S_nera();

		digitalWrite(p_focus, HIGH);
		digitalWrite(p_shoot, HIGH); // Shoot !!

		if (c[2] != '-') //SCATTA CON TEMPO BULB
		{
      time_remoto(d_shoot);

			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(73,53);
			display.println(d_shoot);
			display.setCursor(90,53);
			display.println(c[6]);
			display.display();

			delay(d_shoot);
		}
		else //SCATTA CON TEMPO MACCHINA
		{
			d_shoot = 100;
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(73,53);
			display.println(d_shoot);
			display.setCursor(90,53);
			display.println(c[6]);
			display.display();

			delay(100);
		}

		pagina_1();
		display.display();

		digitalWrite(p_shoot, LOW);
		digitalWrite(p_focus, LOW);

	}
}

void F_nera()
{
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(37,25);
  display.setCursor(37,25);
  display.write(70);//F
  mySerial.println("Focus");
}

void S_nera()
{
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(77,25);
  display.setCursor(77,25);
  display.write(83);//S
  mySerial.println("Shoot");
}

void time_remoto(long delay_out)
{
  int mul;

  delay_out = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

  if (c[6] == 'm')
  {
    mul = 1;
  }
  else if (c[6] == 'S')
  {
    mul = 1000;
  }
  else if (c[6] == 'M')
  {
    mul = 60000;
  }

  delay_out = delay_out * mul; //TRASFORMA IN MILLISECONDI
}
