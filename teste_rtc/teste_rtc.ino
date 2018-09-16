#include <Wire.h>        //Biblioteca para manipulação do protocolo I2C
#include <DS3231.h>      //Biblioteca para manipulação do DS3231
 
DS3231 rtc;              //Criação do objeto do tipo DS3231
RTCDateTime dataehora;   //Criação do objeto do tipo RTCDateTime
 
void setup()
{
  Serial.begin(9600);     //Inicialização da comunicação serial
  rtc.begin();            //Inicialização do RTC DS3231
 
  rtc.setDateTime(__DATE__, __TIME__);   //Configurando valores iniciais 
                                         //do RTC DS3231
}
 
void loop()
{
  dataehora = rtc.getDateTime();     //Atribuindo valores instantâneos de 
                                     //data e hora à instância dataehora
 
 
  Serial.print(dataehora.year);     //Imprimindo o Ano   
  Serial.print("-");
  Serial.print(dataehora.month);    //Imprimindo o Mês
  Serial.print("-");
  Serial.print(dataehora.day);      //Imprimindo o Dia
  Serial.print(" ");
  Serial.print(dataehora.hour);     //Imprimindo a Hora
  Serial.print(":");
  Serial.print(dataehora.minute);   //Imprimindo o Minuto
  Serial.print(":");
  Serial.print(dataehora.second);   //Imprimindo o Segundo
  Serial.println("");
 
  delay(1000);     //Tempo p atualização do valor enviado pela porta
                   //serial
}