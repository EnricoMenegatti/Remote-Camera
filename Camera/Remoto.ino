void Remoto()
{
  Serial.println("++++++++++++Remoto++++++++++++");
}

void Time_Remoto(uint8_t * Time)
{
  int mul;
  uint32_t Time_1, Time_2;

  Time_1 = (uint32_t) strtol((const char *) &Time[0], NULL, 13);//Time[1]*1000 + Time[2]*100 + Time[3]*10 + Time[4]; //(c[2] - 48) * 1000 + (c[3] - 48) * 100 + (c[4] - 48) * 10 + (c[5] - 48); //ESTRAI VALORI E CONVERI IN NUMERO

  if (Time[5] == 'm')
  {
    mul = 1;
  }
  else if (Time[5] == 'S')
  {
    mul = 1000;
  }
  else if (Time[5] == 'M')
  {
    mul = 60000;
  }

  return Time_1;// * mul; //TRASFORMA IN MILLISECONDI
}
