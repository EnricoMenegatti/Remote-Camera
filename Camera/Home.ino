void Home()
{
  Serial.println("home");
  //detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  Enc_cont = 0;

  pagina_0();
  display.display();

  while (modalita == 0)
  {
    encoder(4, 1);//VALORE MAX, MIN
    ESP_Command();

    switch (Enc_cont)
    {
      case 0:
  
        pagina_0();
        display.display();
  
      break;
      
      case 1: 
  
        pagina_R();
        display.display();
  
      break;
  
      case 2:
  
        pagina_T();
        display.display();
  
      break;
  
      case 3:
  
        pagina_L();
        display.display();
  
      break;
  
      case 4:
  
        pagina_A();
        display.display();
  
      break;
  
      default:
  
        pagina_0();
        display.display();
  
      break;
    }

    if (digitalRead(p_SW) == 0)//SELEZIONO MODALITA'
    {
      while (digitalRead(p_SW) == 0);//ATTENDO RILASCIO
      
      modalita = Enc_cont;
    }

    else if (change_command == 1)
    {
      verifica_comando();
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
    }
  }
}

void pagina_0()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A
}

void pagina_R()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(8,30);
  display.write(82);//R
  linee_mancanti(8,30);
}

void pagina_T()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(36,30);
  display.write(84);//T
  linee_mancanti(36,30);
}

void pagina_L()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(64,30);
  display.write(76);//L
  linee_mancanti(64,30);
}

void pagina_A()
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(64,30);
  display.write(76);//L

  display.setTextColor(BLACK, WHITE);
  display.setCursor(92,30);
  display.write(65);//A
  linee_mancanti(92,30);
}


