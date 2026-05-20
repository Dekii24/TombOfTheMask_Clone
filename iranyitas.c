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
#include "statisztika.h"

//Itt történik a karakterünk irányítása. Elõször megnézzük, hogy melyik gombot nyomták le, majd annak megfelelõen faltól falig mozgatjuk a a karaktert.
void jatek_iranyitas(SDL_Event event, matrix *matrix, menuk *menu, statisztikak *statisztika){
    switch(event.type){
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_w: matrix->player.irany = fel; break;
                case SDLK_a: matrix->player.irany = balra; break;
                case SDLK_s: matrix->player.irany = le; break;
                case SDLK_d: matrix->player.irany = jobbra; break;
            }
    }

    karakter *player = &(matrix->player);

    if(player->irany != all) {
        if((matrix->matriksz[player->y-1][player->x] == 0 || matrix->matriksz[player->y-1][player->x] == 2) && player->irany == fel) {
            player->y--;
        }
        if((matrix->matriksz[player->y][player->x-1] == 0 || matrix->matriksz[player->y][player->x-1] == 2) && player->irany == balra) {
            player->x--;
        }
        if((matrix->matriksz[player->y+1][player->x] == 0 || matrix->matriksz[player->y+1][player->x] == 2) && player->irany == le) {
            player->y++;
        }
        if((matrix->matriksz[player->y][player->x+1] == 0 || matrix->matriksz[player->y][player->x+1] == 2) && player->irany == jobbra) {
            player->x++;
        }
    }
    //Ha elérjük a célt, akkor kidob minket az almenübe, ezzel jelezve, hogy teljesítve lett a szint
    if(matrix->matriksz[player->y][player->x] == 2) {
        *menu = 1;
        statisztika->teljesitett += 1;
    }
}

