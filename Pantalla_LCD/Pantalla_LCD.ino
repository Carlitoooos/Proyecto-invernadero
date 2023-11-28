#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

#if defined(ARDUINO) && ARDUINO >= 100
#define printByte(args)  write(args);
#else
#define printByte(args)  print(args,BYTE);
#endif

DHT11 dht11(2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t grado[8]  = {0xe,0x11,0x11,0xe,0x0,0x0,0x0};

void mensajeDeCortecia() {
  lcd.blink();
  delay(2000);
  lcd.setCursor(2, 0);
  lcd.print("Invernadero");
  lcd.setCursor(2, 1);
  lcd.print("automatizado");
  lcd.noBlink();
  delay(1000);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
  lcd.scrollDisplayLeft();
  delay(500);
}
void esperaDeDatos() {
  lcd.clear();
  lcd.print("esperando datos...");
}
int imprimirTempHum(int temperatura, int humedad) {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temperatura:");
  lcd.print(temperatura);
  lcd.printByte(0);
  lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("Humedad:");
  lcd.print(humedad);
  lcd.setCursor(10,1);
  lcd.print("% RH");
}

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, grado);
  lcd.home();
  mensajeDeCortecia();
  lcd.clear();
  esperaDeDatos();
}


void loop() {
  {
    int temperatura = dht11.readTemperature(); /* leemos temperatura y almacenamos en su variable */
    delay(500);                                /* esperamos 500ms antes de volver a realizar otra lectura para sincronizar con el protocolo de comunicacion del sensor DHT11*/
    int humedad = dht11.readHumidity();        /* leemos humedad y almacenamos en su variable */
    delay(500);                                /* volvemos a esperar 500ms para terminar de sincronizar con el protocolo de comunicacion de comunicacion del sensor DHT11 */
    if (temperatura != DHT11::ERROR_CHECKSUM && temperatura != DHT11::ERROR_TIMEOUT) {
      Serial.print("Temperatura: ");
      Serial.print(temperatura);
      Serial.println(" °C");
    } else {
      Serial.print("Error al leer temperatura: ");
      Serial.println(DHT11::getErrorString(temperatura));
    }
    if (humedad != DHT11::ERROR_CHECKSUM && humedad != DHT11::ERROR_TIMEOUT) {
      Serial.print("Humedad: ");
      Serial.print(humedad);
      Serial.println("% HR");
    } else {
      Serial.print("Error al leer humedad: ");
      Serial.println(DHT11::getErrorString(humedad));
    }
    if (temperatura >= 0 && temperatura <= 50 && humedad >= 0 && humedad <= 100) {
      imprimirTempHum(temperatura,humedad);
    }
  }
}
