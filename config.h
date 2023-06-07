#ifndef CONFIG_HH
#define CONFIG_HH


typedef struct laufzeitdaten{

	int zeilen;
	int spalten;
	int schritte;
	double pause_zeit;
	int **puffer;

	int schritteMax;
	int pauseTrue;
}LD_main;
extern LD_main LD;

// Config Schnittstelle
int einlesen(void);
void testMatrix();
void testString();

#endif //CONFIG_HH
