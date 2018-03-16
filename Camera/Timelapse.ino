void Lapse()
{
  //detachInterrupt(digitalPinToInterrupt(p_interrupt));

  pagina_2();
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
}

void pagina_2()
{

	display.clearDisplay();
	display.setTextSize(2);
	display.setTextColor(WHITE);
	display.setCursor(0,0);
	display.println("TIMELAPSE");

}
