/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Nutzerinteraktions-Modul
 */

#include "ui.h"

// für vorgegebene UI Funktionen: grafik_user_input()
# include "graphic.h"
.pause=1
// für die Funktion `exit`
#include <stdlib.h>



//Funktion zur Erkennung und Auswertung von Eingaben


void input()
{
	//Bei jedem Schritt kann es eine neue Eingabe geben.
	//Die Schleife wird so lange wiederholt bis alle Schritte ausgeführt wurden.
	while(LD.schritte<LD.schritteMax)
	{

		//In jedem Schritt wird neu gezeichnet, unabhängig davon ob sich etwas verändert hat
		()gfx_paint();
		if(LD.pauseTrue==0)
		{
			LD.schritte ++;
			berechnung();
		}

		// Getätigte Nutzereingaben verarbeiten.
		// 100 Millisekunden auf Nutzereingabe warten,
		// dann mit Programmablauf fortfahren.
		switch( grafik_user_input(LD.pause_zeit*1000) ){
		case Beenden:
			// Auf die Taste `q` und "Fenster schließen" reagieren.
			return;
		case Pause:
			//Wenn die Leertaste gedrückt wird, wird die Animation pausiert
			printf("Pause\n");

			//Die Animation wird in Abhängigkeit von Vorzustand pausiert oder fortgesetzt
			if(LD.pauseTrue == 0)
			{
				LD.pauseTrue = 1;
			}
			else
			{
				LD.pauseTrue = 0;
			}
			continue;
		case Schritt:
			//Wenn die Punkt-Taste gedrückt wird, wird die Animation pausiert und ein Schritt ausgeführt
			printf("Schritt\n");

			LD.pauseTrue = 1;
			berechnung();
			continue;
		default:
			// Alle anderen Nutzeraktionen ignorieren.
			continue;
		}
	}
} // Ende while(1)

