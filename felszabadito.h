#ifndef NHZ_FELSZABADITO_H
#define NHZ_FELSZABADITO_H

#include "structurak.h"
#include "debugmalloc.h"
//Az egységek által lefoglalt memóriát felszabadítja
void felszabaditt_egysegek(struct Egyseg *egysegek, int meret);
//Az Mezok által lefoglalt memóriát felszabadítja
void felszabaditt_lista(Mezo *lista);
#endif //NHZ_FELSZABADITO_H
