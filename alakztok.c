#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include "stdio.h"
#include "menu.h"
#include "alakzatok.h"
#include "debugmalloc.h"

//A fügvény bekér egy megjelenítõt, egy betûstílust, a szöveget, amit meg szeretnénk jeleníteni, egy színt (ezt nekünk kell definiálni), végül pedig x és y koordinátákat, hogy hol jelenjen meg.
void text(SDL_Renderer *renderer, TTF_Font *font, const char *szoveg, SDL_Color szin, int hovax, int hovay){
    SDL_Surface *text;
    SDL_Texture *text_t;
    SDL_Rect hova = {0,0,0,0};

    text = TTF_RenderUTF8_Blended(font, szoveg, szin);
    if (text == NULL){
        printf("Rossz a text: %s", TTF_GetError());
        return;
    }

    text_t = SDL_CreateTextureFromSurface(renderer, text);
    if (text_t == NULL){
        printf("Rossz a text_t: %s", SDL_GetError());
        SDL_FreeSurface(text);
        return;
    }

    hova.x = hovax;
    hova.y = hovay;
    hova.w = text->w;
    hova.h = text->h;
    SDL_RenderCopy(renderer, text_t, NULL, &hova);
    SDL_FreeSurface(text);
    SDL_DestroyTexture(text_t);
}
//Elõre meghatározott színek
SDL_Color lila = {139, 66, 176, 255};
SDL_Color sarga = {255, 251, 0, 255};

//Itt találhatóak a gombok paraméterei
gombok play_gomb = {430, 300, 200, 70, "PLAY", 1};
gombok quit_gomb = {430, 450, 200, 70, "QUIT", -1};
gombok vissza_gomb = {1000, 50, 40, 40, "<", 0};
gombok lvl1 = {300, 300, 50, 50, "1", 2};
gombok lvl2 = {400, 300, 50, 50, "2", 2};
gombok lvl3 = {500, 300, 50, 50, "3", 2};
gombok lvl4 = {600, 300, 50, 50, "4", 2};
gombok lvl5 = {700, 300, 50, 50, "5", 2};

