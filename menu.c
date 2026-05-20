#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stdio.h"
#include "menu.h"
#include "alakzatok.h"
#include "debugmalloc.h"
#include "beolvas.h"

//A függvény kirajzolja a főmenü kinézetét
void fomenu(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font2) {
    //Cím kirajzolása
    cim(renderer, font2);

    //Play gomb megjelenítése
    playGomb(renderer, font);

    //Quit gomb megjelenítése
    quitGomb(renderer, font);
}

//Kirajzolja az almenü kinézetét
void almenu(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font2, TTF_Font *font3) {
    //Alcím (Levels)
    alcim(renderer, font);

    //Vissza gomb megjelenítése
    visszaGomb(renderer, font2);

    //Szintek megjelenítése
    szintek(renderer, font3);
}

//A játékmenet kirajzolása
void jatekmenu(SDL_Renderer *renderer, TTF_Font *font1, TTF_Font *font2, palyak jelenlegi_palya, matrix *matrix, int egySzamMerete) {
    //Vissza gomb
    visszaGombPause(renderer, font1);
    //Itt döntjük el, hogy melyik pálya legyen betöltve
    if(jelenlegi_palya == 0) {
        szint_megjelenit(palya1, renderer, font2, "Level 1");
        palya_kirajzol(renderer, matrix, egySzamMerete);
    }
    if(jelenlegi_palya == 1) {
        szint_megjelenit(palya2, renderer, font2, "Level 2");
        palya_kirajzol(renderer, matrix, egySzamMerete);
    }
    if(jelenlegi_palya == 2) {
        szint_megjelenit(palya3, renderer, font2, "Level 3");
        palya_kirajzol(renderer, matrix, egySzamMerete);
    }
    if(jelenlegi_palya == 3) {
        szint_megjelenit(palya4, renderer, font2, "Level 4");
        palya_kirajzol(renderer, matrix, egySzamMerete);
    }
    if(jelenlegi_palya == 4) {
        szint_megjelenit(palya5, renderer, font2, "Level 2");
        palya_kirajzol(renderer, matrix, egySzamMerete);
    }
}

//Itt zárunk be vagy szabadítunk fel mindnent
void bezarasok(matrix *matrix, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font1, TTF_Font *font2, TTF_Font *font3, TTF_Font *font4, TTF_Font *font5) {
    matrix_felszabadit(matrix);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font1);
    TTF_CloseFont(font2);
    TTF_CloseFont(font3);
    TTF_CloseFont(font4);
    TTF_CloseFont(font5);
    SDL_Quit();
}




