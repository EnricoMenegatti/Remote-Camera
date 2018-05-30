void Lapse()
{
  //detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  pagina_2();
  display.display();

  if (digitalRead(p_SW) == 0)//RITORNO ALLA HOME SE PREMUTO PER PIU DI 2 SECONDI
  {
    last_time = millis();
    t_pulsante = 0;
    
    while (digitalRead(p_SW) == 0)//ATTENDO RILASCIO
    {
      t_pulsante = millis() - last_time;
      Serial.print(t_pulsante);
    }
          
    if (t_pulsante < 2000)//2000 = 2 SECONDI
    {
      //selezione(d_laser, 10, 20);//VARIABILE, X VARIABILE, Y VARIABILE
      //display.display();
    }

    else 
      modalita = 0;
      
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
    else if (c[i-1] == '*') //FINE STRINGA E CICLO
    {

        i = 0;
    }
  }
}

void pagina_2()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("TIMELAPSE");

}
