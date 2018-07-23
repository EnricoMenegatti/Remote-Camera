
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
