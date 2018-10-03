#include <OneWire.h>
#include <Wire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>
 
// Porta do pino de sinal do DS18B20
#define tempSensorPin 13

// Porta do pino de sinal do Relay
#define relayPin 11
 
// Teclado matricial
const byte linhas = 4; //4 linhas
const byte colunas = 4; //4 colunas

const char matrizteclado[linhas][colunas] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
const byte pinoslinhas[linhas] = {9,8,7,6}; //pinos utilizados nas linhas
const byte pinoscolunas[colunas] = {5,4,3,2}; //pinos utilizados nas colunas
 
//inicializando o teclado
Keypad teclado = Keypad( makeKeymap(matrizteclado), pinoslinhas, pinoscolunas, linhas, colunas );

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(tempSensorPin);
 
// Armazena temperatura de cozimento
float cookTemp;
float cookTempTop;
float cookTempBottom;
bool isRelayOn; 

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;
 
// Inicializa o LCD
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);
 
void setup(void)
{
  Serial.begin(9600);
  sensors.begin();
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
  // Inicia LCD
  lcd.begin(16, 2);
  // Declara pin do relay
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  
}
 
void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}
 
void loop()
{
  char tecla = teclado.getKey(); // verifica se alguma tecla foi pressionada

  if((teclado.getState() == HOLD) && (tecla == 'A')){
    Serial.print("Setar Temperatura");
    // chama função de setCookTemp
  }

  // Le a informacao do sensor
  sensors.requestTemperatures();
  float tempAtual = sensors.getTempC(sensor1);

  Serial.print("Temp C: ");
  Serial.print(tempAtual);
  if (isRelayOn){
    Serial.print(" Relay está Ligado.");
  }
  else {
    Serial.print(" Relay está Desligado.");
  }
  Serial.print("\n");

  // se temp tiver abaixo do minimo e ebulidor desligado, liga o ebulidor
  if ((tempAtual <= cookTempBottom) && !isRelayOn) 
  {
    digitalWrite(relayPin, LOW);
    isRelayOn = true;
  }

  if (tempAtual >= cookTempTop)
  {
    digitalWrite(relayPin, HIGH);
    isRelayOn = false;
  }
   
  delay(3000);
}
