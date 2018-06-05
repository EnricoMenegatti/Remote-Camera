void Laser()
{
laser_start://ETICHETTA PER GOTO

  Serial.println("Laser");
  
  attachInterrupt(digitalPinToInterrupt(p_laser), f_laser, LOW);
  //detachInterrupt(digitalPinToInterrupt(p_audio));

  Enc_cont = 0;
  selezione_ok = 0;

  pagina_3();
  display.display();

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

      print_laser_1();
      delay(100);

      digitalWrite(p_shoot, LOW);
      digitalWrite(p_focus, LOW);

      time_0 = time_2 - time_1;//delay da quando viene riconosciuto l'interrupt a quando viene elaborato

      while (digitalRead(p_laser) == false)
      {
        delay(500);
      }

      print_laser_2();
      attachInterrupt(digitalPinToInterrupt(p_laser), f_laser, LOW);

    }

    /*else if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME SE PREMUTO PER PIU DI 2 SECONDI
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
          selezione_ok = !selezione_ok;
          selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
          display.display();
          Aumento_var(d_laser, 3);
          Serial.print("selezione");
          goto laser_start;
        }

        else
        {
          selezione_ok = !selezione_ok;
          pagina_3();
          display.display();
        }
        
      }

      else 
        modalita = 0;
        
    }*/

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
        t_laser();
        i = 0;

        pagina_3();
        display.display();
      }

     /* else
      {
        encoder(1, 0);//VALORE MAX, MIN

        switch (Enc_cont)
        {
          case 0:
    
            pagina_3();
            display.display();
    
          break;
    
          case 1:
    
            selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
            display.display();
    
          break;
    
          default:
    
            pagina_3();
            display.display();
    
          break;
        }
      }*/
    }
    yield();
  }
}

void f_laser()
{
  if (Enc_cont == 0)
  {
    laser_ok = true;
    time_1 = micros();
  }
}

void t_laser()
{

  d_laser = (c[0] - 48) * 10000 + (c[1] - 48) * 1000 + (c[2] - 48) * 100 + (c[3] - 48) * 10 + (c[4] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  Eeprom_save();

}

void pagina_3()
{

  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(80,30);
  display.write(76);//L
  display.setTextSize(2);
  display.setCursor(30,0);
  display.println("LASER");
  display.setCursor(10,20);
  display.println(d_laser);

}

void print_laser_1()
{
  display.clearDisplay();

  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(80,30);
  display.setCursor(80,30);
  display.write(76);//L

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(30,0);
  display.println("LASER");
  display.setCursor(10,20);
  display.println(d_laser);
  display.display();
}

void print_laser_2()
{
  pagina_3();
  display.setCursor(10,40);
  display.println(time_0);
  display.display();
}
