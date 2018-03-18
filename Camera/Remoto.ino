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
	display.write(70);
	display.setCursor(77,25);
	display.write(83);

}

void scatto()
{
	if (c[0] == 'F' && c[1] == 'F') //FOCUS
	{

		if (c[2] != '-') //IMPOSTA TEMPO FUOCO
		{
			t_focus = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

			if (c[6] == 'm')
			{
				mul_d = 1;
			}
			else if (c[6] == 'S')
			{
				mul_d = 1000;
			}
			else if (c[6] == 'M')
			{
				mul_d = 60000;
			}

			d_focus = t_focus * mul_d; //TRASFORMA IN MILLISECONDI
		}

		display.setTextColor(BLACK, WHITE);
		display.setTextSize(3);
		linee_mancanti(37,25);
		display.setCursor(37,25);
		display.write(70);
		mySerial.println("Focus");

		digitalWrite(p_focus, HIGH); // Focus..

		if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
		{
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(33,53);
			display.println(t_focus);
			display.setCursor(50,53);
			display.println(c[6]);
			display.display();

			delay(d_focus);
		}
		else //FUOCO CON TEMPO STANDARD
		{
			t_focus = 1;
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(33,53);
			display.println(t_focus);
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

		display.setTextColor(BLACK, WHITE);
		display.setTextSize(3);
		linee_mancanti(37,25);
		display.setCursor(37,25);
		display.write(70);
		mySerial.println("Focus");

		digitalWrite(p_focus, HIGH); // Focus..

		t_focus = 1;
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(33,53);
		display.println(t_focus);
		display.setCursor(50,53);
		display.println(c[6]);
		display.display();

		delay(1000);

		display.setTextColor(BLACK, WHITE);
		display.setTextSize(3);
		linee_mancanti(77,25);
		display.setCursor(77,25);
		display.write(83);
		mySerial.println("Shoot");

		digitalWrite(p_shoot, HIGH); // Shoot !!

		t_shoot = 100;
		display.setTextSize(1);
		display.setTextColor(WHITE);
		display.setCursor(73,53);
		display.println(t_shoot);
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
		if (c[2] != '-') //IMPOSTA TEMPO BULB
		{
			t_shoot = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

			if (c[6] == 'm')
			{
				mul_d = 1;
			}
			else if (c[6] == 'S')
			{
				mul_d = 1000;
			}
			else if (c[6] == 'M')
			{
				mul_d = 60000;
			}

			d_shoot = t_shoot * mul_d; //TRASFORMA IN MILLISECONDI

		}

		display.setTextColor(BLACK, WHITE);
		display.setTextSize(3);
		linee_mancanti(77,25);
		display.setCursor(77,25);
		display.write(83);
		mySerial.println("Shoot");

		digitalWrite(p_focus, HIGH);
		digitalWrite(p_shoot, HIGH); // Shoot !!

		if (c[2] != '-') //SCATTA CON TEMPO BULB
		{
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(73,53);
			display.println(t_shoot);
			display.setCursor(90,53);
			display.println(c[6]);
			display.display();

			delay(d_shoot);
		}
		else //SCATTA CON TEMPO MACCHINA
		{
			t_shoot = 100;
			display.setTextSize(1);
			display.setTextColor(WHITE);
			display.setCursor(73,53);
			display.println(t_shoot);
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
