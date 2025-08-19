// Pinos PWM para cada cor
const int redPin = 9;
const int greenPin = 10;
const int bluePin = 11;

void setup() {
  // Configura os pinos como saída
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop() {
  // Exemplo de variação de cores usando PWM (0-255)
  
  // Vermelho forte
  setColor(255, 0, 0);
  delay(1000);
  
  // Verde forte
  setColor(0, 255, 0);
  delay(1000);
  
  // Azul forte
  setColor(0, 0, 255);
  delay(1000);
  
  // Amarelo (vermelho + verde)
  setColor(255, 255, 0);
  delay(1000);
  
  // Ciano (verde + azul)
  setColor(0, 255, 255);
  delay(1000);
  
  // Magenta (vermelho + azul)
  setColor(255, 0, 255);
  delay(1000);
  
  // Branco (todas as cores no máximo)
  setColor(255, 255, 255);
  delay(1000);
  
  // Apaga LED
  setColor(0, 0, 0);
  delay(1000);
}

// Função para ajustar a cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}




