void Remoto()
{
  detachInterrupt(digitalPinToInterrupt(p_interrupt));

  pagina_1();
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
        scatto();
        i = 0;
    }
  }
}
