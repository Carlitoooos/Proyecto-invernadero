#include <DHT11.h>

DHT11 dht11(2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  int temperatura = dht11.readTemperature();    /* leemos temperatura y almacenamos en su variable */
  delay(500);                                   /* esperamos 500ms antes de volver a realizar otra lectura para sincronizar con el protocolo de comunicacion del sensor DHT11*/
  int humedad = dht11.readHumidity();           /* leemos humedad y almacenamos en su variable */
  delay(500);                                   /* volvemos a esperar 500ms para terminar de sincronizar con el protocolo de comunicacion de comunicacion del sensor DHT11 */
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
}
