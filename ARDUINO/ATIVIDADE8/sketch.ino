// Definindo o pino do potenciômetro e os pinos dos LEDs
const int pinoPotenciometro = A0;
const int pinosLEDs[] = {2, 3, 4, 5, 6, 7, 8, 9};
const int numeroDeLEDs = 8;

void setup() {
  // Configura todos os pinos dos LEDs como SAÍDA
  for (int i = 0; i < numeroDeLEDs; i++) {
    pinMode(pinosLEDs[i], OUTPUT);
  }
}

void loop() {
  // 1. Ler o valor do potenciômetro (0 a 1023)
  int valorPotenciometro = analogRead(pinoPotenciometro);

  // 2. Mapear o valor lido para o número de LEDs (0 a 8)
  int ledsParaAcender = map(valorPotenciometro, 0, 1023, 0, numeroDeLEDs);

  // 3. Acender os LEDs até o número mapeado
  for (int i = 0; i < ledsParaAcender; i++) {
    digitalWrite(pinosLEDs[i], HIGH);
  }

  // 4. Apagar os LEDs restantes
  for (int i = ledsParaAcender; i < numeroDeLEDs; i++) {
    digitalWrite(pinosLEDs[i], LOW);
  }

  // Pequena pausa para estabilidade
  delay(10);
}



