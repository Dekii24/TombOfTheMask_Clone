#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "beolvas.h"
#include "alakzatok.h"
#include "debugmalloc.h"

//A függvény bekér egy szövegfáljt,egy mátrix címet, majd egy sorszámor és egy oszlopszámot eltároló pointert. A függvény soronként végigmegy a szövegfájlon és megszámolja hány sor és hány oszlop található benne.
void beleolvas(char *fajl, matrix *matrix) {
    FILE *palyaFile = fopen(fajl, "r");
    if (palyaFile == NULL) {
        printf("Hiba tortent a fajl megnyitasa kozben.");
        return;
    }
    int oszlopok = 0;
    int sorok = 0;
    int ujsor = 1;
    int ertek;
    int ossz = 0;

    while (fscanf(palyaFile, "%d", &ertek) != EOF) {
        ossz += 1;
        if (ujsor == 1) {
            sorok += 1;
            ujsor = 0;
        }
        if (fgetc(palyaFile) == '\n') {
            ujsor = 1;
        }
    }
    oszlopok = ossz / sorok;

    matrix ->matriksz = (int **)malloc(sorok * sizeof (int *));
    for(int i = 0; i < sorok; i++){
        matrix->matriksz[i] = (int *)malloc(oszlopok * sizeof (int));
    }
    matrix->sorok = sorok;
    matrix->oszlopok = oszlopok;

    fclose(palyaFile);
}

//Pálya mátrix feltöltése a fájlból
void matrix_feltolt(char *fajl, matrix *matrix) {
    FILE *palyaFile = fopen(fajl, "r");
    if (palyaFile == NULL) {
        printf("Hiba tortent a fajl megnyitasa kozben.");
        return;
    }

    for (int i = 0; i < matrix->sorok; i++){
        for (int j = 0; j < matrix->oszlopok; j++) {
            fscanf(palyaFile, "%d", &(matrix->matriksz[i][j]));
            if(matrix->matriksz[i][j] == 3) {
                matrix->matriksz[i][j] = 0;
                matrix->player = (karakter){j, i, all};
            }
        }
    }

    fclose(palyaFile);
}

//Mátrix kirajzolása a konzolra (teszteléshez kell)
void matrix_kirajzol(matrix *matrix) {
    for (int i = 0; i < matrix->sorok; i++) {
        for (int j = 0; j < matrix->oszlopok; j++) {
            printf("%d ", matrix->matriksz[i][j]);
        }
        printf("\n");
    }
}

//Felszabadítjuk a mátrixot
void matrix_felszabadit(matrix *matrix) {
    if(matrix->matriksz == NULL) {
        return;
    }
    if(matrix->matriksz != NULL) {
        for (int i = 0; i < matrix->sorok; i++) {
            free(matrix->matriksz[i]);
        }
        free(matrix->matriksz);
    }
}

//Ezzel a függvénnyel rajzoljuk ki a pályát. Elhelyezzük a képernyő közepére, majd a számokan megfelelő blockot kirajzoljuk
void palya_kirajzol(SDL_Renderer *renderer, matrix *matrix, int egySzamMerete) {
    int palya_x = 1080/2-matrix->oszlopok*egySzamMerete/2;
    int palya_y = 720/2-matrix->sorok*egySzamMerete/2;
    for(int i = 0; i < matrix->sorok; i++) {
        for(int j = 0; j < matrix->oszlopok; j++) {
            SDL_Rect egyBlock = {palya_x + j * egySzamMerete, palya_y + i * egySzamMerete, egySzamMerete, egySzamMerete};
            if(matrix->matriksz[i][j] == 2) {
                SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
            }
            if(matrix->matriksz[i][j] == 1) {
                SDL_SetRenderDrawColor(renderer, 139, 66, 176, 255);
            }
            if(matrix->matriksz[i][j] == 0 || matrix->matriksz[i][j] == 3) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            }
            SDL_RenderFillRect(renderer, &egyBlock);
        }
    }
    karakter_megjelenit(renderer, matrix, egySzamMerete);
}
