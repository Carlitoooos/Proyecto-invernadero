int extractor = 13;
int bombaDeAgua = 12;
int luz = 8;

void setup() {
  pinMode(extractor, OUTPUT);
  pinMode(bombaDeAgua, OUTPUT);
  pinMode(luz, OUTPUT);
}

void loop() {
  /* el modulo rele de 2 canales tiene los bits de activacion invertidos */
  digitalWrite(extractor, true);    /* extractor apagado */
  digitalWrite(luz, false);         /* Luz apagada */
  digitalWrite(bombaDeAgua, true);  /* bomba apagada */
  delay(1000);
  digitalWrite(extractor, false);   /* extractor encendido */
  digitalWrite(luz, false);         /* Luz apagada */
  digitalWrite(bombaDeAgua, true);  /* bomba apagada */
  delay(1000);
  digitalWrite(extractor, true);    /* extractor apagado */
  digitalWrite(luz, false);         /* Luz apagada */
  digitalWrite(bombaDeAgua, false); /* bomba encendida */
  delay(1000);
  digitalWrite(extractor, true);    /* extractor apagado */
  digitalWrite(luz, true);          /* Luz encendida */
  digitalWrite(bombaDeAgua, true);  /* bomba apagada */
  delay(1000);
}
