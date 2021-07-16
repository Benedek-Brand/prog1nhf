#ifndef NHZ_ANIMACIO_H
#define NHZ_ANIMACIO_H

#include "structurak.h"
#include "utkereses.h"
#include "SDL.h"
#include "rajzok.h"
#include "debugmalloc.h"

void egy_lepes(Palya *palya, OsszesUt *kivalasztott,int i);
OsszesUt *meghalttak_eltavolitasa(Mezo *lista, Egyseg *egyseg,struct OsszesUt *utak);
OsszesUt *torol_egyseg(Egyseg *egyseg, int tipus, int torlendo,struct OsszesUt *utak);
void animacio_mozgok(SDL_Renderer *renderer, Vezerlesiadatok *vezerloadatok,Palya *palya, OsszesUt **utak,int Width,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2,SDL_Texture *hatter2);
OsszesUt *egy_tamadas(Mezo *lista, Egyseg *egyseg,struct OsszesUt *utak);

#endif //NHZ_ANIMACIO_H
