#ifndef STATISZTIKA_H_INCLUDED
#define STATISZTIKA_H_INCLUDED
#include "menu.h"

typedef struct statisztikak{
    int teljesitett;
    time_t inditas;
    time_t bezaras;
    double mennyitJatszott;
} statisztikak;

void statisztika_ertekek(statisztikak *statisztika);

void statisztika_kiiras(statisztikak *statisztika, const char *fajlnev);

#endif // STATISZTIKA_H_INCLUDED
