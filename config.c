/*
 * lPraktikumsversuch: Einführung in die Sprache C
 * Konfigurationsdatei-Modul
 */

# include "graphic.h"
# include "config.h"
# include "engine.h"
# include "gfx.h"
// für fopen, getline, fscanf, fclose:
#include <stdio.h>

// für strncmp und memset:
#include <string.h>

// für malloc, calloc und atoi:
#include <stdlib.h>

// für zeit
#include <time.h>
	 
// Config und Dateiarbeit Funktionen

#include <sys/stat.h>

const char* filename = "settings-1.txt";
LD_main LD;

int einlesen(void)
{
	//Hilfsvariablen
	srand(time(0));
	int musterBeginn = 0;
	int musterLaenge = 0;
	int xMax2;
	int yMax2;
	int i = 0;
	char zufall = 0;


	//file öffnen
	FILE *fp = fopen(filename, "r");
	if(!fp)
		goto error_open_file;
	printf("Opened file: %s\n", filename);

	//Zeilen zählen
	char cr;
	size_t lines = 0;

	while( cr != EOF)
	{
		if( cr == '\n')
		{
			lines++;
		}
		cr = getc(fp);
	}
	printf("Number of lines: %zu\n", lines);
	rewind(fp);


	//Daten lesen und in dem array data[] Zeilenweise speichern
	{
		char *data[lines];
		char *gefundenerWert;

		for (size_t i = 0; i < lines; i++)
		{
			data[i] = NULL;
			size_t n = 0;

			getline(&data[i], &n, fp);

			if( ferror (fp))
				goto error_read_file;
		}


		//Data[] Array wird durchiteriert und nach Worten abgesucht
		for (size_t i = 0; i < lines; i++)
		{
			//printf("%s", data[i]);

			//Suchen nach Zeilen
			if (strstr(data[i], "Zeilen:") != NULL) {
			    printf("Zeilen wurde gefunden!\n");
			    gefundenerWert = strtok(data[i], " ");
			    gefundenerWert = strtok(NULL, " ");
			    //printf("%s", gefundenerWert);
			    LD.zeilen = atoi(gefundenerWert);
			    yMax2 = LD.zeilen + 2;
			}

			//Suchen nach Spalten
			if (strstr(data[i], "Spalten:") != NULL) {
			    printf("Spalten wurde gefunden!\n");
			    gefundenerWert = strtok(data[i], " ");
			    gefundenerWert = strtok(NULL, " ");
			    //printf("%s", gefundenerWert);
			    LD.spalten = atoi(gefundenerWert);
			    xMax2 = LD.spalten + 2;
			}

			//Suchen nach Schritt
			if (strstr(data[i], "Schritt:") != NULL) {
			    printf("Schritt wurde gefunden!\n");
			    gefundenerWert = strtok(data[i], " ");
			    gefundenerWert = strtok(NULL, " ");
			    //printf("%s", gefundenerWert);
			    LD.schritte = atoi(gefundenerWert);
			}

			//Suchen nach Schritte
			if (strstr(data[i], "Schritte:") != NULL) {
			    printf("Schritte wurde gefunden!\n");
			    gefundenerWert = strtok(data[i], " ");
			    gefundenerWert = strtok(NULL, " ");
			    //printf("%s", gefundenerWert);
			    LD.schritteMax = atoi(gefundenerWert);
			}

			//Suchen nach Pause
			if (strstr(data[i], "Pause:") != NULL) {
			    printf("Pause wurde gefunden!\n");
			    //printf("%s\n", data[i]);
			    gefundenerWert = strtok(data[i], " ");
			    gefundenerWert = strtok(NULL, " ");
			    //printf("%s\n", gefundenerWert);
			    LD.pause_zeit = atof(gefundenerWert);
			    //printf("%s\n", data[i]);
			}


			//Suchen nach Zufall
			if (strstr(data[i], "Zufall") != NULL) {
			    printf("Zufall wurde gefunden!\n");
			    zufall = 1;


			}

			//Suchen nach Animations-Puffer
			if (strstr(data[i], "Animations-Puffer:") != NULL) {
				printf("AnimationsPuffer wurde gefunden!\n");
				musterBeginn = i+1;
				//printf("line length: %zd\n", strlen(data[i+1])-1);
				musterLaenge = strlen(data[i+1])-1;
				break;
			}
		}


		//file schließen
		fclose(fp);


		//Erstellen der dynamischen Matrix
		LD.puffer = malloc(sizeof(int*) * yMax2);		//hier wird speicher für drei Pointer kreirrt
		for (i = 0; i<yMax2; i++)
		{
			(LD.puffer)[i]= malloc(sizeof(int) * xMax2);		//hier wird der speicher für die Arrays in x richtung kreiert, jeweils vier byte (eine Int) groß
		}


		//Matrix mit Nullen befüllen
		for(i = 0; i<yMax2; i++)
		{
			for(int j = 0; j<xMax2; j++)
			{
				(LD.puffer)[i][j] = 0;
			}
		}


		//Falls es kein Zufall geben soll
		if(!zufall){


			//Muster einlesen und in der Matrix speichern, es werden nur Einsen eingelesen, alles andere wird ignoriert
			//printf("Hier das gelesene Muster:\n");
			for(i = musterBeginn; i<lines;i++ )
			{
				int j = 0;
				while(data[i][j] != '\0')
				{
					if(data[i][j] == 120)
					{
						int posX = (int)(xMax2-musterLaenge)/2+j;
						int posY = (int)(yMax2-(lines-musterBeginn-1))/2+(i-musterBeginn);
						//printf("Position X: %d\n", posX);
						//printf("Zeilen an Muster: %d\n", lines-musterBeginn);
						(LD.puffer)[posY][posX] = 1;
					}
					//printf("%d\n", data[i][j]);
					j++;
				}
				//printf("%s", data[i]);
			}
		}


		//Falls es Zufall geben soll
		if(zufall)
		{
			for(i = 1; i<xMax2-1;i++)
			{
				for(int j = 1; j < yMax2-1;j++)
				{
					(LD.puffer)[i][j] = rand()%2;
				}
			}
			//printf("%s", data[i]);
		}

		// Matrix printen
//		printf("\nEingelesenes Muster:\n\n");
//		for(i = 0; i<yMax2; i++)
//		{
//			for(int j = 0; j<xMax2; j++)
//			{
//				printf("%d ", (LD.puffer)[i][j]);
//			}
//			printf("\n");
//		}
		printf("\n");
	}

	return 0;

	error_read_file:
			perror("fopen ");
			return 1;

	error_open_file:
			perror("getline ");
			return 2;
}


