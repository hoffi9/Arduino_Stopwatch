# include <LiquidCrystal.h>
# include <OneButton.h>
int TASTER_START_STOP = 7;
int TASTER_RESET = 8;
float REFRESH_CYCLE = 500; //Zeit in ms, nach der Bild neu geschrieben wird im State running

// Name des Tasters (Constructor)
OneButton StartStopTaster(TASTER_START_STOP, true, true);
OneButton ResetTaster(TASTER_RESET, true, true);


// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Variablen der Zeit
float StartZeit = 0;
float VerstricheneZeit = 0;
float Sekunden = 0;
float LetzerRefreshBildschirm = 0;
bool Anzeige = true;

// TasterStatus sorgt für Start/Neustart

int StopWatchState = 1; //1 Reset, 2 run, 3 stop 
float LaufZeitFreeze = 0;

void setup() {
 // set up the LCD's number of columns and rows:
 lcd.begin(16, 2);
 lcd.print("0.0s");
 lcd.setCursor(0, 1);
 lcd.print("Hau drauf! :-)");

 //serielle Komm starten
 Serial.begin(9600); 

 // Aktionen dem Modus des Tasters zuordnen
 StartStopTaster.attachClick(einKlick1);
 ResetTaster.attachClick(einKlick2);

 /*
 Anzahl der Millisekunden festlegen
 Standardwerte gesetzt:
 PressTicks: 1000
 ClickTicks: 600
 DebounceTicks: 50
 wenn die Standardwerte gesetzt werden sollen
 können die nächsten Zeilen auskommentiert werden
 */
 StartStopTaster.setPressTicks(1000);
 StartStopTaster.setClickTicks(500);
 StartStopTaster.setDebounceTicks(50);

 ResetTaster.setPressTicks(1000);
 ResetTaster.setClickTicks(500);
 ResetTaster.setDebounceTicks(50);

}

void loop() {
  // Taster alle 10 Millisekunden abfragen
 StartStopTaster.tick();
 ResetTaster.tick();
 delay(10);
 if ((StopWatchState == 2) and (LetzerRefreshBildschirm - millis()<REFRESH_CYCLE))  {
  LetzerRefreshBildschirm = millis();
  //Serial.print("Ausgabe: ");
  //Serial.println(LetzerRefreshBildschirm);
  // Ausgabe LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(Ausgabe(LaufZeit(StartZeit)) + " s");
  lcd.setCursor(0, 1);
  lcd.print("laeuft...");
 }
}

void einKlick1()
{
 switch (StopWatchState){
  case 1: //reset
    Serial.println("Case 1");
    StartZeit = millis();
    LetzerRefreshBildschirm = StartZeit;
    StopWatchState=2;
    break;
  case 2: //run
    Serial.println("Case 2");
    LaufZeitFreeze = LaufZeit(StartZeit);
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print(Ausgabe(LaufZeitFreeze) + " s");
    lcd.setCursor(0, 1);
    lcd.print("angehalten");

    StopWatchState=3;
    break;
  case 3://stop
  Serial.println("Case 3");
    //Uhr soll weiterlaufen, also state=2=run
    StartZeit = millis()-LaufZeitFreeze*1000;
//    Serial.println(StartZeit);
//    Serial.println(millis());
//    Serial.println(LaufZeitFreeze);
    StopWatchState=2;
    // Hier noch einfügen, dass Pin1 der Stopuhr gereizt werden muss

    break;

 }

}

void einKlick2()
{
  lcd.setCursor(0, 0);
  lcd.print("0.00 s");
  lcd.setCursor(0, 1);
  lcd.print("Hau drauf! :-)");
  StopWatchState=1;
  //Hier noch einfügen, dass Pin3 der Stoppuhr gereizt werden muss
}

float LaufZeit(float lokStartZeit){
 // Zeit berechnen
 //float Sekunden;
 //String Ergebnis; 
 Serial.println(lokStartZeit);
 Serial.println(millis());
 VerstricheneZeit = millis() - lokStartZeit; //millis()-(millis()-Laufzeitfreeze)
 Sekunden = VerstricheneZeit / 1000;

 return Sekunden;
}

String Ausgabe(float value){
 String GesamtSekunden = String(value);
 // . durch , ersetzen
 GesamtSekunden.replace(".", ",");
 // Ausgabe im Seriellen Monitor
 //Serial.println("Sekunden insgesamt: " + GesamtSekunden);

 // Sekunden in String umwandeln
 // damit . durch , ersetzt werden kann
 String AnzahlSekunden = String(Sekunden);
 // . durch , ersetzen
 AnzahlSekunden.replace(".", ",");
 //Ergebnis = AnzahlSekunden;
 return AnzahlSekunden;
}
