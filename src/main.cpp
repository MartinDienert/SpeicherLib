#include <SpeicherLib.h>

Speicher speicher = Speicher();

int lesen(byte *, int);
void schreiben(byte *, int);
void datenausgeben();

void setup(){
  pinMode(2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(2, LOW);
  Serial.setTimeout(40);
  Serial.begin(115200);
  speicher.callbackLesen(lesen);
  speicher.callbackSchreiben(schreiben);
  speicher.callbackNeueDaten(datenausgeben);
  speicher.startMaster(5000);
//  speicher.setMaster(true);
//  speicher.startMDaten(30000);
//  speicher.setMDaten(true);
  while(Serial.available()){      // Puffer leeren
    Serial.read();
    delay(5);
  }
}

void loop() {
  digitalWrite(LED_BUILTIN,LOW);      // LED leuchtet
  speicher.run();
  delay(300);
  digitalWrite(LED_BUILTIN,HIGH);      // LED ist aus
}

int lesen(byte *b, int l){
  return Serial.readBytes(b, l);
}

void schreiben(byte *b, int l){
  digitalWrite(2, HIGH);
  delay(10);
  Serial.write(b, l);
  delay(5);
  digitalWrite(2, LOW);
}

void datenausgeben(){
  Serial.println();
  Serial.print("Millis: ");
  Serial.println(millis());
  Daten daten = speicher.getDaten();
  Serial.print("Typ: ");
  Serial.print(daten.typ);
  Serial.print("Spannung: ");
  Serial.print(daten.spannung);
  Serial.println(" V");
  Serial.print("SOC: ");
  Serial.print(daten.soc);
  Serial.println(" %");
  Serial.print("Strom Akku: ");
  Serial.print(daten.stromakku);
  Serial.println(" A");
  Serial.print("Strom PV: ");
  Serial.print(daten.strompv);
  Serial.println(" A");
  Serial.print("Temperatur: ");
  Serial.print(daten.temperatur);
  Serial.println(" °C");
  Serial.println();
}
