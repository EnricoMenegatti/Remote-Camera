void Laser()
{
  detachInterrupt(digitalPinToInterrupt(p_interrupt));

  pagina_3();
  display.display();

  if (mySerial.available() > 0)
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

      i = 0;
    }
  }

  laser = analogRead(p_laser);

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,20);
  display.println(laser);
  display.display();
}

void pagina_3()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(20,0);
	display.println("LASER");

}
