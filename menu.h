#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <stdbool.h>
#include "beolvas.h"

//Itt határozzuk meg a menüket. A fo_menu értéke 0, az al_menü-é 1, a jatek_menu-é pedig 2. Így egyszerûen lehet majd váltogatni a menüket a mainben.
typedef enum menuk{
    fo_menu,
    al_menu,
    jatek_menu,
} menuk;

//Ezzel fogjuk eldönteni, hogy majd melyik pálya legyen kirajzolva
typedef enum palyak{
    palya1,
    palya2,
    palya3,
    palya4,
    palya5,
} palyak;

void fomenu(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font2);
void almenu(SDL_Renderer *renderer, TTF_Font *font, TTF_Font *font2, TTF_Font *font3);
void bezarasok(matrix *matrix, SDL_Renderer *renderer, SDL_Window *window, TTF_Font *font1, TTF_Font *font2, TTF_Font *font3, TTF_Font *font4, TTF_Font *font5);
void jatekmenu(SDL_Renderer *renderer, TTF_Font *font1, TTF_Font *font2, palyak jelenlegi_palya, matrix *matrix, int egySzamMerete);

#endif // MENU_H_INCLUDED
