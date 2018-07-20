void Remoto()
{
  Serial.println("Remoto");
  modalita = 1;
  
  //detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  pagina(1);
  display.display();

  while (modalita == 1)
  {
    ESP_Command();
    
    if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME SE PREMUTO PER PIU DI 2 SECONDI
    {
      last_time = millis();
      t_pulsante = 0;
      
      while (digitalRead(p_SW) == 0)//ATTENDO RILASCIO
      {
        t_pulsante = millis() - last_time;
        //Serial.print(t_pulsante);
        yield();
      }
            
      if (t_pulsante < 2000)//2000 = 2 SECONDI
      {
        scatto(1);
      }
  
      else 
        modalita = 0;
        
    }
  
    else if (change_command == 1)
    {
      verifica_comando();
      scatto(0);
    }
  
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
      else if (c[i-1] == '*') //FINE STRINGA E CICLO DI SCATTO
      {
        scatto(0);
        i = 0;
      }
    }
  }
}

void scatto(int flag)
{
  if (flag == 1)//solo premendo encoder
  {
    F_nera();
  
      digitalWrite(p_focus, HIGH); // Focus..
  
      d_focus = 1000;
      t_focus = 1000;
  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(33,53);
      display.println(t_focus);
      display.setCursor(50,53);
      display.println(c[6]);
      display.display();
  
      delay(d_focus);
  
      S_nera();
  
      digitalWrite(p_shoot, HIGH); // Shoot !!
  
      d_shoot = 100;
      t_shoot = 100;
  
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(73,53);
      display.println(t_shoot);
      display.setCursor(90,53);
      display.println(c[6]);
      display.display();
  
      delay(d_shoot);
  
      pagina(1);
      display.display();
  
      digitalWrite(p_focus, LOW);
      digitalWrite(p_shoot, LOW);
  }
  
  else//scatto da applucazione
  {
  	if (c[0] == 'F' && c[1] == 'F') //FOCUS
  	{
  		F_nera();
  
  		digitalWrite(p_focus, HIGH); // Focus..
  
  		if (c[2] != '-') //FUOCO CON TEMPO IMPOSTATO
        time_remoto(d_focus, t_focus);//CALCOLA TEMPO DI FUOCO
  
  		else //FUOCO CON TEMPO STANDARD
      {
        d_focus = 1000;
        t_focus = 1000;
      }
  
  		display.setTextSize(1);
  		display.setTextColor(WHITE);
  		display.setCursor(33,53);
  		display.println(t_focus);
  		display.setCursor(50,53);
  		display.println(c[6]);
  		display.display();
  
  		delay(d_focus);
  
  		pagina(1);
  		display.display();
  
  		digitalWrite(p_focus, LOW);
  	}
  
  	if (c[0] == 'F' && c[1] == 'S')//FOCUS + SHOOT
  	{
  		F_nera();
  
  		digitalWrite(p_focus, HIGH); // Focus..
  
  		d_focus = 1000;
      t_focus = 1000;
  
  		display.setTextSize(1);
  		display.setTextColor(WHITE);
  		display.setCursor(33,53);
  		display.println(t_focus);
  		display.setCursor(50,53);
  		display.println(c[6]);
  		display.display();
  
  		delay(d_focus);
  
  		S_nera();
  
  		digitalWrite(p_shoot, HIGH); // Shoot !!
  
  		d_shoot = 100;
      t_shoot = 100;
  
  		display.setTextSize(1);
  		display.setTextColor(WHITE);
  		display.setCursor(73,53);
  		display.println(t_shoot);
  		display.setCursor(90,53);
  		display.println(c[6]);
  		display.display();
  
  		delay(d_shoot);
  
  		pagina(1);
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
        time_remoto(d_shoot, t_shoot);
  
  		else //SCATTA CON TEMPO MACCHINA
  			d_shoot = 100;
        t_shoot = 100;
  
  		display.setTextSize(1);
  		display.setTextColor(WHITE);
  		display.setCursor(73,53);
  		display.println(t_shoot);
  		display.setCursor(90,53);
  		display.println(c[6]);
  		display.display();
  
  		delay(d_shoot);
  
  		pagina(1);
  		display.display();
  
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
