
void pagina(int n_pagina)
{

  switch(n_pagina)
  {
    case 0://HOME
    
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
      
    break;

    case 1://REMOTO

      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(29,0);
      display.println("REMOTO");
    
      display.setTextSize(3);
      display.setCursor(37,25);
      display.write(70);//F
      display.setCursor(77,25);
      display.write(83);//S
      
    break;

    case 2://LAPSE

      display.clearDisplay();
      display.setTextSize(2);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      display.println("TIMELAPSE");

    break;

    case 3://LASER

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

    break;

    case 4://AUDIO
    
      display.clearDisplay();
      display.setTextColor(WHITE);
      display.setTextSize(3);
      display.setCursor(80,30);
      display.write(65);//A
      display.setTextSize(2);
      display.setCursor(30,0);
      display.println("AUDIO");
      display.setCursor(10,20);
      display.println(d_audio);
      
    break;
  }
}

void linee_mancanti(int X, int Y)
{
  display.drawLine(X - 1, Y - 1, X + 17, Y - 1, WHITE); //LINEE ORIZZONTALI
  display.drawLine(X - 2, Y - 2, X + 17, Y - 2, WHITE);
  display.drawLine(X - 3, Y - 3, X + 17, Y - 3, WHITE);
  display.drawLine(X - 1, Y - 1, X - 1, Y + 23, WHITE); //LINEE VERTICALI
  display.drawLine(X - 2, Y - 2, X - 2, Y + 23, WHITE);
  display.drawLine(X - 3, Y - 3, X - 3, Y + 23, WHITE);
}
//-----------------------------------------------HOME---------------------------------------
void pagina_R()
{
  //Serial.println("R");
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(36,30);
  display.write(84);//T
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(8,30);
  display.write(82);//R
  linee_mancanti(8,30);
}

void pagina_T()
{
  //Serial.println("T");
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.println("HOME");
  display.setTextSize(3);
  display.setCursor(8,30);
  display.write(82);//R
  display.setCursor(64,30);
  display.write(76);//L
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(36,30);
  display.write(84);//T
  linee_mancanti(36,30);
}

void pagina_L()
{
  //Serial.println("T");
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
  display.setCursor(92,30);
  display.write(65);//A

  display.setTextColor(BLACK, WHITE);
  display.setCursor(64,30);
  display.write(76);//L
  linee_mancanti(64,30);
}

void pagina_A()
{
  //Serial.println("A");
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

  display.setTextColor(BLACK, WHITE);
  display.setCursor(92,30);
  display.write(65);//A
  linee_mancanti(92,30);
}
//-----------------------------------------------REMOTO---------------------------------------
void F_nera()
{
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(37,25);
  display.setCursor(37,25);
  display.write(70);//F
  Serial.println("Focus");
}

void S_nera()
{
  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(77,25);
  display.setCursor(77,25);
  display.write(83);//S
  Serial.println("Shoot");
}
//-----------------------------------------------LAPSE---------------------------------------
//-----------------------------------------------LASER---------------------------------------
void print_laser_1()
{
  display.clearDisplay();

  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(80,30);
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
  pagina(3);
  display.setCursor(10,40);
  display.println(time_0);
  display.display();
}
//-----------------------------------------------AUDIO---------------------------------------
void print_audio_1()
{
  display.clearDisplay();

  display.setTextColor(BLACK, WHITE);
  display.setTextSize(3);
  linee_mancanti(80,30);
  display.setCursor(80,30);
  display.write(65);//A

  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(30,0);
  display.println("AUDIO");
  display.setCursor(10,20);
  display.println(d_audio);
  display.display();
}

void print_audio_2()
{
  pagina(4);
  display.setCursor(10,40);
  display.println(time_0);
  display.display();
}
