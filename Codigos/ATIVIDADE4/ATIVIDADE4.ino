#include <LiquidCrystal_I2C.h>                        
#include <Wire.h> 
#define somPin 10
#define potPin A1

LiquidCrystal_I2C lcd(0x27,16,2);

int leitura;
float frequencia;
float tensao;

void setup(){
  Serial.begin(9600);
  pinMode(somPin, OUTPUT);
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
void loop(){
  leitura = analogRead(potPin);
  frequencia = map(leitura, 0, 1024, 0, 22000);
  
  lcd.setBacklight(HIGH); 
  lcd.setCursor(0,0);
  lcd.print("Frequencia: ");
  lcd.setCursor(0,1);
  lcd.print(frequencia);
  lcd.print(" Hz");
    
  tone(somPin, frequencia, 800);
  delay(1000);
}
