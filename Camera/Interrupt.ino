void Interrupt()
{
  attachInterrupt(digitalPinToInterrupt(p_interrupt), f_interrupt, LOW);

  pagina_4();
  display.display();

  while (modalita == 4)
  {
    if (interrupt_ok == true) // SE INTERRUPT AVVENUTO
    {
      detachInterrupt(digitalPinToInterrupt(p_interrupt)); // BLOCCO ALTRI INTERRUPT

      time_2 = micros();
      interrupt_ok = false;
      delay(d_interrupt);

      digitalWrite(p_focus, HIGH);
      digitalWrite(p_shoot, HIGH); // Shoot !!

      print_interrupt_1();
      delay(100);

      digitalWrite(p_shoot, LOW);
      digitalWrite(p_focus, LOW);

      time_0 = time_2 - time_1;//delay da quando viene riconosciuto l'interrupt a quando viene elaborato
      print_interrupt_2();

      while (digitalRead(p_interrupt) == false)
      {
        delay(500);
      }

      attachInterrupt(digitalPinToInterrupt(p_interrupt), f_interrupt, LOW);

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
        t_interrupt();
        i = 0;
      }
    }
  }
}

void f_interrupt()
{
	interrupt_ok = true;
	time_1 = micros();
}

void t_interrupt()
{

  d_interrupt = (c[0] - 48) * 1000000 + (c[1] - 48) * 100000 + (c[2] - 48) * 10000 + (c[3] - 48) * 1000 + (c[4] - 48) * 100 + (c[5] - 48) * 10 + (c[6] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  save_ee();
  
}

void pagina_4()
{

	display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(3);
  display.setCursor(80,30);
  display.write(73);//I
	display.setTextSize(2);
	display.setCursor(10,0);
	display.println("INTERRUPT");
  display.setCursor(10,20);
  display.println(d_interrupt);

}

void print_interrupt_1()
{
  display.clearDisplay();
  
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  display.drawLine(79, 29, 97, 29, WHITE); //LINEE ORIZZONTALI
  display.drawLine(78, 28, 97, 28, WHITE);
  display.drawLine(77, 27, 97, 27, WHITE);
  display.drawLine(79, 29, 79, 53, WHITE); //LINEE VERTICALI
  display.drawLine(78, 28, 78, 53, WHITE);
  display.drawLine(77, 27, 77, 53, WHITE);
  display.setCursor(80,30);
  display.write(73);//I
  
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(10,0);
  display.println("INTERRUPT");
  display.setCursor(10,20);
  display.println(d_interrupt);
  display.display();
}

void print_interrupt_2()
{
	pagina_4();
	display.setCursor(10,40);
	display.println(time_0);
	display.display();
}
