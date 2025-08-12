const int botaoPin = 8;    // Pino do botão
const int ledPin = 7;     // Pino do LED (usando o LED interno do Arduino)

bool estadoLed = false;    // Estado atual do LED (false = apagado, true = ligado)
bool estadoBotaoAnterior = HIGH;  // Estado anterior do botão (considerando pull-up)

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP);  // Usando resistor interno pull-up
  digitalWrite(ledPin, LOW);         // Começa com LED apagado
}

void loop() {
  bool estadoBotaoAtual = digitalRead(botaoPin);

  // Detecta a transição do botão de HIGH para LOW (pressionado)
  if (estadoBotaoAnterior == HIGH && estadoBotaoAtual == LOW) {
    // Alterna o estado do LED
    estadoLed = !estadoLed;
    digitalWrite(ledPin, estadoLed ? HIGH : LOW);

    // Pequeno delay para evitar múltiplas leituras do mesmo toque (debounce simples)
    delay(50);
  }

  estadoBotaoAnterior = estadoBotaoAtual;
}


