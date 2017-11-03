
const int focus = 8;
const int shoot = 9;

int serial = 0;

void setup()
{

  Serial.begin(115200); // Baud-rate
  pinMode(focus, OUTPUT);
  pinMode(shoot, OUTPUT);

}

void loop()
{
  // Send data only when you receive data
  if (Serial.available() > 0)
  {
    // Reading incoming bytes :
    serial = Serial.read();

    switch (serial)
    {
      case 'f':

        digitalWrite(focus, HIGH); // Focus..
        delay(1000);
        digitalWrite(focus, LOW);

        break;

      case 's':

        digitalWrite(shoot, HIGH); // Shoot !!
        delay(200);
        digitalWrite(shoot, LOW);

        break;

    }
  }
}