//Testfunktion für Matrixerstellung
void testMatrix()
{
	int** puffer;
	int x = 20;
	int y = 20;
	puffer = malloc(sizeof(int*) * x);		//hier wird speicher für drei Pointer kreirrt
	for (int i = 0; i<x; i++)
	{
		puffer[i]= malloc(sizeof(int) * y);		//hier wird der speicher für die Arrays in x richtung kreiert, jeweils ein byte groß
	}


	//Alles auf Null setzen
	for(int i = 0; i<x; i++)
	{
		for(int j = 0; j<y; j++)
		{
			puffer[i][j] = 0;
		}
	}




	for(int i = 0; i<x; i++)
	{
		for(int j = 0; j<y; j++)
		{
			printf("%d ", puffer[i][j]);
		}
		printf("\n");
	}



	for (int i = 0; i < x; i++)
	{
		free(puffer[i]);
		puffer[i] = NULL;
	}
	free(puffer);
	puffer = NULL;
}


void testString()
{
	printf("Test 1 erfolgreich\n");

	char test[] = "Ich habe hunger";
	printf("Test 2 erfolgreich\n");
	size_t i = 0;
	while (test[i] != '\0') {       /* Stop looping when we reach the null-character. */
	    printf("%c\n", test[i]);    /* Print each character of the string. */
	    i++;
	}
	printf("%s", test);
}
