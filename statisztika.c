#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stdio.h"
#include "statisztika.h"
#include "debugmalloc.h"
#include "menu.h"

//Itt állítjuk alap helyzetbe a statisztika adatait
void statisztika_ertekek(statisztikak *statisztika) {
    statisztika->inditas = time(NULL);
    statisztika->teljesitett = 0;
    statisztika->bezaras = 0;
    statisztika->mennyitJatszott = 0;
}

//Itt írjuk ki a statisztika.txt fájlba a statisztikákat. Figyelünk arra hogy minden mûsodpercben, percben és órában se csússzon el a fájlba történõ kiírás.
void statisztika_kiiras(statisztikak *statisztika, const char *fajlnev) {
    FILE *fajl = fopen(fajlnev, "w");

    statisztika->mennyitJatszott = difftime(statisztika->bezaras, statisztika->inditas);

    fprintf(fajl, "=====~Legutóbbi játék statisztikái~=====\n");
    fprintf(fajl, "|--------------------------------------|\n");

    if(statisztika->teljesitett < 10){
        fprintf(fajl, "|        Teljesített szintek: %d        | \n", statisztika->teljesitett);
    }
    if(statisztika->teljesitett >= 10 && statisztika->teljesitett < 100){
        fprintf(fajl, "|        Teljesített szintek: %d       | \n", statisztika->teljesitett);
    }
    if(statisztika->teljesitett >= 100 && statisztika->teljesitett < 1000){
        fprintf(fajl, "|        Teljesített szintek: %d      | \n", statisztika->teljesitett);
    }
    if(statisztika->mennyitJatszott < 10){
        fprintf(fajl, "|        Játékidõ: %.0f másodperc         | \n", statisztika->mennyitJatszott);
    }
    if(statisztika->mennyitJatszott >= 10 && statisztika->mennyitJatszott < 60){
        fprintf(fajl, "|        Játékidõ: %.0f másodperc        | \n", statisztika->mennyitJatszott);
    }
    if(statisztika->mennyitJatszott >= 60 && statisztika->mennyitJatszott < 600){
        fprintf(fajl, "|        Játékidõ: %.0f perc              | \n", statisztika->mennyitJatszott / 60);
    }
    if(statisztika->mennyitJatszott >= 600 && statisztika->mennyitJatszott < 3600){
        fprintf(fajl, "|        Játékidõ: %.0f perc             | \n", statisztika->mennyitJatszott / 60);
    }
    if(statisztika->mennyitJatszott >= 3600){
        fprintf(fajl, "|        Játékidõ: %.0f óra               | \n", statisztika->mennyitJatszott / 3600);
    }
    fprintf(fajl, "|--------------------------------------|");

    fclose(fajl);

}
