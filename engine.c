/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Berechnungs-Modul
 */

# include "graphic.h"
# include "config.h"
# include "engine.h"
# include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Engine Quellcode:
//	Dieser Teil des Programms ist dafür zuständig den nächsten Animationsschritt ausgehend vom aktuellen Zustand zu berechnen.
//	Benötigt:
//	Anzahl der Zeilen und Spalten
//	Aktuellen Animationspuffer
void berechnung(void)
{
	int row,col;
	int b[LD.zeilen+2][LD.spalten+2];// erzeugt eine Zwischenmatrix des nächsten Animationsschrittes.

	memset(b, 0, sizeof(b));// setzt die b Matrix auf 0.


// iteriert zeilenweise durch jedes element des Puffer Arrays.
	for(row=0; row<LD.zeilen+2; row++)
	{
		for(col=0;col<LD.spalten+2;col++)
		{
			// Iteriert durch die umliegenden Felder im Array.
			// "count" ist die Anzahl an Nachbarn des etrachteten Feldes
			int count=0;
			for(int h=row-1; h<=row+1; h++)
			{
				for(int l=col-1;l<=col+1;l++)
				{
					// Kontrolle ob das Feld, welches gerade angeschaut wird, außerhalb des Arrays liegt oder das Feld selber ist.
					if((h<0 || l<0) || (h>=LD.zeilen+2 || l>=LD.spalten+2) || (h==row && l==col))
					{
						continue;
					}
					// Falls es ein mögliches nachbar Feld ist wird geschaut ob es belegt ist.
					// Wenn ja wird der Nachbar counter hochgezählt
					if(LD.puffer[h][l]==1)
					{
						count++;
					}
				}
			}

			// Kontrolliert die Regeln des Spiels für den Folgezustand

			// Wenn das Feld belegt ist und es 2 oder 3 Nachbarn hat bleibt es belegt.
			// Regel 3
			if(LD.puffer[row][col]==1 && (count==2 || count==3)){
				b[row][col]=1;
			}

			// Wenn es nicht belegt ist und exakt 3 Nachbarn hat wird es belegt.
			// Regel 1
			else if(LD.puffer[row][col]==0 && count==3){
				b[row][col]=1;
			}

			// In allen anderen Fällen(mehr als 3 oder weniger als 2 Nachbarn) wird es nicht belegt.
			// Regel 2,4
			else{
				b[row][col]=0;
			}
		}
	}


	// Überschreibt den aktuellen Animationsschritt mit dem neu berechneten.
	for(row=0; row< LD.zeilen+2; row++)
	{
		for(col=0; col< LD.spalten+2; col++)
		{
			LD.puffer[row][col]=b[row][col];
		}
	}


}

