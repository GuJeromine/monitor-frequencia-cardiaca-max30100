#include <Wire.h> //Biblioteca para comunicação I2C
#include "MAX30100_PulseOximeter.h" //Biblioteca para uso do sensor de frequência cardíaca e oxímetro MAX30100 
#include <LiquidCrystal.h>          // Biblioteca para o display LCD 

#define REPORTING_PERIOD_MS     1000 // Intervalo entre a medição de cada amostra

// LCD RS  -> Arduino D3
// LCD EN  -> Arduino D4
// LCD D4  -> Arduino D5
// LCD D5  -> Arduino D6
// LCD D6  -> Arduino D7
// LCD D7  -> Arduino D8
const int rs = 3, en = 4, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

uint32_t tsLastReport = 0; // Tempo da última amostra detectada

PulseOximeter pox; //Declaração objeto pox, tipo PulseOximeter que é nativo da biblioteca MAX30100_PulseOximeter.h.

void onBeatDetected() { //Função executada quando um pulso é detectado
  Serial.println("Batimento detectado");
}

void setup() {
  Serial.begin(9600); //Inicialização da comunicação serial
  Serial.print("Iniciando funcionamento do sensor ");
  lcd.begin(16, 2); // Inicia o LCD com 16 colunas e 2 linhas
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  if (!pox.begin())  //Testa a comunicação com o sensor
  {
    Serial.println("Falhou ! "); //Se a comunicação não foi realizada corretamente exibe a mensagem "Falhou"
    lcd.setCursor(0, 1);
    lcd.print("Falhou ! ");
    for (;;);
  } else
  {
    lcd.setCursor(0, 1);
    lcd.print("Sucesso ! ");
    Serial.println("Sucesso ! "); //Se a comunicação foi realizada com sucesso exibe a mensagem "Sucesso !"
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA); // Define que o sensor use 7,6 mA para o led, quanto maior a corrente, mais brilhante será o LED e mais profundamente ele atinge a pele
  pox.setOnBeatDetectedCallback(onBeatDetected); // Registra todas as vezes em que um batimento for detectado
}

void loop() {
  pox.update(); //Atualiza a leitura do sensor
  float batimento= pox.getHeartRate();
  float oxigenacao = pox.getSpO2();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) { //Imprime a leitura em intervalos de 1000ms,  tcLastReport para armazenar a hora em que ocorreu o último batimento cardíaco em milissegundos.
    if (batimento > 30 && batimento < 220 && oxigenacao > 80) {
    lcd.clear();
    
    lcd.setCursor(0, 0);
    Serial.print("Taxa de Batimento : ");
    Serial.print(pox.getHeartRate()); // Faz a leitura de batimento cardíaco
    lcd.print("BPM: ");
    lcd.print(batimento, 1); // Imprime o valor com 1 casa decimal
    lcd.setCursor(0, 1);
    Serial.print("bpm / Saturacao sangue(SP02) : ");
    Serial.print(pox.getSpO2()); //Realiza a leitura da saturação do sangue
    Serial.println("%");
    lcd.print("SpO2: ");
    lcd.print(oxigenacao, 0); // Imprime o valor como um inteiro
    lcd.print("%");
    

    tsLastReport = millis();
    }
  }
}