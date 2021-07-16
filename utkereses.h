//
// Created by beni on 2020. 11. 15..
//

#ifndef NHZ_UTKERESES_H
#define NHZ_UTKERESES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "structurak.h"
#include "Minden_inicializalasi_elem.h"
#include "Mezok_kezelese.h"
#include "debugmalloc.h"

//Pitagorasztétel ált. vett távolság
double tavolsag(int ax, int ay, int bx, int by);
OsszesUt *utakmegforditasa(Mezo *lista, Egyseg *egysegek, OsszesUt *ujutak);
//Megvizsgálja hogy az összes Mezo át lett-e már vizsgálva
void felszabaditt_utak(OsszesUt *utak);
bool osszesvizsgalt(Mezo *lista);
//Megnézi a vizsgalando mezőket és kiváálasztja a legközelebbit
Mezo *sorbavizsgalando(Mezo *lista);
void vizsgal_szomszed(struct Mezo *vizsgalando,struct Mezo *end,struct Mezo *szomszed);
//Megkkeresi a legrövidebb utat a célhoz vagy ha az nem elérhető akkor keres egy utat az akadályig
Mezo *utkereses(Mezo *lista,int ex, int ey, int mx, int my);
Ut *elore_beszur(Ut *utak, Mezo *mezo);
OsszesUt *elore_beszur_utat(OsszesUt *ujutak, Ut *utak);
void felszabaditt_ut(struct Ut *ut);
OsszesUt *felszabaditt_egyutak(OsszesUt *utak);
void felszabaditt_kor(struct KorElemei *elemek);
void helyek_eggy_adott_koron_belul(Mezo *lista, Egyseg *egyseg, int i, int tipus);


#endif //NHZ_UTKERESES_H
