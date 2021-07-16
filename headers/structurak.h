//
// Created by beni on 2020. 11. 15..
//

#ifndef NHZ_STRUCTURAK_H
#define NHZ_STRUCTURAK_H

#include <stdbool.h>
#include "debugmalloc.h"
//A programban használt struktúrák
typedef struct Mezo {
    int x, y, kor_x, kor_y;
    bool foglalt; //akadályozza-e a mozgo egységek útját?
    bool vizsgalt; //vizsgált pont-e
    bool vizsgalando; //vizsgált pont-e
    int el; //vizsgált pont-e
    double cel_tav; // celtol valo tavolsag
    double loc_cel_tav; // celtol valo tavolsag
    struct Mezo *szarmazik; //a legrövidebb út visszakereséséhez
    struct Egyseg *babu;//Milyen egység van rajta vagy esetleg üres
    struct Mezo *elozo, *kov;//láncollt listához
    struct Mezo *fel, *jobb, *bal, *also; // szomszédok
    struct Jatekos *kie;//Melyik játékosé az adott mező
    int egyforma_db_pirosj;
    int egyforma_db;
    int egyforma_db_kekj;
} Mezo;
typedef struct Egyseg {
    int db,azon;
    int eredeti_x, eredeti_y, meret, ara;
    int *kie;
    int range;
    int *x;
    int *y; //xy számpárok
    double sebzes;
    double *elet;
    double kezdoelet;
} Egyseg;
typedef struct Jatekos {
    int azon, elet;
    double allopont, mozgopont;
} Jatekos;
typedef struct Ut {
    struct Mezo *lepes;
    struct Ut *kov;
} Ut;
typedef struct OsszesUt {
    struct Ut *egyik;
    struct OsszesUt *kov;
} OsszesUt;
typedef struct KorElemei{
    struct Mezo *eleme;
    struct KorElemei *kov;
}KorElemei;
typedef struct Vezerlesiadatok{
    bool quit;
    bool vege;
    bool start;
    bool torolt;
    bool ujrajz;
    bool kor_vege;
    bool menu;
    bool beolvas;
    int jatekos;
    int nyert;
    int kor_szama;
    int akt_kor[2];
    int egyseg_val;
}Vezerlesiadatok;
typedef struct Palya{
    Mezo *mezo;
    Egyseg *egyseg;
    Jatekos *jatekos;
}Palya;
#endif //NHZ_STRUCTURAK_H
