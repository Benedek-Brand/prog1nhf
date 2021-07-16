#include "rajzok.h"

void Rajzol_k_gomb(SDL_Renderer *renderer, int jatekos,int Width,int Height) {
    boxRGBA(renderer, Width - 13, Height - 20, Width - 93, Height - 50, jatekos == 0 ? 0 : 255, 0,
            jatekos == 0 ? 255 : 0, 255);
    stringRGBA(renderer, Width - 83, Height - 40, "k\x94r vege", 255, 255, 255, 255);
}

void Rajzol_ertekek(SDL_Renderer *renderer, Jatekos *jatekosok) {
    char mozgo_p[5];
    stringRGBA(renderer, 15, 90, "M", 255, 255, 255, 255);
    sprintf(mozgo_p, "%.0f", jatekosok[0].mozgopont);
    stringRGBA(renderer, 15, 120, mozgo_p, 255, 255, 255, 255);
    stringRGBA(renderer, 50, 90, "A", 255, 255, 255, 255);
    sprintf(mozgo_p, "%.0f", jatekosok[0].allopont);
    stringRGBA(renderer, 50, 120, mozgo_p, 255, 255, 255, 255);
    stringRGBA(renderer, 100, 90, "Elet", 255, 255, 255, 255);
    sprintf(mozgo_p, "%2d", jatekosok[0].elet);
    stringRGBA(renderer, 100, 120, mozgo_p, 255, 255, 255, 255);
    stringRGBA(renderer, 15, 190, "M", 255, 255, 255, 255);
    sprintf(mozgo_p, "%.0f", jatekosok[1].mozgopont);
    stringRGBA(renderer, 15, 220, mozgo_p, 255, 255, 255, 255);
    stringRGBA(renderer, 50, 190, "A", 255, 255, 255, 255);
    sprintf(mozgo_p, "%.0f", jatekosok[1].allopont);
    stringRGBA(renderer, 50, 220, mozgo_p, 255, 255, 255, 255);
    stringRGBA(renderer, 100, 190, "Elet", 255, 255, 255, 255);
    sprintf(mozgo_p, "%2d", jatekosok[1].elet);
    stringRGBA(renderer, 100, 220, mozgo_p, 255, 255, 255, 255);
    boxRGBA(renderer, 5, 100, 200, 150, 255, 0, 0, 100);
    boxRGBA(renderer, 5, 200, 200, 250, 0, 0, 255, 100);
}
void Rajzol_panel(SDL_Renderer *renderer, Egyseg *egysegek, int kor_szama,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2) {
    char mozgo_p[4];
    stringRGBA(renderer, 15, 30, "K\x94r\x94k szama:", 255, 255, 255, 255);
    sprintf(mozgo_p, "%3d", kor_szama);
    stringRGBA(renderer, 110, 30, mozgo_p, 255, 255, 255, 255);
    boxRGBA(renderer, 5, Height - 10, 170, Height - 60, 255, 255, 255, 50);
    //boxRGBA(renderer, egysegek[2].eredeti_x, egysegek[2].eredeti_y, egysegek[2].eredeti_x + egysegek[2].meret,egysegek[2].eredeti_y - egysegek[2].meret, 255, 0, 0, 255);
    if (torony2 != NULL) {
        SDL_Rect src = {0, 0, 240, 240};
        SDL_Rect dest = {egysegek[2].eredeti_x, egysegek[2].eredeti_y-20, 22, 22};
        SDL_RenderCopy(renderer, torony2, &src, &dest);
    }
    //circleRGBA(renderer, egysegek[1].eredeti_x, egysegek[1].eredeti_y, egysegek[1].meret, 255, 0, 0, 255);
    if (fal11 != NULL) {
        SDL_Rect src = {0, 0, 240, 240};
        SDL_Rect dest = {egysegek[1].eredeti_x-10, egysegek[1].eredeti_y-10, 22, 22};
        SDL_RenderCopy(renderer, fal11, &src, &dest);
    }
    //filledCircleRGBA(renderer, egysegek[3].eredeti_x, egysegek[3].eredeti_y, egysegek[3].meret, 255, 0, 0, 255);
    if (fal21 != NULL) {
        SDL_Rect src = {0, 0, 240, 240};
        SDL_Rect dest = {egysegek[3].eredeti_x-10, egysegek[3].eredeti_y-10, 22, 22};
        SDL_RenderCopy(renderer, fal21, &src, &dest);
    }
    //filledTrigonRGBA(renderer,egysegek[4].eredeti_x+egysegek[4].meret,egysegek[4].eredeti_y-egysegek[4].meret, egysegek[4].eredeti_x,egysegek[4].eredeti_y+egysegek[4].meret,egysegek[4].eredeti_x+2*egysegek[4].meret,egysegek[4].eredeti_y+egysegek[4].meret,255,0,0,255);
    if (sh != NULL) {
        SDL_Rect src = {0, 0, 240, 240};
        SDL_Rect dest = {egysegek[4].eredeti_x, egysegek[4].eredeti_y-10, 22, 22};
        SDL_RenderCopy(renderer, sh, &src, &dest);
    }
}
void uj_kor(Palya *palya, int x, int y, int kor_x, int kor_y) {
    Mezo *uj = (Mezo *) malloc(sizeof(Mezo));
    memset(uj, 0, sizeof(Mezo));
    if (uj != NULL) {
        uj->x = x;
        uj->kor_x = kor_x;
        uj->y = y;
        uj->kor_y = kor_y;
        uj->elozo = palya->mezo;
        uj->kov = palya->mezo->kov;
        uj->babu = &palya->egyseg[0];
        uj->foglalt = false;
        uj->el = 0;
        for (int i = 0;i<14;i++) {
            //bal alsó él
            if (uj->x == i && uj->y == 13-i){
                uj->el = 1;
            }
            //jobb alsó él
            if (uj->x == i+14 && uj->y == i){
                uj->el = 2;
            }
            //bal felső él
            if (uj->x == i && uj->y == i+14){
                uj->el = 3;
            }
            //jobb felső él
            if (uj->x == i+14 && uj->y == 27-i){
                uj->el = 4;
            }
        }
        if (y > 13) {
            uj->kie = &palya->jatekos[1];
        }
        else {
            uj->kie = &palya->jatekos[0];
        }
        palya->mezo->kov->elozo = uj;
        palya->mezo->kov = uj;
    }
    int *x_kor = (int *) malloc(sizeof(int) * (palya->egyseg[0].db + 1));
    int *y_kor = (int *) malloc(sizeof(int) * (palya->egyseg[0].db + 1));
    if (x_kor != NULL && y_kor != NULL) {
        for (int i = 0; i < palya->egyseg[0].db; i++) {
            x_kor[i] = palya->egyseg[0].x[i];
            y_kor[i] = palya->egyseg[0].y[i];
        }
        free(palya->egyseg[0].x);
        free(palya->egyseg[0].y);
        x_kor[palya->egyseg[0].db] = x;
        y_kor[palya->egyseg[0].db] = y;
        palya->egyseg[0].x = x_kor;
        palya->egyseg[0].y = y_kor;
    }
}
void Rajzol_palya(SDL_Renderer *renderer, Palya *palya,Vezerlesiadatok *vezerlesiadatok,int Height) {
    for (int x = 0; x < 28; ++x) {
        for (int y = 0; y < 28; ++y) {
            if (y < 13 - x && x < 14 || y < x - 14 && x > 14 || y > 13 && x < y - 14 || y > 13 && x > 41 - y) {
                filledCircleRGBA(renderer, 250 + x * 12, Height - 10 - y * 13, 3, 100, 100, 100, 255);
            } else {
                if (vezerlesiadatok->start) {
                    uj_kor(palya, x, y, 250 + x * 12, Height - 10 - y * 13);
                }
                filledCircleRGBA(renderer, 250 + x * 12, Height - 10 - y * 13, 1, 255, 255, 255, 255);
            }
        }
    }
    vezerlesiadatok->start = false;
}
void Rajzol_babu(SDL_Renderer *renderer, struct Mezo *lista, struct Egyseg *egysegek, int fajta,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2) {
    for (int i = 0; i <= fajta; i++) {
        for (int db = 0; db != egysegek[i].db; db++) {
            switch (i) {
                case 1:
                    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                        if (egysegek[i].x[db] == m->x && egysegek[i].y[db] == m->y) {
                            if (fal11 != NULL) {
                                SDL_Rect src = {0, 0, 240, 240};
                                SDL_Rect dest = {m->kor_x - 5, m->kor_y - 5, 12, 12};
                                SDL_RenderCopy(renderer, egysegek[i].kie[db] == 0 ? fal11 : fal12, &src, &dest);
                            }
                            break;
                            //circleRGBA(renderer, m->kor_x, m->kor_y, 4, egysegek[i].kie[db] == 0 ? 255 : 0, 0,egysegek[i].kie[db] == 0 ? 0 : 255, 255);
                            //break;
                        }
                    }
                    break;
                case 2:
                    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                        if (egysegek[i].x[db] == m->x && egysegek[i].y[db] == m->y) {
                            //circleRGBA(renderer, m->kor_x, m->kor_y, 4, 255, 255, 255, 255);
                            if (torony != NULL) {
                                //boxRGBA(renderer,Width-20,Height/2-30,Width-200,Height/2+30,100,255,100,255);
                                SDL_Rect src = { 0, 0, 240, 240 };
                                SDL_Rect dest = { m->kor_x - 5, m->kor_y - 5, 12, 12};
                                SDL_RenderCopy(renderer, egysegek[i].kie[db] == 0 ? torony2 : torony, &src, &dest);
                            }
                            break;
                        }
                    }
                    break;
                case 3:
                    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                        if (egysegek[i].x[db] == m->x && egysegek[i].y[db] == m->y) {
                            //filledCircleRGBA(renderer, m->kor_x, m->kor_y, 4, egysegek[i].kie[db] == 0 ? 255 : 0, 0, egysegek[i].kie[db] == 0 ? 0 : 255, 255);
                            if (fal21 != NULL) {
                                SDL_Rect src = {0, 0, 240, 240};
                                SDL_Rect dest = {m->kor_x - 5, m->kor_y - 5, 12, 12};
                                SDL_RenderCopy(renderer, egysegek[i].kie[db] == 0 ? fal21 : fal22, &src, &dest);
                            }
                            break;
                        }
                    }
                    break;
                case 4:
                    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                        if (egysegek[i].x[db] == m->x && egysegek[i].y[db] == m->y) {
                            if (sh != NULL) {
                                SDL_Rect src = {0, 0, 240, 240};
                                SDL_Rect dest = {m->kor_x - 5, m->kor_y - 5, 12, 12};
                                SDL_RenderCopy(renderer, egysegek[i].kie[db] == 0 ? sh : sh2, &src, &dest);
                            }
                            //filledTrigonRGBA(renderer,m->kor_x,m->kor_y-egysegek[4].meret/2, m->kor_x-egysegek[4].meret/2,m->kor_y+egysegek[4].meret/2,m->kor_x+egysegek[4].meret/2,m->kor_y+egysegek[4].meret/2,egysegek[i].kie[db] ==0 ? 255 : 0,0,egysegek[i].kie[db] == 0 ? 0 : 255,255);
                            char szam[4];
                            sprintf(szam, "%3d", m->egyforma_db);
                            stringRGBA(renderer,m->kor_x-25,m->kor_y,szam,255,255,255,255);
                            break;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
void Rajzol_menu(SDL_Renderer *renderer,SDL_Texture *hater,SDL_Texture *gomb1,SDL_Texture *gomb2,int Width,int Height){
    if (hater != NULL) {
        SDL_Rect src = { 0, 0, 1062, 856 };
        SDL_Rect dest = { 0, 0, Width, Height};
        SDL_RenderCopy(renderer, hater, &src, &dest);
    }
    if (gomb1 != NULL) {
        //boxRGBA(renderer,20,Height/2-30,200,Height/2+30,255,100,255,255);
        SDL_Rect src = { 0, 0, 1062, 856 };
        SDL_Rect dest = { 20, Height/2-30, 150, 60};
        SDL_RenderCopy(renderer, gomb1, &src, &dest);
    }
    //stringRGBA(renderer,40,Height/2,"Uj jatek",255,255,255,255);
    if (gomb2 != NULL) {
        //boxRGBA(renderer,Width-20,Height/2-30,Width-200,Height/2+30,100,255,100,255);
        SDL_Rect src = { 0, 0, 1062, 856 };
        SDL_Rect dest = { Width-180, Height/2-30, 150, 60};
        SDL_RenderCopy(renderer, gomb2, &src, &dest);
    }
    //stringRGBA(renderer,Width-160,Height/2,"Jatek betoltes",255,255,255,255);
}
void ki_rajzol(SDL_Renderer *renderer,Vezerlesiadatok *vezerlesiadatok,Palya *palya,int Width,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2){
    vezerlesiadatok->torolt = true;
    vezerlesiadatok->ujrajz = false;
    Rajzol_k_gomb(renderer, vezerlesiadatok->jatekos ,Width,Height);
    Rajzol_ertekek(renderer, palya->jatekos);
    Rajzol_panel(renderer, palya->egyseg, vezerlesiadatok->kor_szama,Height,torony,torony2,fal22,fal21,fal11,fal12,sh,sh2);
    Rajzol_palya(renderer, palya,vezerlesiadatok,Height);
    Rajzol_babu(renderer, palya->mezo, palya->egyseg, 4,torony,torony2,fal22,fal21,fal11,fal12,sh,sh2);
}

