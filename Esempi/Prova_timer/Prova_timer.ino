
<<<<<<< HEAD
#include <Ticker.h>

#define ESP8266

Ticker flipper;

int count = 0;
long somma;

void flip()
{
  Serial.println(micros());
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
  
  ++count;
  // when the counter reaches a certain value, start blinking like crazy
  if (count == 20)
  {
    Serial.println("***********************************");
    flipper.attach_ms(5, flip);
  }
  // when the counter reaches yet another value, stop blinking
  else if (count == 120)
  { 
    flipper.detach();
  }
}

void setup() 
{
  Serial.begin(115200);
  
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  
  // flip the pin every 0.3s
  flipper.attach_ms(10, flip);
}

void loop() 
{
  somma = somma + 1;
}

=======
int LED = 2;
bool toggle = false;

void timer0_ISR (void) {
  if (toggle) {
    digitalWrite(LED, HIGH);
    toggle = false;
  } else {
    digitalWrite(LED, LOW);
    toggle = true;
  }
  timer0_write(ESP.getCycleCount() + 80000000L); // 80MHz == 1sec
  Serial.println("timer0_ISR");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  noInterrupts();
  timer0_isr_init();
  timer0_attachInterrupt(timer0_ISR);
  timer0_write(ESP.getCycleCount() + 80000000L); // 80MHz == 1sec
  interrupts();
}

void loop() {}
>>>>>>> 5e5c9141fb5b950feb4089bbb8a45a99a07cd4c3
