#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>
#include <stdlib.h>
#include "stdio.h"
#include "menu.h"
#include "alakzatok.h"
#include "debugmalloc.h"

//A fügvény bekér egy megjelenítõt, egy betűstílust, a szöveget, amit meg szeretnénk jeleníteni, egy színt (ezt nekünk kell definiálni), végül pedig x és y koordinátákat, hogy hol jelenjen meg.
void text(SDL_Renderer *renderer, TTF_Font *font, const char *szoveg, SDL_Color szin, int hovax, int hovay) {
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

void cim(SDL_Renderer *renderer, TTF_Font *font) {
    text(renderer, font, "Tomb", sarga, 200, 70);
    text(renderer, font, "of", lila, 410, 70);
    text(renderer, font, "the", sarga, 520, 70);
    text(renderer, font, "Mask", lila, 690, 70);
}

void playGomb(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 139, 66, 176, 255);
    SDL_Rect play_alapja = {play_gomb.x, play_gomb.y, play_gomb.sz, play_gomb.m};
    SDL_RenderFillRect(renderer, &play_alapja);
    text(renderer, font, play_gomb.szoveg, sarga, play_gomb.x+35, play_gomb.y);
}

void quitGomb(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 255, 251, 0, 255);
    SDL_Rect quit_alapja = {quit_gomb.x, quit_gomb.y, quit_gomb.sz, quit_gomb.m};
    SDL_RenderFillRect(renderer, &quit_alapja);
    text(renderer, font, quit_gomb.szoveg, lila, quit_gomb.x+30, quit_gomb.y);
}

void alcim(SDL_Renderer *renderer, TTF_Font *font) {
    text(renderer, font, "Levels", lila, 380, 50);
}

void visszaGomb(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 255, 251, 0, 255);
    SDL_Rect vissza_alapja = {vissza_gomb.x, vissza_gomb.y, vissza_gomb.sz, vissza_gomb.m};
    SDL_RenderFillRect(renderer, &vissza_alapja);
    text(renderer, font, vissza_gomb.szoveg, lila, vissza_gomb.x+7, vissza_gomb.y-8);
}

void visszaGombPause(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 255, 251, 0, 255);
    SDL_Rect vissza_alapja = {vissza_gomb.x, vissza_gomb.y, vissza_gomb.sz, vissza_gomb.m};
    SDL_RenderFillRect(renderer, &vissza_alapja);
    text(renderer, font, "||", lila, vissza_gomb.x+3, vissza_gomb.y-3);
}

void szintek(SDL_Renderer *renderer, TTF_Font *font) {
    SDL_SetRenderDrawColor(renderer, 255, 251, 0, 255);
    SDL_Rect lvl1_alapja = {lvl1.x, lvl1.y, lvl1.sz, lvl1.m};
    SDL_Rect lvl2_alapja = {lvl2.x, lvl2.y, lvl2.sz, lvl2.m};
    SDL_Rect lvl3_alapja = {lvl3.x, lvl3.y, lvl3.sz, lvl3.m};
    SDL_Rect lvl4_alapja = {lvl4.x, lvl4.y, lvl4.sz, lvl4.m};
    SDL_Rect lvl5_alapja = {lvl5.x, lvl5.y, lvl5.sz, lvl5.m};
    SDL_RenderFillRect(renderer, &lvl1_alapja);
    SDL_RenderFillRect(renderer, &lvl2_alapja);
    SDL_RenderFillRect(renderer, &lvl3_alapja);
    SDL_RenderFillRect(renderer, &lvl4_alapja);
    SDL_RenderFillRect(renderer, &lvl5_alapja);
    text(renderer, font, lvl1.szoveg, lila, lvl1.x+10, lvl1.y);
    text(renderer, font, lvl2.szoveg, lila, lvl2.x+10, lvl2.y);
    text(renderer, font, lvl3.szoveg, lila, lvl3.x+10, lvl3.y);
    text(renderer, font, lvl4.szoveg, lila, lvl4.x+10, lvl4.y);
    text(renderer, font, lvl5.szoveg, lila, lvl5.x+10, lvl5.y);
}

void szint_megjelenit(bool palya, SDL_Renderer *renderer, TTF_Font *font, char* kiir) {
    text(renderer, font, kiir, sarga, 380, 30);
}

