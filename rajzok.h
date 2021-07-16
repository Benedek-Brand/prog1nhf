#ifndef NHZ_RAJZOK_H
#define NHZ_RAJZOK_H

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include "structurak.h"
#include <SDL_image.h>
#include "debugmalloc.h"
//kirajzolja a játékosoknak a kör végét jelző gombot
void Rajzol_k_gomb(SDL_Renderer *renderer, int jatekos,int Width,int Height);
//Kirajzolja a játékosokhoz tartozó értékeket
void Rajzol_ertekek(SDL_Renderer *renderer, Jatekos *jatekosok);
//Kirajzolja a körök számát és a különböző egységeket tartalmazó panelt
void Rajzol_panel(SDL_Renderer *renderer, Egyseg *egysegek, int kor_szama,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2);
//A Mezoket teljesen feltölti a pályának megfelelően
void uj_kor(Palya *palya, int x, int y, int kor_x, int kor_y);
//Kirajzolja a pályát
void Rajzol_palya(SDL_Renderer *renderer, Palya *palya,Vezerlesiadatok *vezerlesiadatok,int Height);
//Kirajzolja a megfelelő Mezokre a megfelelő egységeket
void Rajzol_babu(SDL_Renderer *renderer, struct Mezo *lista, struct Egyseg *egysegek, int fajta,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2);
//Kirajzolja az elején a menüt
void Rajzol_menu(SDL_Renderer *renderer,SDL_Texture *hater,SDL_Texture *gomb1,SDL_Texture *gomb2,int Width,int Height);
//Egyben kirajzol minden dolgot a játék futásakor
void ki_rajzol(SDL_Renderer *renderer,Vezerlesiadatok *vezerlesiadatok,Palya *palya,int Width,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2);

#endif //NHZ_RAJZOK_H