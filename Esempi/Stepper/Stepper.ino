/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************
  This example runs directly on ESP8266 chip.

  Note: This requires ESP8266 support package:
    https://github.com/esp8266/Arduino

  Please be sure to select the right ESP8266 module
  in the Tools -> Board menu!

  Change WiFi ssid, pass, and Blynk auth token to run :)
  Feel free to apply it to any other example. It's simple!
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "50ef28d55ffe4ca49ecbb5828f19c39d";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Vodafone-Menegatti";
char pass[] = "Menegatti13";

const int pinDir = D2;
const int pinStep = D3;
 
const int numStepMotore = 200;
const long velocita = 2000;

int cursore;
int stato = 0;
 

BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V0);
  Blynk.syncVirtual(V1);
}

BLYNK_WRITE(V0)
{
  if(V0 == 1)
  {
    digitalWrite(pinDir, HIGH);

    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocita);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocita);
  }
}

BLYNK_WRITE(V1)
{
  if(V1 == 1)
  {
    digitalWrite(pinDir, LOW);

    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocita);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocita);
  }
}

void setup()
{
  // Debug console
  Serial.begin(9600);

  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();

  /*if(cursore < stato)
  {
    digitalWrite(pinDir, HIGH);
 
    //esegue un giro completo in un senso
    for (int x = 0; x <= stato - cursore; x++)
    {
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(velocita);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(velocita);
    }

    stato = cursore;
  }
  
  else if(cursore > stato)
  {
    digitalWrite(pinDir, LOW);
 
    //esegue un giro completo in un senso
    for (int x = 0; x <= cursore - stato; x++)
    {
      digitalWrite(pinStep, HIGH);
      delayMicroseconds(velocita);
      digitalWrite(pinStep, LOW);
      delayMicroseconds(velocita);
    }

    stato = cursore;
  }*/
}

