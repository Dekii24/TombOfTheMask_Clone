#ifndef ALAKZATOK_H_INCLUDED
#define ALAKZATOK_H_INCLUDED
#include "menu.h"
#include "beolvas.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>

void text(SDL_Renderer *renderer, TTF_Font *font, const char *szoveg, SDL_Color szin, int hovax, int hovay);

//Így vesszük fel a gombok adatait
typedef struct gombok{
    int x, y, sz, m;
    char *szoveg;
    int mitcsinal;

} gombok;

gombok play_gomb;
gombok quit_gomb;
gombok vissza_gomb;
gombok lvl1;
gombok lvl2;
gombok lvl3;
gombok lvl4;
gombok lvl5;

SDL_Color sarga;
SDL_Color lila;

void cim(SDL_Renderer *renderer, TTF_Font *font);
void playGomb(SDL_Renderer *renderer, TTF_Font *font);
void quitGomb(SDL_Renderer *renderer, TTF_Font *font);
void alcim(SDL_Renderer *renderer, TTF_Font *font);
void visszaGomb(SDL_Renderer *renderer, TTF_Font *font);
void visszaGombPause(SDL_Renderer *renderer, TTF_Font *font);
void szintek(SDL_Renderer *renderer, TTF_Font *font);
void szint_megjelenit(bool palya, SDL_Renderer *renderer, TTF_Font *font, char* kiir);

bool rajtavan(gombok egy_gomb, int egerX, int egerY);

void karakter_megjelenit(SDL_Renderer *renderer, matrix *matrix, int egySzamMerete);

void gomb_vizsgalat(SDL_Event event, matrix *matrix, menuk *jelenlegi_menu, palyak *jelenlegi_palya, bool *fut);

#endif // ALAKZATOK_H_INCLUDED
