
/*void Interrupt_Setup()
{
  Serial.println("Interrupt setup");
  noInterrupts();
  timer0_isr_init();
  //timer0_attachInterrupt(Timer0_ISR);
  //timer0_write(ESP.getCycleCount() + 80000000L); // 80MHz == 1sec

  Serial.println("Interrupt setup OK");
}

void Timer0_ISR()
{
  Serial.println(micros());
  digitalWrite(pStep, toggle);
  toggle = !toggle;

  cont++;

  timer0_write(ESP.getCycleCount() + (S_Vel.toInt() * 80)); // 80MHz == 1sec
  
  if (cont >= S_Step.toInt())
  {
    timer0_detachInterrupt();
  }
}*/
