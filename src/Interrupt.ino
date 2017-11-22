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

          time_2 = millis();
          interrupt_ok = false;
          delay(1000);

          digitalWrite(p_focus, HIGH);
          digitalWrite(p_shoot, HIGH); // Shoot !!

          delay(50);

          digitalWrite(p_shoot, LOW);
          digitalWrite(p_focus, LOW);

          time_0 = time_2 - time_1;
          print_interrupt();

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
      }
  }
}