//Itt történik a karakter megjelenítése. A pálya elhelyezkedésének megfelelően jelenik meg egy sárga kocka.
void karakter_megjelenit(SDL_Renderer *renderer, matrix *matrix, int egySzamMerete) {
    int palya_x = 1080/2-matrix->oszlopok*egySzamMerete/2;
    int palya_y = 720/2-matrix->sorok*egySzamMerete/2;
    karakter egyKarakter = matrix->player;
    SDL_Rect karakterBlock = {egyKarakter.x*egySzamMerete+palya_x, egyKarakter.y*egySzamMerete+palya_y, egySzamMerete, egySzamMerete};
    SDL_SetRenderDrawColor(renderer, 255, 251, 0, 255);
    SDL_RenderFillRect(renderer, &karakterBlock);
}

//Itt megvizsgáljuk, hogy az egér beleesik-e egy gomb tartományába.
bool rajtavan(gombok egy_gomb, int egerX, int egerY) {
    if (egerX >= egy_gomb.x && egerX <= (egy_gomb.x + egy_gomb.sz) && egerY >= egy_gomb.y && egerY <= (egy_gomb.y + egy_gomb.m)){
        return true;
    }
    else {
        return false;
    }
}

//Ez a függvény vizsgálja meg, hogy egyes gombok megnyomása megtörtént-e, és ha igen, akkor utána mi történjen.
void gomb_vizsgalat(SDL_Event event, matrix *matrix, menuk *jelenlegi_menu, palyak *jelenlegi_palya, bool *fut) {
    int eger_x = event.button.x;
    int eger_y = event.button.y;

        switch (*jelenlegi_menu) {
            case fo_menu:
                if(rajtavan(play_gomb, eger_x, eger_y)) {
                    if(play_gomb.mitcsinal == -1){ //Ha esetleg megváltoztatnánk a gomb utasítását, akkor se legyen probléma
                        *fut = false;
                        break;
                    }
                    else {
                    *jelenlegi_menu = play_gomb.mitcsinal;
                    }
                }
                else if(rajtavan(quit_gomb, eger_x, eger_y)) {
                    if(quit_gomb.mitcsinal == -1){
                        *fut = false;
                    }
                    else {
                        *jelenlegi_menu = quit_gomb.mitcsinal;
                    }
                }
                break;

            case al_menu:
                if(rajtavan(vissza_gomb, eger_x, eger_y)) {
                    *jelenlegi_menu = vissza_gomb.mitcsinal;
                }
                else if(rajtavan(lvl1, eger_x, eger_y)) {
                    *jelenlegi_menu = lvl1.mitcsinal;
                    *jelenlegi_palya = 0;
                    matrix_felszabadit(matrix);
                    beleolvas("palya1.txt",matrix);
                    matrix_feltolt("palya1.txt", matrix);
                    matrix_kirajzol(matrix);
                }
                else if(rajtavan(lvl2, eger_x, eger_y)) {
                    *jelenlegi_menu = lvl2.mitcsinal;
                    *jelenlegi_palya = 1;
                    matrix_felszabadit(matrix);
                    beleolvas("palya2.txt",matrix);
                    matrix_feltolt("palya2.txt", matrix);
                    matrix_kirajzol(matrix);
                }
                else if(rajtavan(lvl3, eger_x, eger_y)) {
                    *jelenlegi_menu = lvl3.mitcsinal;
                    *jelenlegi_palya = 2;
                    matrix_felszabadit(matrix);
                    beleolvas("palya3.txt",matrix);
                    matrix_feltolt("palya3.txt", matrix);
                    matrix_kirajzol(matrix);
                }
                else if(rajtavan(lvl4, eger_x, eger_y)) {
                    *jelenlegi_menu = lvl4.mitcsinal;
                    *jelenlegi_palya = 3;
                    matrix_felszabadit(matrix);
                    beleolvas("palya4.txt",matrix);
                    matrix_feltolt("palya4.txt", matrix);
                    matrix_kirajzol(matrix);
                }
                else if(rajtavan(lvl5, eger_x, eger_y)) {
                    *jelenlegi_menu = lvl5.mitcsinal;
                    *jelenlegi_palya = 4;
                    matrix_felszabadit(matrix);
                    beleolvas("palya5.txt",matrix);
                    matrix_feltolt("palya5.txt", matrix);
                    matrix_kirajzol(matrix);
                }
                break;

            case jatek_menu:
                if(rajtavan(vissza_gomb, eger_x, eger_y)) {
                    *jelenlegi_menu = vissza_gomb.mitcsinal;
                }
                break;
            }
}
