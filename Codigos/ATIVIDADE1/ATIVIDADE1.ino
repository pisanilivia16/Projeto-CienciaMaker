#include <LiquidCrystal_I2C.h>                          // Definindo a biblioteca LiquidCrystal_I2C para o monitor LCD.
#include <Wire.h>                                       // Definindo a biblioteca Wire, padrão de monitores LCD.
#include <HCSR04.h>                                     // Definindo a biblioteca HCSR04 para o sensor de distância/ultrassônico.

LiquidCrystal_I2C lcd(0x27,16,2);                       // Criando um LCD de 16x2 no endereço 0x27

byte triggerPin = 7;                                    // Definindo a porta de entrada de Trigger do sensor de distância.
byte echoPin = 6;                                       // Definindo a porta de entrada de Echo do sensor de distância.
double distanciaM;                                      // Definindo variável distância
const double veloSom_mpms = 0.000340;                   // Definindo a constante double veloSom_mpms.

void setup () {
  
  Serial.begin(9600);                                   // Padrão Arduino de 9600 bits por segundo.
  HCSR04.begin(triggerPin, echoPin);                    // Ativando o sensor de ditância.
  lcd.init();                                           // Inicializando o LCD
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("PROJETO");       
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("CIENCIAMAKER");
  delay(5000);
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("");                                        // Retirando o conteúdo da posição 0,0.
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("");                                        // Retirando o conteúdo da posição 0,1.
  lcd.setBacklight(LOW);                                // Desligando a luz do painel LCD.

}

void loop () {
   
  long*   times     = HCSR04.measureMicroseconds();     // Função de cálculo de tempo em *microsegundos*, presente na biblioteca.
  double  timesS    = (double)times[0];                 // Conversão de Long para Double, para posteriormente ser convertido em *segundos*.
  distanciaM = (timesS * veloSom_mpms) / 2;
  
  // Informações localizadas no LCD.
  lcd.setBacklight(HIGH);                               // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                   // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("Metros: ");
  lcd.print(distanciaM);                                // Exibição da distância em *Metros*.
  lcd.setCursor(0,1);                                   // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("Seg: "); 
  lcd.print(timesS/1000000, 5);                         // Conversão de microsegundos em segundos.
  // Fim das informações localizadas no LCD.
  
  delay(3000);
   
}
