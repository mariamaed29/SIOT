// Pinos onde os LEDs estão conectados
const int numLeds = 8;
int ledPins[numLeds] = {2, 3, 4, 5, 6, 7, 8, 9};

void setup() {
  for (int i = 0; i < numLeds; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  // Vai da esquerda para a direita
  for (int i = 0; i < numLeds; i++) {
    acendeLed(i);
  }

  // Volta da direita para a esquerda (sem repetir o último LED)
  for (int i = numLeds - 2; i > 0; i--) {
    acendeLed(i);
  }
}

void acendeLed(int i) {
  digitalWrite(ledPins[i], HIGH);
  delay(100); // Tempo que o LED fica aceso
  digitalWrite(ledPins[i], LOW);
}

