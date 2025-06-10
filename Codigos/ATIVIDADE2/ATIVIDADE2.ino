#include <OneWire.h>                                              // Definindo a biblioteca OneWire para o sensor de temperatura DS18B20.
#include <DallasTemperature.h>                                    // Definindo a biblioteca DallasTemperature para o sensor de temperatura DS18B20.
#include <LiquidCrystal_I2C.h>                                    // Definindo a biblioteca LiquidCrystal_I2C para o monitor LCD.
#define    ONE_WIRE_BUS     3                                     // Especificando a porta de sinal do sensor de temperatura DS18B20.

OneWire oneWire(ONE_WIRE_BUS);                                    // Definindo o objeto oneWire.
DallasTemperature sensorT(&oneWire);                              // Definindo como sensorT o objeto que irá detectar a temperatura.
DeviceAddress sensor1;                                            // Definindo como sensor1 o sensor de temperatura que será localizado.
LiquidCrystal_I2C lcd(0x27,16,2);                                 // Criando um LCD de 16x2 no endereço 0x27. 

void mostra_endereco_sensor(DeviceAddress deviceAddress);         // Função para mostrar endereço do sensor (sensor1).
float tempMin = 999;                                              // Variável que armazena temperatura mínima      
float tempMax = 0;                                                // Variável que armazena temperatura máxima
int c = 0;                                                        // Definindo a variável c do loop como 0.

void setup() 
{
  Serial.begin(9600);                                             // Padrão Arduino de 9600 bits por segundo.
  sensorT.begin();                                                // Inicializa o sensor de temperatura.
  lcd.init();                                                     // Inicializando o LCD
  lcd.setBacklight(HIGH);                                         // Liga a luz do painel LCD (melhor visualização).
  lcd.setCursor(0,0);                                             // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("PROJETO");       
  lcd.setCursor(0,1);                                             // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("CIENCIAMAKER"); 
  delay(5000);
  lcd.setCursor(0,0);                                            // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.
  lcd.print("                ");                                 // Retirando o conteúdo da posição 0,0.
  lcd.setCursor(0,1);                                            // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
  lcd.print("                ");                                 // Retirando o conteúdo da posição 0,1.
  
  // Localiza e mostra enderecos dos sensores.
  
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensorT.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  
  if (!sensorT.getAddress(sensor1, 0)) 
    Serial.println("Sensores nao encontrados !"); 
     
  // Mostra o endereco do sensor encontrado no barramento.
  
  Serial.print("Endereço sensor: ");
  mostra_endereco_sensor(sensor1);
  
  // Fim da localização de sensores no Monitor Serial.
} 

void loop() 
{
  sensorT.requestTemperatures();                                // Função que irá requisitar a temperatura encontrada no sensor.                         
  double tempC = sensorT.getTempC(sensor1);                     // Variável que irá comportar a temperatura em °Celsius.

  // If's que determinam a temperatura mínima e máxima registradas a cada medição.
  if (tempC < tempMin){
    tempMin = tempC;
  }
  if (tempC > tempMax){
    tempMax = tempC;
  }
  
  // If e Else que fazem o Arduino continuar medindo temperaturas antes de mostrar a máxima e a mínima. 
  if (c < 10){
    lcd.setCursor(0,0);                                         // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.                               
    lcd.print("Temperatura: ");
    lcd.setCursor(0,1);                                         // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.
    lcd.print(tempC);
    lcd.print (" Celsius");
    delay(500);
  }else{
    lcd.setCursor(0,0);                                         // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.                                   
    lcd.print("             ");                                 // Retirando o conteúdo da posição 0,0.                                       
    lcd.setCursor(0,1);                                         // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.                                   
    lcd.print("             ");                                 // Retirando o conteúdo da posição 0,1.                                       
    lcd.setCursor(0,0);                                         // Informações passarão a ser inseridas a partir da posição 0,0 do LCD.                
    lcd.print("Max: ");                                           
    lcd.print(tempMax); 
    lcd.setCursor(0,1);                                         // Informações passarão a ser inseridas a partir da posição 0,1 do LCD.                
    lcd.print ("Min: ");
    lcd.print(tempMin);
    delay(5000);
    c = 0;
  }
  c += 1;                                                       // Soma necessária para fazer o loop prosseguir.
} 

// Função para mostrar endereço do sensor.
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
