const int pinosLED[] = {2, 3, 4, 5};
const int numeroDePinos = 4;

// Variável para armazenar o número atual
int contador = 0;

void setup() {
  // Configura cada pino como saída
  for (int i = 0; i < numeroDePinos; i++) {
    pinMode(pinosLED[i], OUTPUT);
  }
}

void loop() {
  // Converte o número decimal para binário e acende/apaga os LEDs
  for (int i = 0; i < numeroDePinos; i++) {
    // bitRead(numero, bit) verifica se o bit é 0 ou 1
    int bitStatus = bitRead(contador, i);
    digitalWrite(pinosLED[i], bitStatus);
  }

  // Incrementa o contador
  contador++;

  // Reinicia a contagem quando chega a 16 (0 a 15)
  if (contador >= 16) {
    contador = 0;
  }

  // Espera 500ms antes de ir para o próximo número
  delay(500);
}
