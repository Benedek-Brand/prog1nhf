#ifndef NHZ_MINDEN_INICIALIZALASI_ELEM_H
#define NHZ_MINDEN_INICIALIZALASI_ELEM_H

#include "structurak.h"
#include "debugmalloc.h"
//Az egységekek inicializálja
void inic_egyseg(Egyseg *egysegek,int Height);
//Az oda vissza láncolt listanál az első elemt hozza létre
Mezo *inic_listaelso();
//A két játékost inicializálja
void inic_jatekosok(struct Jatekos *jatekosok,int Elet);
Mezo *inicializalas_struckturak(Egyseg *egysegek, Jatekos jatekosok[2], Vezerlesiadatok *vezerloadatok,Palya *palya,int Height, int Elet);
#endif //NHZ_MINDEN_INICIALIZALASI_ELEM_H
