// Semáforo simples (blocking) - Arduino
const int PIN_RED   = 8;
const int PIN_YELLOW= 9;
const int PIN_GREEN = 10;

// tempos em milissegundos
const unsigned long TIME_GREEN  = 5000; // 5s
const unsigned long TIME_YELLOW = 2000; // 2s
const unsigned long TIME_RED    = 5000; // 5s

void setup() {
  pinMode(PIN_RED, OUTPUT);
  pinMode(PIN_YELLOW, OUTPUT);
  pinMode(PIN_GREEN, OUTPUT);
  // garante início com vermelho
  digitalWrite(PIN_RED, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_GREEN, LOW);
}

void loop() {
  // Verde
  digitalWrite(PIN_GREEN, HIGH);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, LOW);
  delay(TIME_GREEN);

  // Amarelo
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, HIGH);
  digitalWrite(PIN_RED, LOW);
  delay(TIME_YELLOW);

  // Vermelho
  digitalWrite(PIN_GREEN, LOW);
  digitalWrite(PIN_YELLOW, LOW);
  digitalWrite(PIN_RED, HIGH);
  delay(TIME_RED);
}
