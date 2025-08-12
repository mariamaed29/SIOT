const int ledPin = 8;
const int botaoPin = 7;

bool ledEstado = false;        // Estado atual do LED (ligado ou desligado)
bool botaoAnterior = LOW;      // Estado anterior do botão

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(botaoPin, INPUT_PULLUP);  // Botão com resistor pull-up interno
  digitalWrite(ledPin, LOW);         // LED inicialmente desligado
}

void loop() {
  bool botaoAtual = digitalRead(botaoPin);

  // Detecta a transição de HIGH para LOW (botão pressionado)
  if (botaoAnterior == HIGH && botaoAtual == LOW) {
    // Alterna o estado do LED
    ledEstado = !ledEstado;
    digitalWrite(ledPin, ledEstado ? HIGH : LOW);
  }

  botaoAnterior = botaoAtual;

  delay(50); // pequeno debounce para evitar múltiplas leituras rápidas
}
