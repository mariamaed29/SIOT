// =================================================================
// 1. DEFINIÇÃO DE PINOS E CONSTANTES
// =================================================================

// Pinos do Sensor Ultrassônico HC-SR04
const int TRIG_PIN = 9;   // Pino Trigger (Saída)
const int ECHO_PIN = 10;  // Pino Echo (Entrada)

// Pinos dos LEDs Indicadores
const int LED_VERDE = 5;  // Nível BOM (Cheio)
const int LED_AMARELO = 4; // Nível ATENÇÃO (Médio)
const int LED_VERMELHO = 3; // Nível CRÍTICO (Vazio)

// =================================================================
// 2. VARIÁVEIS DE CALIBRAÇÃO (Ajustar para o seu reservatório!)
// =================================================================

// DISTANCIA_MAXIMA_CM: É a leitura do sensor quando o reservatório está COMPLETAMENTE VAZIO.
// *** SUBSTITUA ESTE VALOR PELA SUA MEDIDA REAL (ex: 45.0 cm) ***
const float DISTANCIA_MAXIMA_CM = 45.0; 

// LIMIARES DE ALERTA (em porcentagem de ocupação)
const int LIMIAR_CRITICO = 30; // Abaixo de 30% é CRÍTICO (LED Vermelho)
const int LIMIAR_ATENCAO = 70; // Entre 30% e 70% é ATENÇÃO (LED Amarelo)
// Acima de 70% é CHEIO (LED Verde)

// =================================================================
// 3. VARIÁVEIS DE ESTADO
// =================================================================
long duracao;     // Armazena a duração do pulso de eco
float distancia_cm; // Distância lida em centímetros
int nivel_porcentagem; // Nível de ocupação (0 a 100%)

// Variável de controle de tempo para o LED piscante (não bloqueia o código)
unsigned long tempoAnterior = 0;
const long intervaloPisca = 200; // Pisca a cada 200 milissegundos

// =================================================================
// 4. FUNÇÃO DE MEDIÇÃO DE DISTÂNCIA (HC-SR04)
// =================================================================

float getDistance() {
  // Limpa o pino TRIG
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  
  // Dispara o pulso de 10us
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // Lê o tempo de duração do pulso de eco (ida e volta)
  duracao = pulseIn(ECHO_PIN, HIGH);
  
  // Calcula a distância em cm (velocidade do som é aprox. 340m/s ou 29.1 us/cm)
  // Formula: Distância = (Duração em us * 0.034) / 2
  distancia_cm = duracao * 0.034 / 2;
  
  return distancia_cm;
}

// =================================================================
// 5. FUNÇÃO PARA CALCULAR A PORCENTAGEM DE NÍVEL
// =================================================================

int calculatePercentage(float dist_lida, float dist_maxima) {
  // 'Nivel' é a distância preenchida pelo material (Distância Máxima - Distância Lida)
  float nivel_cm = dist_maxima - dist_lida;
  
  // Evita leituras negativas (erro do sensor)
  if (nivel_cm < 0) nivel_cm = 0;
  
  // Calcula a Porcentagem de Ocupação
  int percentagem = (nivel_cm / dist_maxima) * 100;
  
  // Limita a 100%
  if (percentagem > 100) percentagem = 100;
  
  return percentagem;
}

// =================================================================
// 6. FUNÇÃO DE CONTROLE DOS LEDS (Ações Automatizadas)
// =================================================================

void setLeds(int nivel) {
  // Desliga os LEDs (exceto se o Vermelho precisar piscar)
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  
  if (nivel < LIMIAR_CRITICO) {
    // ESTADO CRÍTICO: O LED VERMELHO será controlado para piscar no loop principal.
    digitalWrite(LED_AMARELO, LOW); // Garante que Amarelo está desligado
    digitalWrite(LED_VERDE, LOW);  // Garante que Verde está desligado
    
  } else if (nivel < LIMIAR_ATENCAO) {
    // ESTADO ATENÇÃO: Amarelo Fixo
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_AMARELO, HIGH);
    
  } else {
    // ESTADO CHEIO/BOM: Verde Fixo
    digitalWrite(LED_VERMELHO, LOW);
    digitalWrite(LED_VERDE, HIGH);
  }
}

// =================================================================
// 7. SETUP - CONFIGURAÇÃO INICIAL
// =================================================================

void setup() {
  // Configuração da comunicação serial para debug (Monitor Serial)
  Serial.begin(9600);
  Serial.println("--- Sistema Autônomo de Monitoramento de Nível ---");
  Serial.print("Distância Máxima Calibrada (Vazio): ");
  Serial.print(DISTANCIA_MAXIMA_CM);
  Serial.println(" cm");

  // Configuração dos Pinos
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);

  // Desliga todos os LEDs na inicialização
  digitalWrite(LED_VERDE, LOW);
  digitalWrite(LED_AMARELO, LOW);
  digitalWrite(LED_VERMELHO, LOW);
}

// =================================================================
// 8. LOOP PRINCIPAL
// =================================================================

void loop() {
  // 1. REALIZA A MEDIÇÃO
  distancia_cm = getDistance();
  
  // 2. CALCULA O NÍVEL EM PORCENTAGEM
  nivel_porcentagem = calculatePercentage(distancia_cm, DISTANCIA_MAXIMA_CM);
  
  // 3. APLICA A LÓGICA DO LED
  setLeds(nivel_porcentagem);

  // 4. SAÍDA DE DEBUG NO MONITOR SERIAL
  Serial.print("Distância Lida: ");
  Serial.print(distancia_cm);
  Serial.print(" cm | Nível de Ocupação: ");
  Serial.print(nivel_porcentagem);
  Serial.println(" %");

  // 5. CONTROLE DO PISCA-PISCA DO LED VERMELHO (ESTADO CRÍTICO)
  // Usamos millis() para não bloquear outras funções
  if (nivel_porcentagem < LIMIAR_CRITICO) {
    unsigned long tempoAtual = millis();
    if (tempoAtual - tempoAnterior >= intervaloPisca) {
      tempoAnterior = tempoAtual;
      
      // Inverte o estado do LED Vermelho (liga/desliga)
      digitalWrite(LED_VERMELHO, !digitalRead(LED_VERMELHO));
    }
  } else {
    // Se não estiver em estado crítico, garante que o LED Vermelho está desligado
    digitalWrite(LED_VERMELHO, LOW);
    // Pequeno atraso para não sobrecarregar o loop (se o LED não estiver piscando)
    delay(500);
  }
}
