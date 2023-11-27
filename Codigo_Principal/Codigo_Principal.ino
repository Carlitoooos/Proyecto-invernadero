/* importamos las librerias necesarias para el proyecto*/
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>

/* definimos el macro printByte como write(args)  */
/* esto debido a que estamos compilando el codigo */
/* en una version de arduino mayor a la 1.0.0     */
#define printByte(args) write(args);

/* Declaracion de variables */
unsigned int temperatura = 0;
unsigned int humedad = 0;
byte selector = 0;
byte contador = 0;
char *estadosDelSuelo[] = { "Seco", "Humedo", "Mojado" };
const int valorDelAire = 630;
const int valorDelAgua = 260;
int intervalos = (valorDelAire - valorDelAgua) / 3;
unsigned int humedadDelSuelo = 0;
byte agua = 7;
byte iluminacion = 6;
byte extractor = 5;

/* creacion de objetos necesarios para el proyecto */
DHT11 dht11(2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t grado[8] = { 0xe, 0x11, 0x11, 0xe, 0x0, 0x0, 0x0 };

/* funciones para hacer el codigo más legible y de alto nivel */
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
int imprimirTemperaturaYHumedad(int temperatura, int humedad) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura:");
  lcd.print(temperatura);
  lcd.printByte(0);
  lcd.print("C");
  lcd.setCursor(0, 1);
  lcd.print("Humedad:");
  lcd.print(humedad);
  lcd.setCursor(10, 1);
  lcd.print("% RH");
}
int imprimirHumedadEnSuelo(int selector) {
  lcd.clear();
  lcd.print("Humedad en suelo");
  lcd.setCursor(0, 1);
  lcd.print(estadosDelSuelo[selector]);
}

/* inicializacion del proyecto */
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, grado);
  lcd.home();
  mensajeDeCortecia();
  lcd.clear();
  esperaDeDatos();
  pinMode(agua, OUTPUT);
  pinMode(iluminacion, OUTPUT);
  pinMode(extractor, OUTPUT);
}

/* codigo principal del proyecto */
void loop() {
  {
    /* lectura de datos */
    humedadDelSuelo = analogRead(A0);      /* leemos la humedad del suelo y la almacenamos en su respectiva variable */
    temperatura = dht11.readTemperature(); /* leemos temperatura y almacenamos en su variable */
    delay(500);                            /* esperamos 500ms antes de volver a realizar otra lectura para sincronizar con el protocolo de comunicacion del sensor DHT11*/
    humedad = dht11.readHumidity();        /* leemos humedad y almacenamos en su variable */
    delay(500);                            /* volvemos a esperar 500ms para terminar de sincronizar con el protocolo de comunicacion de comunicacion del sensor DHT11 */

    /* verificamos que las lecturas esten correctas y las imprimimos en el monitor serial */
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

    /* clasificamos estados del suelo en 3 y seleccionamos el que corresponda en el arreglo de caracteres */
    if (humedadDelSuelo > valorDelAgua && humedadDelSuelo < (valorDelAgua + intervalos)) {
      Serial.println("Mojado");
      selector = 2;
    } else if (humedadDelSuelo > (valorDelAgua + intervalos) && humedadDelSuelo < (valorDelAire - intervalos)) {
      Serial.println("Humedo");
      selector = 1;
    } else if (humedadDelSuelo < valorDelAire && humedadDelSuelo > (valorDelAire - intervalos)) {
      Serial.println("Seco");
      selector = 0;
    }

    /* alternamos la impresion de datos en la pantalla LCD cada 3 segundos */
    if (contador >= 0 && contador <= 3) {
      contador++;
      /* verificamos que las lecturas esten dentro de rangos teoricamente normales e imprimimos en la pantalla LCD */
      if (temperatura >= 0 && temperatura <= 50 && humedad >= 0 && humedad <= 100) {
        imprimirTemperaturaYHumedad(temperatura, humedad);
      }
    }
    /* alternamos la impresion de datos en la pantalla LCD cada 3 segundos */
    if (contador >= 4 && contador <= 6) {
      contador++;
      if (contador > 6) {                 
        contador = 0;                     /* reiniciamos el contador para que se cumpla el ciclo de iteracion de 3 segundos  */
      }
      imprimirHumedadEnSuelo(selector);   /* imprimimos la humedad del suelo en la pantalla LCD */
    }
  }
}
