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
* Se define una macro *printByte* que simplifica la llamada a la función write.
* Se declaran variables para almacenar valores relacionados con la temperatura, humedad, estado del suelo, etc.
* *estadosDelSuelo* es un arreglo de strings que representan los estados del suelo.
* *valorDelAire* y *valorDelAgua* son umbrales utilizados para clasificar el estado del suelo.
* *intervalos* calcula la diferencia entre los valores de aire y agua dividido por 3.
* *humedadDelSuelo* almacenará la lectura analógica del sensor conectado al pin A0.
* Se definen los pines para controlar agua, iluminación y extractor.
