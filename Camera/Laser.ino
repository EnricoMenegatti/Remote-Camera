void Laser()
{
  attachInterrupt(digitalPinToInterrupt(p_laser), f_laser, LOW);
  detachInterrupt(digitalPinToInterrupt(p_audio));

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
        t_laser();
        i = 0;
      }
    }
  }
}

void f_laser()
{
  laser_ok = true;
  time_1 = micros();
}

void t_laser()
{

  d_laser = (c[0] - 48) * 1000000 + (c[1] - 48) * 100000 + (c[2] - 48) * 10000 + (c[3] - 48) * 1000 + (c[4] - 48) * 100 + (c[5] - 48) * 10 + (c[6] - 48); //ESTRAI VALORI E CONVERI IN NUMERO
  save_ee();
  
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
  display.drawLine(79, 29, 97, 29, WHITE); //LINEE ORIZZONTALI
  display.drawLine(78, 28, 97, 28, WHITE);
  display.drawLine(77, 27, 97, 27, WHITE);
  display.drawLine(79, 29, 79, 53, WHITE); //LINEE VERTICALI
  display.drawLine(78, 28, 78, 53, WHITE);
  display.drawLine(77, 27, 77, 53, WHITE);
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
