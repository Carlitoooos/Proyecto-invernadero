# Proyecto-invernadero
## Carpetas DMH11 y liquidcrystal_I2C
Son librerias necesarias para el codigo que no vienen por defecto en el IDE de arduino.
## Carpeta Codigo_Principal
Contiene el codigo para el proyecto
## Diagrama de flujo
Representa el flujo de control del programa de manera visual 
# Explicación del codigo
``` cpp
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT11.h>
```
Se importan tres librerías necesarias para el proyecto: Wire para la comunicación I2C, LiquidCrystal_I2C para controlar una pantalla LCD, y DHT11 para leer datos del sensor de temperatura y humedad.
``` cpp
#define printByte(args) write(args);

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
```
* Se define una macro ***printByte*** que simplifica la llamada a la función write.
* Se declaran variables para almacenar valores relacionados con la temperatura, humedad, estado del suelo, etc.
* ***estadosDelSuelo*** es un arreglo de strings que representan los estados del suelo.
* ***valorDelAire*** y ***valorDelAgua*** son umbrales utilizados para clasificar el estado del suelo.
* ***intervalos*** calcula la diferencia entre los valores de aire y agua dividido por 3.
* ***humedadDelSuelo*** almacenará la lectura analógica del sensor conectado al pin A0.
* Se definen los pines para controlar agua, iluminación y extractor.
```cpp
DHT11 dht11(2);
LiquidCrystal_I2C lcd(0x27, 16, 2);
uint8_t grado[8] = { 0xe, 0x11, 0x11, 0xe, 0x0, 0x0, 0x0 };

void mensajeDeCortecia() {
  // ... (función para mostrar un mensaje de bienvenida en la LCD)
}

void esperaDeDatos() {
  // ... (función para mostrar un mensaje de espera en la LCD)
}

int imprimirTemperaturaYHumedad(int temperatura, int humedad) {
  // ... (función para imprimir temperatura y humedad en la LCD)
}

int imprimirHumedadEnSuelo(int selector) {
  // ... (función para imprimir el estado del suelo en la LCD)
}
```
* Se crean objetos ***dht11*** y ***lcd*** de las clases ***DHT11*** y ***LiquidCrystal_I2C*** respectivamente.
* Se define un nuevo carácter personalizado en la LCD (***grado***).
* Se crean tres funciones (***mensajeDeCortecia***, ***esperaDeDatos***, ***imprimirTemperaturaYHumedad***, ***imprimirHumedadEnSuelo***) relacionadas con la presentación y visualización en la pantalla LCD.
```cpp
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
```
* Se inicia la comunicación serial a 9600 baudios.
* Se inicializa la LCD, se configura el carácter personalizado y se muestra un mensaje de bienvenida.
* Se configuran los pines agua, iluminacion y extractor como salidas.
```cpp
void loop() {
  // ... (lecturas de sensores, clasificación de estados del suelo, y presentación en la LCD)
}
```
En el bucle principal, se realizan lecturas de sensores de temperatura, humedad del aire y humedad del suelo.
Se clasifican los estados del suelo y se imprime información en la consola serial y en la pantalla LCD.
La presentación en la LCD alterna entre la temperatura/humedad y el estado del suelo cada 3 segundos.
