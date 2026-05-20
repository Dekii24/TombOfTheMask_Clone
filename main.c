#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "stdio.h"
#include "beolvas.h"
#include "menu.h"
#include "alakzatok.h"
#include "iranyitas.h"
#include "ablak.h"
#include "statisztika.h"
#include "debugmalloc.h"

int main(int argc, char *argv[]) {

    //Létrehozzuk az ablakot
    SDL_Window *window;
    SDL_Renderer *renderer;
    ablak("Tomb of the Mask", 1080, 720, &window, &renderer);

    SDL_TimerID id = SDL_AddTimer(20, idozit, NULL);

    matrix matrix;
    const int egySzamMerete = 60;
    beleolvas("palya1.txt",&matrix);
    matrix_feltolt("palya1.txt", &matrix);

    statisztikak statisztika;
    statisztika_ertekek(&statisztika);

    //Itt adjuk meg a betűstílust
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("C:/Windows/Fonts/BAUHS93.ttf",64);
    TTF_Font *font_nyil = TTF_OpenFont("C:/Windows/Fonts/BAUHS93.ttf",50);
    TTF_Font *font_pause = TTF_OpenFont("C:/Windows/Fonts/BAUHS93.ttf",35);
    TTF_Font *font2 = TTF_OpenFont("C:/Windows/Fonts/OCRAEXT.ttf",80);
    TTF_Font *font_szamok = TTF_OpenFont("C:/Windows/Fonts/OCRAEXT.ttf", 50);

    palyak jelenlegi_palya;

    menuk jelenlegi_menu = fo_menu;
    bool fut = true;

    while(fut) {     //Addig fut a program amíg a fut változó hamis nem lesz
        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type){
            case SDL_QUIT:
                fut = false;
                break;

            case SDL_MOUSEBUTTONDOWN: //Egér lenyomásának vizsgálata
                gomb_vizsgalat(event, &matrix, &jelenlegi_menu, &jelenlegi_palya, &fut);
            break;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        //Itt megadjuk midnegyik menünek, hogy mit kell tartalmaznia (mit jelenitsen meg a kepernyőn.
        switch(jelenlegi_menu) {
            case fo_menu:
                fomenu(renderer, font, font2);
                break;

            case al_menu:
                almenu(renderer, font2, font_nyil, font_szamok);
                break;

            case jatek_menu:
                jatek_iranyitas(event, &matrix, &jelenlegi_menu, &statisztika);
                jatekmenu(renderer, font_pause, font2, jelenlegi_palya, &matrix, egySzamMerete);
        }
        SDL_RenderPresent(renderer);
    }
    //A játék bezárását követően a bezaras felveszi a bezárás időpontját, majd a statisztika.txt-be kiirja az adatokat
    statisztika.bezaras = time(NULL);
    statisztika_kiiras(&statisztika, "statisztika.txt");

    //Bezárás
    bezarasok(&matrix, renderer, window, font, font2, font_nyil, font_pause, font_szamok);
    SDL_RemoveTimer(id);
    return 0;
}
