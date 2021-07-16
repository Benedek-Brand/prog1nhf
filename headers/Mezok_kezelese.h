#ifndef NHZ_MEZOK_KEZELESE_H
#define NHZ_MEZOK_KEZELESE_H

#include "structurak.h"
#include "debugmalloc.h"

//A Mezok-nek szomszédjait hozza létre
void szomszedok_feltoltese(Mezo *lista);
//Megkapja a Mezőkből álló listát és kezdő kordinátáit ezekből meghatározza az ebből induló cél Mezőjét
Mezo *elkereso(Mezo *lista, int x, int y);
#endif //NHZ_MEZOK_KEZELESE_H
