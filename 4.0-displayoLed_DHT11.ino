//https://www.youtube.com/watch?v=UJpiIpmWPVM
//https://forum.arduino.cc/t/add-second-dht11-sensor-to-eps32-arduino-code/851681
//pino 22 do esp no sck do display
//pino 21 do esp no sda do display
//para o pino data do DHT NÃO USAR os pinos D2,D12,D18,D19,D21,D22,D23,D25,D26,D27,D33,D32,D34,D35
//para o pino data do DHT     USAR os pinos D4, D5,D13,D14,D15

#include <DHT.h>
#define DHTPIN 5          // pino do esp32 para ligar o DHT11
#define DHTTYPE DHT11     // DHT sensor type (DHT11)
DHT dht (DHTPIN, DHTTYPE);//define o pino e o tipo de DHT

#include <Adafruit_SSD1306.h>
#define OLED_LARGURA 128                // Número de Pixels do display OLED (Largura)
#define OLED_ALTURA  64                 // Número de Pixels do display OLED (Altura)
#define OLED_RESET   4                  // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(OLED_LARGURA, OLED_ALTURA, &Wire, OLED_RESET);//inicialização do display SSD1306

void setup()
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);//inicialização do display e endereçamendo I2C
  display.clearDisplay();                   // Limpa p display
  dht.begin();                              //inicializa o sensor DHT
  Serial.begin(9600);                       // Initialize serial communication.
}
 
void loop() 
{
  float umidade = dht.readHumidity();        //realiza a leitura da unidade
  float temperatura = dht.readTemperature(); //realiza a leiutra da temperatura
  Serial.print("umidade: ");                 //imprimir no monitor serial o texto
  Serial.print(umidade);                     //imprmi o valor da umidade
  Serial.print("%\t");                       //imprimi a unidade e um espaço e tab
  Serial.print("Temperatura: ");             //imprimir no monitor serial o texto
  Serial.print(temperatura);                 //imprimir o valor da temperatura
  Serial.println("°C");                      //imprimir a unidade
  
  display.clearDisplay();                 // Limpa p display
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setTextColor(WHITE);            // Cor da fonte
  display.setCursor(1,8);                 // coordenada coluna=1 e linha=8 para imprimir
  display.println(" *** TEMPERATURA ***");// texto
  display.setTextSize(2);                 // Tamanho da fonte
  display.setTextColor(WHITE);            // Cor da fonte
  display.setCursor(24,16);               // coordenada coluna=24 e linha=16 para imprimir
  display.println(temperatura);           // Variável a ser impressa
  display.setCursor(83,8);                // coordenada coluna=83 e linha=8 para imprimir
  display.println(".");                   // ponto
  display.setCursor(93,16);               // coordenada coluna=93 e linha=16 para imprimir
  display.println("C");                   //texto
  
  display.setTextSize(1.5);               // Tamanho da fonte
  display.setCursor(1,33);                 // coordenada coluna=1 e linha=33 para imprimir
  display.println(" ***** UMIDADE *****");// texto
  display.setTextSize(2);                 // Tamanho da fonte
  display.setCursor(24,43);               // coordenada coluna=24 e linha=43 para imprimir
  display.println(umidade);               // Variável a ser impressa
  display.setCursor(93,46);               // Local de início do texto
  display.println("%");                   //texto
  display.display();                      //finaliza a impressão no display
  delay(1000);  
}
