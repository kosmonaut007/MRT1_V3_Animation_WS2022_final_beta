/*
 * Praktikumsversuch: Einführung in die Sprache C
 * Grafikausgabe-Modul
 */

// für vorgegebene Grafik Funktionen grafik_paint_point() und andere:
# include "graphic.h"
# include "config.h"
# include "engine.h"
# include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


// Funktionen zur Grafikausgabe
 void gfx_paint(void)
 {

		grafik_lock_for_painting(); 			//die paint Area wird verrieglet um die einzelnen Pixel zu setzen
		for (int i = 0; i < LD.zeilen; i++)		//iterration durch die Zielen (y-Richtung) um alle einmal aus zu lesen
		{
			for(int j = 0; j < LD.spalten; j++)	//iterration durch die Spalten (x-Richtung) um alle einmal aus zu lesen
			{
				if( LD.puffer[i+1][j+1] == 0)	//auslesen der Pixel im berechnerten Array, jeweils + 1 rechnen um zu die zusätzliche "Umrandung" des Arrays nicht zu zeichnen
				{
					grafik_paint_point(j, i, Valhalla); //setzen von dunklen Pixel, wenn Stelle im Array gleich 0 ist
				}
				else
				{
					grafik_paint_point(j, i, Christi);	//setzen von grünen Pixel, wenn Stelle im Array gleich 1 ist
				}

			}


		}
		grafik_unlock_and_show(); //entriegeln der paint Area, so dass alle neu gezeichneten Pixel auf einmal gezeichnet werden


 }




