//Definizione dei PIN
const int pinDir = D2;
const int pinStep = D3;
 
const int numStepMotore = 200; //E' il numero di step per rotazione del motore (potrebbe differire in base al modello)
const long velocita = 500; //Si tratta di microsecondi tra un impulso e l'altro sul pin STEP
 
void setup() {
  //inizializzo i PIN come OUTPUT
  pinMode(pinStep, OUTPUT);
  pinMode(pinDir, OUTPUT);
}
void loop() {
 
  //definiamo la direzione del motore
  digitalWrite(pinDir, HIGH);
 
  //esegue un giro completo in un senso
  for (int x = 0; x <= numStepMotore; x++) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocita);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocita);
  }
 
  //aspetto 2 secondi
  delay(2000);
 
  //cambio la direzione di marcia
  digitalWrite(pinDir, LOW);
 
  //rieseguo un altro giro completo nel senso opposto
  for (int x = 0; x <= numStepMotore; x++) {
    digitalWrite(pinStep, HIGH);
    delayMicroseconds(velocita);
    digitalWrite(pinStep, LOW);
    delayMicroseconds(velocita);
  }
 
  //aspetto altri 2 secondi
  delay(2000);
}
