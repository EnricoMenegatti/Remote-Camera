void Remoto()
{
  Serial.println("++++++++++++Remoto++++++++++++");
}

void scatto(int flag)
{
  if (flag == 1)//solo premendo encoder
  {  
    digitalWrite(p_focus, HIGH); // Focus..
  
    d_focus = 1000;
    t_focus = 1000;
  
    delay(d_focus);
  
    digitalWrite(p_shoot, HIGH); // Shoot !!
  
    d_shoot = 100;
    t_shoot = 100;
  
    delay(d_shoot);
  
    digitalWrite(p_focus, LOW);
    digitalWrite(p_shoot, LOW);
  }
  
  else//scatto da applucazione
  {
  	if (c[0] == 'F' && c[1] == 'F') //FOCUS
  	{  
  		digitalWrite(p_focus, HIGH); // Focus..
  
  		if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
        time_remoto(d_focus, t_focus);//CALCOLA TEMPO DI FUOCO
  
  		else //FUOCO CON TEMPO STANDARD
      {
        d_focus = 1000;
        t_focus = 1000;
      }
  
  		delay(d_focus);
  
  		digitalWrite(p_focus, LOW);
  	}
  
  	if (c[0] == 'F' && c[1] == 'S')//FOCUS + SHOOT
  	{  
  		digitalWrite(p_focus, HIGH); // Focus..
  
  		d_focus = 1000;
      t_focus = 1000;
  
  		delay(d_focus);
  
  		digitalWrite(p_shoot, HIGH); // Shoot !!
  
  		d_shoot = 100;
      t_shoot = 100;
  
  		delay(d_shoot);
  
  		digitalWrite(p_focus, LOW);
  		digitalWrite(p_shoot, LOW);
  	}
  
  
  	if (c[0] == 'S' && c[1] == 'S') //SHOOT
  	{  
  		digitalWrite(p_focus, HIGH);
  		digitalWrite(p_shoot, HIGH); // Shoot !!
  
  		if (c[2] != '-') //SCATTA CON TEMPO BULB
        time_remoto(d_shoot, t_shoot);
  
  		else //SCATTA CON TEMPO MACCHINA
      {
  			d_shoot = 100;
        t_shoot = 100;
      }
  
  		delay(d_shoot);
  
  		digitalWrite(p_shoot, LOW);
  		digitalWrite(p_focus, LOW);
  
  	}
  }
}

void time_remoto(long delay_out, int Time)
{
  int mul;

  Time = (c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

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

  delay_out = Time * mul; //TRASFORMA IN MILLISECONDI
}
