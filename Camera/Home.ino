void Home()
{
  detachInterrupt(digitalPinToInterrupt(p_audio));
  detachInterrupt(digitalPinToInterrupt(p_laser));

  pagina_0();
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

