#include <LiquidCrystal.h>
#include <Keypad.h>

LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 4; //QUANTIDADE DE COLUNAS DO TECLADO

byte PinosqtdLinhas[qtdLinhas] = {4, 5, 6, 7}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {8, 9, 10,11}; //PINOS UTILIZADOS PELAS COLUNAS


 
//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
 
//INICIALIZAÇÃO DO TECLADO
Keypad keypad = Keypad( makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 
 
 
char entryStr[2];
int i=0;
int cookTemp;


void setup()
{ 
 
  Serial.begin(9600); //INICIALIZA A SERIAL
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  
  
  lcd.print("Set Temperatura"); //IMPRIME O TEXTO NO MONITOR SERIAL
  lcd.println(); //QUEBRA UMA LINHA NO MONITOR SERIAL
}

void loop()
{
  char key = keypad.getKey();

  if (key)
  {
  	if (key != '#')
    {
    	if(key =='*')
      {
    		lcd.clear();
        entryStr[0]= '0';
        entryStr[1]= '0';	
      }
      else 
      { 
        entryStr[i]= key;
        lcd.clear();
        lcd.setCursor(1,2);
        lcd.print(entryStr[i]);
        i++;
      }
    }
    else 
    {
      i=0;
      lcd.clear(); 
      lcd.setCursor(1,0); 
      lcd.print("Temperatura:");
      lcd.print(entryStr);
      cookTemp = (int) entryStr;
    } 
  
  }   
}
