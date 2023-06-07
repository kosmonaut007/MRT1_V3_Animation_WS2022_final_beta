/* BOF MAIN_C
 Praktikumsversuch: Einführung in die Sprache C
 Haupt-Programm, hallo das ist ein probiertes Lebenszeichen
 */
#include "graphic.h"
#include "config.h"
#include "engine.h"
#include "gfx.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Variablendefinition
int xMax;
int yMax;
int step;
int stepMax;
float delay;
int** puffer;


// Forwarddeklaration der später definierten Hilfsfunktionen:
void goodbye_msg(void);
static void init_exit(void);


int main (void)
{

		//registireren einer Hilfsfunktion, welche bei jedem Programmende einen Text ausgibt.
        init_exit();
	

        //Werte Einlesen
        einlesen();


        //Erzeugt das Anteigefenster und den ersten Zustand.
		grafik_init_window();
		grafik_create_paint_area(0,LD.spalten,0,LD.zeilen,LD.spalten,LD.zeilen);
		gfx_paint();

		printf("\n");


		LD.pauseTrue = 0;


		// Blockierender Dialog, einmalig anzeigen.
		// Solange der Dialog angezeigt wird, wird die Grafik nicht neu gezeichnet.
		// Informiert den Nutzer wie er das Programm abbrechen kann.

		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION,
					 "MRT 1 - V3 - Information",
					 "MRT 1 - V3 - Farbdemonstration\n\n"
					 "Nach dem Schließen dieses Dialogs,\n"
					 "kann die Taste 'q' verwendet werden "
					 "um das Programm zu beenden.\n",
					 NULL);

		// Alle bisherigen Tastatureingaben verwerfen.
		while (grafik_user_input(10) > Fehler);

		// Startet den Hauptteil des Programms mit dem Zyklischen Duchlauf aus zeichnen und berechnen und beachtet die user Eingabe.
		input();


}


// -- Hilfsfunktionen ---
static void init_exit(void)
{
        if(atexit(goodbye_msg)){
                fprintf(stderr, "Fehler bei Registrierung der Exitfunktion\n");
                exit(-1);
        }
}

void goodbye_msg(void)
{
        printf("MRT1, V3, Programm beendet.\n");
}

/* EOF MAIN_C */
