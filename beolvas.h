#ifndef BEOLVAS_H_INCLUDED
#define BEOLVAS_H_INCLUDED

typedef enum irany{
    fel,
    le,
    jobbra,
    balra,
    all,
}irany;

typedef struct karakter{
    int x, y;
    irany irany;
} karakter;

typedef struct matrix{
    int **matriksz;
    int sorok;
    int oszlopok;
    karakter player;
} matrix;

void beleolvas(char *fajl, matrix *matrix);
void matrix_feltolt(char *fajl, matrix *matrix);
void matrix_kirajzol(matrix *matrix);
void matrix_felszabadit(matrix *matrix);
void palya_kirajzol(SDL_Renderer *renderer, matrix *matrix, int egySzamMerete);



#endif // BEOLVAS_H_INCLUDED
