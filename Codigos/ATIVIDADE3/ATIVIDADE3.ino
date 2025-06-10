#include <LiquidCrystal_I2C.h>                          // Definindo a biblioteca LiquidCrystal_I2C para o monitor LCD.
#include <Wire.h>                                       // Definindo a biblioteca Wire, padrão de monitores LCD.
int PinTrigger = 5;                                     // Pino usado para disparar os pulsos do sensor
int PinEcho = 4;                                        // Pino usado para ler a saída do sensor
float TempoEcho = 0;                                    // Variável tempo do eco
const int buzzer = 10;                                  // Variável buzzer

const float velocidadeSom_mps = 340;                    // Velocidade do som em metros por segundo
const float velocidadeSom_mpus = 0.000340;              // Velocidade do som em metros por microsegundo

LiquidCrystal_I2C lcd(0x27,16,2);                       // Criando um LCD de 16x2 no endereço 0x27

void setup() {
  Serial.begin(9600);                                   // Criando um LCD de 16x2 no endereço 0x27
  pinMode(PinTrigger, OUTPUT);
  digitalWrite(PinTrigger, LOW);
  pinMode(PinEcho, INPUT);
  delay(100);
  lcd.init();                                           // Inicializando o LCD
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("PROJETO");       
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("CIENCIAMAKER");
  delay(5000);
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("                       ");                 // Retirando o conteúdo da posição 0,0.
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("                       ");                 // Retirando o conteúdo da posição 0,1.
  lcd.setBacklight(LOW);                                // Desligando a luz do painel LCD.

}

void loop() {
  DisparaPulsoUltrassonico();                           // Ativa afunção DisparaPulsoUltrassonico()
  TempoEcho = pulseIn(PinEcho, HIGH);                   // Mede duração do pulso de eco em microsegundos
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("Dist. : ");
  lcd.print(CalculaDistancia(TempoEcho) * 100);         // Distância em CM.
  lcd.print(" cm");
  delay(1000);
  // Início dos if's que determinam a nota que será tocada.
  if (CalculaDistancia(TempoEcho) * 100 > 150.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Do ");
  tone (buzzer, 262);
  delay (500);
  noTone(buzzer);
    }

  if (CalculaDistancia(TempoEcho) * 100 < 150.0 && CalculaDistancia(TempoEcho) * 100 > 120.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Re ");
  tone (buzzer, 294);
  delay (500);
  noTone(buzzer);
  }

  if (CalculaDistancia(TempoEcho) * 100 < 120.0 && CalculaDistancia(TempoEcho) * 100 > 100.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Mi ");  
  tone (buzzer, 330);
  delay (500);
  noTone(buzzer);
  }
  
  if (CalculaDistancia(TempoEcho) * 100 < 100.0 && CalculaDistancia(TempoEcho) * 100 > 80.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Fa ");
  tone (buzzer, 349);
  delay (500);
  noTone(buzzer);
  }

  if (CalculaDistancia(TempoEcho) * 100 < 80.0 && CalculaDistancia(TempoEcho) * 100 > 50.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Sol");
  tone (buzzer, 392);
  delay (500);
  noTone(buzzer);
  }

  if (CalculaDistancia(TempoEcho) * 100 < 50.0 && CalculaDistancia(TempoEcho) * 100 > 30.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: La ");
  tone (buzzer, 440);
  delay (500);
  noTone(buzzer);
  }

  if (CalculaDistancia(TempoEcho) * 100 < 30.0 && CalculaDistancia(TempoEcho) * 100 > 15.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Si ");
  tone (buzzer, 494);
  delay (500);
  noTone(buzzer);
  }

  if (CalculaDistancia(TempoEcho) * 100 < 15.0 && CalculaDistancia(TempoEcho) * 100 > 0.0){
  lcd.setCursor(0,1);
  lcd.print("Nota: Do ");
  tone (buzzer, 523);
  delay (500);
  noTone(buzzer);
  }
  
}
// Funções de cálculo das distâncias.
void DisparaPulsoUltrassonico(){
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
}

float CalculaDistancia(float tempo_us){
  return ((tempo_us * velocidadeSom_mpus) / 2);    // Calcula distância em metros
}
