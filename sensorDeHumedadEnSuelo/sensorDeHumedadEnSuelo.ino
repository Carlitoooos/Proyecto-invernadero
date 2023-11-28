const int valorDelAire = 630;
const int valorDelAgua = 260;
int intervalos = (valorDelAire - valorDelAgua) / 3;
int humedadDelSuelo = 0;
void setup() {
  Serial.begin(9600);  
}
void loop() {
  humedadDelSuelo = analogRead(A0);  
  if (humedadDelSuelo > valorDelAgua && humedadDelSuelo < (valorDelAgua + intervalos)) {
    Serial.println("Mojado");
  } else if (humedadDelSuelo > (valorDelAgua + intervalos) && humedadDelSuelo < (valorDelAire - intervalos)) {
    Serial.println("Humedo");
  } else if (humedadDelSuelo < valorDelAire && humedadDelSuelo > (valorDelAire - intervalos)) {
    Serial.println("Seco");
  }
  Serial.print("/// lectura analoga: ");
  Serial.println(humedadDelSuelo);
  delay(100);
}