#define ldrPin A3                                        // Definindo o pino LDR na porta A0.
#include <LiquidCrystal_I2C.h>                           // Definindo a biblioteca LiquidCrystal_I2C para o monitor LCD.                       
#include <Wire.h>                                        // Definindo a biblioteca Wire, padrão de monitores LCD.

LiquidCrystal_I2C lcd(0x27,16,2);                        // Criando um LCD de 16x2 no endereço 0x27
// Criação das variáveis.
int leitura;
float tensao;
float luz;

void setup() {
  Serial.begin(9600);
  lcd.init();                                           // Inicializando o LCD
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("PROJETO");       
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("CIENCIAMAKER");
  delay(5000);
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("                              ");          // Retirando o conteúdo da posição 0,0.
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("                              ");          // Retirando o conteúdo da posição 0,1.
  lcd.setBacklight(LOW);                                // Desligando a luz do painel LCD.
}

void loop() {
  leitura = analogRead(ldrPin);
  tensao = leitura * (5.0 / 1024);  
  luz = 4464.9*exp(-17.73*tensao);                      
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor (0,0);                                  // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("Luz: ");
  lcd.setCursor (0,1);                                  // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print(luz, 3);
  lcd.print(" unidades    ");

  delay(500);
}
