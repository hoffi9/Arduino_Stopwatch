# Arduino_Stopwatch
Stopwatch mit einem Arduino Nano und einer externen Stoppuhr (die einfach da war)

Das soll das Projekt können:
Realisiert soll über den Nano eine Stoppuhr mit zwei Buttons:
Button A soll toggeln zwischen start und stop, ohne Reset wird bei starten immer beim alten Wert weiter gezählt.
	Das soll später über den "Schlagkopf" passieren.
Button B soll nur dem Reset dienen.

Startverhalten:
	- große Stoppuhr zeigt 000
	- Zustand "Reset"

Zustände:
Reset (Uhren auf 0,0, nix läuft)
Läuft
Stop

Verhalten:
Reset: 
	- Button A: Startet Uhr, reizt S1 (Pin1 der Stoppuhr), Zustandswechsel in "Läuft"
	- Button B: Bleibt in Reset
	- Kl.Display: zeigt "0,00s" /LF "Hau drauf!   :-)"
	
Läuft:
	- Button A: Stoppt Uhr, reizt S2 (Pin2 der Stoppuhr), Zustandswechsel in "Stop"
	- Button B: Stoppt und resettet Uhr, reizt Pin3 der Stoppuhr), Zustandswechsel in "Reset"
	- Kl. Display: zeigt Zeit in "x,xxs" /LF "Läuft…" (Refreshrate 100ms)
Stop:
	- Button A: Lässt die Stoppuhr weiterlaufen, reizt S1 (Pin1 der Stoppuhr), Zustandswechsel in "Läuft"
	- Button B: resettet Uhr, reizt Pin3 der Stoppuhr), Zustandswechsel in "Reset"
	- Kl.Display: zeigt Zeit in "x,xxs" /LF "Angehalten"
	


Benötigt:
I2C 16x2 Display
Arduino nano
Stoppuhrmodul
3x Relais Modul
2x Button
Verbinder
Netzteil![image](https://user-images.githubusercontent.com/27030642/111083034-c5869c80-850b-11eb-9820-b06d98dd73d8.png)
