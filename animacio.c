#include "animacio.h"

void egy_lepes(Palya *palya, OsszesUt *kivalasztott,int i) {
    Mezo *mezon = NULL;
    Mezo *lepes = NULL;
    for (mezon = palya->mezo->kov ; mezon->kov != NULL;mezon = mezon->kov){
        if (mezon->x == palya->egyseg[4].x[i] && mezon->y == palya->egyseg[4].y[i]){
            break;
        }
    }
    if (kivalasztott->egyik != NULL){
        for (lepes = palya->mezo->kov; lepes->kov != NULL;lepes = lepes->kov){
            if (lepes->x == kivalasztott->egyik->lepes->x && lepes->y == kivalasztott->egyik->lepes->y){
                break;
            }
        }
    }
    mezon->egyforma_db--;
    if (mezon->egyforma_db == 0){
        mezon->babu = &palya->egyseg[0];
    }
    if (lepes != NULL && kivalasztott->egyik != NULL){
        lepes->babu = &palya->egyseg[4];
        lepes->egyforma_db++;
        if (palya->egyseg[4].kie[i] == 0){
            lepes->egyforma_db_pirosj++;
            mezon->egyforma_db_pirosj--;
        }
        else{
            lepes->egyforma_db_kekj++;
            mezon->egyforma_db_kekj--;
        }
        palya->egyseg[4].x[i] = kivalasztott->egyik->lepes->x;
        palya->egyseg[4].y[i] = kivalasztott->egyik->lepes->y;
        Ut *tmp = kivalasztott->egyik;
        kivalasztott->egyik = kivalasztott->egyik->kov;
        free(tmp);
    }
    else{
        if (palya->egyseg[4].kie[i] == 0) {
            palya->jatekos[1].elet-=1;
        }
        else if(palya->egyseg[4].kie[i] == 1){
            palya->jatekos[0].elet-=1;
        }
        palya->egyseg[4].db--;
    }
}
OsszesUt *meghalttak_eltavolitasa(Mezo *lista, Egyseg *egyseg,OsszesUt *utak) {
    for (int tipus = 1;tipus<5;tipus++){
        int egysegdb = egyseg[tipus].db;
        for (int i = 0;i<egysegdb;i++){
            if (egyseg[tipus].elet[i] <= 0) {
                Mezo *akt;
                for (akt = lista->kov;akt->kov != NULL ; akt = akt->kov) {
                    if (akt->x == egyseg[tipus].x[i] && akt->y == egyseg[tipus].y[i]){
                        break;
                    }
                }
                if (egyseg[tipus].kie[i] == 0) {
                    akt->egyforma_db_pirosj--;
                }
                if (egyseg[tipus].kie[i] == 1) {
                    akt->egyforma_db_kekj--;
                }
                akt->egyforma_db--;
                utak = torol_egyseg(egyseg, tipus, i, utak);
                if (akt->egyforma_db == 0) {
                    akt->babu = &egyseg[0];
                }
                egysegdb--;
                i--;
            }
        }
    }
    return utak;
}
OsszesUt *torol_egyseg(Egyseg *egyseg, int tipus, int torlendo,OsszesUt *utak) {
    if (tipus == 4){
        OsszesUt *val = utak;
        struct OsszesUt * elozo = NULL;
        for (int i = egyseg[4].db-1 ; i>torlendo;i--){
            elozo = val;
            val = val->kov;
        }
        if (elozo != NULL){
            elozo->kov = val->kov;
            felszabaditt_egyutak(val);
        }
        else{
            if (val->kov != NULL){
                utak = val->kov;
                felszabaditt_egyutak(val);
            } else{
                felszabaditt_utak(utak);
                utak = NULL;
            }

        }
    }
    int xdb = 0;
    int *xm_kor = (int *) malloc(sizeof(int) * (egyseg[tipus].db - 1));
    int *ym_kor = (int *) malloc(sizeof(int) * (egyseg[tipus].db - 1));
    int *kie_egy = (int *) malloc(sizeof(int) * (egyseg[tipus].db - 1));
    double *eletek = (double *) malloc(sizeof(double) * (egyseg[tipus].db - 1));
    for (int i = 0;i<egyseg[tipus].db;i++){
        if (i != torlendo) {
            xm_kor[xdb] = egyseg[tipus].x[i];
            ym_kor[xdb] = egyseg[tipus].y[i];
            eletek[xdb] = egyseg[tipus].elet[i];
            kie_egy[xdb++] = egyseg[tipus].kie[i];
        }
    }
    free(egyseg[tipus].x);
    free(egyseg[tipus].y);
    free(egyseg[tipus].elet);
    free(egyseg[tipus].kie);
    egyseg[tipus].db--;
    egyseg[tipus].x = xm_kor;
    egyseg[tipus].y = ym_kor;
    egyseg[tipus].elet = eletek;
    egyseg[tipus].kie = kie_egy;
    return utak;
}

void animacio_mozgok(SDL_Renderer *renderer, Vezerlesiadatok *vezerloadatok,Palya *palya, OsszesUt **utak,int Width,int Height,SDL_Texture *torony,SDL_Texture *torony2,SDL_Texture *fal22,SDL_Texture *fal21,SDL_Texture *fal11,SDL_Texture *fal12,SDL_Texture *sh,SDL_Texture *sh2,SDL_Texture *hatter2) {
    *utak = utakmegforditasa(palya->mezo,palya->egyseg,*utak);
    vezerloadatok->ujrajz = true;
    while (palya->egyseg[4].db != 0){
        *utak = egy_tamadas(palya->mezo,palya->egyseg,*utak);
        OsszesUt *kivalasztott = *utak;
        for (int i = palya->egyseg[4].db-1 ; i>=0;i--){
            egy_lepes(palya,kivalasztott,i);
            kivalasztott = kivalasztott->kov;
        }
        usleep(6000);
        if (hatter2 != NULL) {
            SDL_Rect src = {0, 0, Width, Height};
            SDL_Rect dest = {0, 0, Width, Height};
            SDL_RenderCopy(renderer, hatter2, &src, &dest);
        }
        ki_rajzol(renderer,vezerloadatok,palya,Width,Height,torony,torony2,fal22,fal21,fal11,fal12,sh,sh2);
        SDL_RenderPresent(renderer);
        if (vezerloadatok->torolt) {
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
        }
    }
}
OsszesUt *egy_tamadas(Mezo *lista, Egyseg *egyseg,struct OsszesUt *utak) {
    //prioritása(mozgo>>allo)(tavolság az egységhez képest)(elet)
    for(int tipus = 1;tipus<5;tipus++){
        for(int i = 0; i < egyseg[tipus].db;i++){
            helyek_eggy_adott_koron_belul(lista,egyseg,i,tipus);
        }
    }
    utak = meghalttak_eltavolitasa(lista,egyseg,utak);
    return utak;
}