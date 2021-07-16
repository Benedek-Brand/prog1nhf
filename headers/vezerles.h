#ifndef NHZ_VEZERLES_H
#define NHZ_VEZERLES_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_render.h>
#include "utkereses.h"
#include "rajzok.h"
#include "structurak.h"
#include "SDL_letrehozas.h"
#include "Mezok_kezelese.h"
#include "Minden_inicializalasi_elem.h"
#include "felszabadito.h"
#include "animacio.h"
#include <unistd.h>
#include <SDL_image.h>
#include "debugmalloc.h"

extern const int Width;
extern const int Height;
extern const int Elet;

//Megvizsgálja hogy a játékosnak van-e elég pontja az adott egységhez
bool van_eleg_pont(double pont, int ara);

//A körönként kiszámolja a játékos pontjainak változását
void jatekosok_pontjainak_val(struct Jatekos *jatekosok,int kor_szama);

//Megnézi hogy az adott Mezo ures-e és ha igen akkor feltöllti az adott típussal
void ureshely_feltoltes(Mezo *m, struct Egyseg *egysegek, int tipus,int jatekos);

//Vezérli a programot különbözőő egér és billentyűzet alapján
void SDL_vezerlo(SDL_Renderer *renderer, struct Mezo *lista,struct Egyseg *egysegek,Vezerlesiadatok *vezerlesiadatok);
void fajlkezeles(FILE **fp, FILE **fpdb, char *megnyitasmod);
bool eger_vizsgalat(Sint32 xn, int yn, Sint32 xk, double yk, Sint32 x1, int i1, Sint32 y1, double d1);
void jatek();
#endif //NHZ_VEZERLES_H
