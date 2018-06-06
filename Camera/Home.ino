void Home()
{
  Serial.println("Home");
  modalita = 0;
  
  //detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  Enc_cont = 0;

  pagina(0);
  display.display();

  while (modalita == 0)
  {
    encoder(4, 1);//VALORE MAX, MIN
    ESP_Command();

    switch (Enc_cont)
    {
      case 0:
        //Serial.println("0");
        pagina(0);
        display.display();
  
      break;
      
      case 1: 
        //Serial.println("1");
        pagina_R();
        display.display();
  
      break;
  
      case 2:
        //Serial.println("2");
        pagina_T();
        display.display();
  
      break;
  
      case 3:
        //Serial.println("3");
        pagina_L();
        display.display();
  
      break;
  
      case 4:
        //Serial.println("4");
        pagina_A();
        display.display();
  
      break;
  
      default:
  
        pagina(0);
        display.display();
  
      break;
    }

    if (digitalRead(p_SW) == 0)//SELEZIONO MODALITA'
    {
      while (digitalRead(p_SW) == 0)//ATTENDO RILASCIO
      {
        Serial.print(".");
        yield();
      }
      
      modalita = Enc_cont;
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
    }
    yield();
  }
}

