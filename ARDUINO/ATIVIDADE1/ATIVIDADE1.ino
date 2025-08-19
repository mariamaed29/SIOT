// Defina o pino do LED
const int ledPin = 13;

// Defina os tempos de duração
const int tempoPonto = 200;  // 200 milissegundos
const int tempoTraco = 3 * tempoPonto;
const int tempoEntreElementos = tempoPonto;
const int tempoEntreLetras = 3 * tempoPonto;
const int tempoEntrePalavras = 7 * tempoPonto;

// Mapeamento do Código Morse
String morseMap[] = {
  // Letras
  ".-",   // A
  "-...", // B
  "-.-.", // C
  "-..",  // D
  ".",    // E
  "..-.", // F
  "--.",  // G
  "....", // H
  "..",   // I
  ".---", // J
  "-.-",  // K
  ".-..", // L
  "--",   // M
  "-.",   // N
  "---",  // O
  ".--.", // P
  "--.-", // Q
  ".-.",  // R
  "...",  // S
  "-",    // T
  "..-",  // U
  "...-", // V
  ".--",  // W
  "-..-", // X
  "-.--", // Y
  "--..", // Z
  // Números
  "-----",  // 0
  ".----",  // 1
  "..---",  // 2
  "...--",  // 3
  "....-",  // 4
  ".....",  // 5
  "-....",  // 6
  "--...",  // 7
  "---..",  // 8
  "----."   // 9
};

// Frase para ser transmitida
String frase = "Ola mundo";

void setup() {
  pinMode(ledPin, OUTPUT);
}

void loop() {
  for (int i = 0; i < frase.length(); i++) {
    char c = frase[i];
    
    // Converter o caractere para maiúscula para facilitar o mapeamento
    c = toupper(c);

    // Se o caractere for um espaço, adicione um atraso de palavra
    if (c == ' ') {
      delay(tempoEntrePalavras);
      continue;
    }
    
    // Encontrar o índice do caractere
    int index = (int)c - (int)'A';
    
    // Apenas para letras, ignore outros caracteres
    if (index >= 0 && index < 26) {
      String morseCode = morseMap[index];
      
      // Transmitir o código Morse
      for (int j = 0; j < morseCode.length(); j++) {
        char morseChar = morseCode[j];
        
        if (morseChar == '.') {
          piscar(tempoPonto);
        } else if (morseChar == '-') {
          piscar(tempoTraco);
        }
        delay(tempoEntreElementos);
      }
      delay(tempoEntreLetras);
    }
  }
  
  // Repita a mensagem após um tempo
  delay(5000); 
}

void piscar(int duracao) {
  digitalWrite(ledPin, HIGH);
  delay(duracao);
  digitalWrite(ledPin, LOW);
}


