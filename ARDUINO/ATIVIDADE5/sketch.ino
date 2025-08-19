// Pino PWM conectado ao LED
const int ledPin = 9; 

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // Aumenta o brilho
  for (int brilho = 0; brilho <= 255; brilho++) {
    analogWrite(ledPin, brilho);
    delay(10); // Delay para visualizar a mudança de brilho
  }

  // Diminui o brilho
  for (int brilho = 255; brilho >= 0; brilho--) {
    analogWrite(ledPin, brilho);
    delay(10);
  }
}
