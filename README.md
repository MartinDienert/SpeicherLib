# SpeicherLib

Bibliothek zum auslesen der Daten eines DMEGC M01 Speichers über die serielle RS485 Schnittstelle.

## Verwendung
```
#include <SpeicherLib.h>
```
Die Bibliothek in dein Projekt einfügen.
```
Speicher speicher = Speicher();
```
Das Objekt erstellen.
```
int lesen(byte *b, int l){
  return Serial.readBytes(b, l);
}
```
Callbackfunktion zum lesen der Daten von der Schnittstelle.
```
void schreiben(byte *b, int l){
  digitalWrite(2, HIGH);
  delay(10);
  Serial.write(b, l);
  delay(5);
  digitalWrite(2, LOW);
}
```
Callbackfunktion zum schreiben der Daten auf die Schnittstelle. Ist eine Umschaltung zwischen lesen und schreiben nötig kann dies hier erfolgen.
```
void datenausgeben(){
  Serial.println();
  Serial.print("Millis: ");
  Serial.println(millis());
  Daten daten = speicher.getDaten();
  Serial.print("Typ: ");
  Serial.println(daten.typ);
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
```
Diese Funktion wird aufgerufen wenn neue Daten gelesen wurden.
```
void setup(){
  pinMode(2, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(2, LOW);
  Serial.setTimeout(40);
  Serial.begin(115200);
```
Vorbereiten der Schnittstelle.
```
speicher.callbackLesen(lesen);
  speicher.callbackSchreiben(schreiben);
  speicher.callbackNeueDaten(datenausgeben);
```
Die Callbackfunktionen an das SpeicherLib-Objekt übergeben.
```
speicher.startMaster(5000);
```
Der Mastermodus wird in 5 Sekunden gestartet.

```
speicher.startMDaten(30000);
```
Das Telegramm "mehr Daten" (App geöffnet) wird in 30 Sekunden gesendet und dann alle 4 Minuten wiederholt. Die Zeit kann in der Konstante **mDaten_Interval** in der SpeicherLib.h eingestellt werden.
```
while(Serial.available()){      // Puffer leeren
    Serial.read();
    delay(5);
  }
}
```
Der RX-Puffer wird gelesen und die Daten verworfen.
```
void loop() {
  digitalWrite(LED_BUILTIN,LOW);      // LED leuchtet
  speicher.run();
  delay(300);
  digitalWrite(LED_BUILTIN,HIGH);      // LED ist aus
}
```
Die Funktion run des Speicherobjektes muss in der loop-Funktion aufgerufen werden.

