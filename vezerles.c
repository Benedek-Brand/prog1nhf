#include "vezerles.h"


const int Width = 683;
const int Height = 384;
const int Elet = 30;



bool van_eleg_pont(double pont, int ara) {
    return pont - ara >= 0;
}
void jatekosok_pontjainak_val(struct Jatekos *jatekosok,int kor_szama) {
    int plusz = kor_szama/10;
    jatekosok[0].mozgopont = (jatekosok[0].mozgopont * 0.75) + 5 + plusz;
    jatekosok[1].mozgopont = (jatekosok[1].mozgopont * 0.75) + 5 + plusz;
    jatekosok[0].allopont += 5;
    jatekosok[1].allopont += 5;
}
void ureshely_feltoltes(Mezo *m, struct Egyseg *egysegek, int tipus,int jatekos) {
    m->babu = &egysegek[tipus];
    if (tipus < 4) {
        m->foglalt = true;
    } else{
        m->egyforma_db++;
    }
    int xdb;
    int *xm_kor = (int *) malloc(sizeof(int) * (egysegek[tipus].db + 1));
    int *ym_kor = (int *) malloc(sizeof(int) * (egysegek[tipus].db + 1));
    int *kie_egy = (int *) malloc(sizeof(int) * (egysegek[tipus].db + 1));
    double *eletek = (double *) malloc(sizeof(double) * (egysegek[tipus].db + 1));
    if (m->egyforma_db == 0){
        xdb = 0;
        for (int i = 0; i < egysegek[tipus].db; i++) {
            if (!(m->x == egysegek[tipus].x[i] && m->y == egysegek[tipus].y[i])) {
                xm_kor[xdb] = egysegek[tipus].x[i];
                ym_kor[xdb] = egysegek[tipus].y[i];
                eletek[xdb] = egysegek[tipus].elet[i];
                kie_egy[xdb++] = egysegek[tipus].kie[i];
            }
        }
    }
    else{
        xdb = 0;
        for (int i = 0; i < egysegek[tipus].db; i++) {
            xm_kor[xdb] = egysegek[tipus].x[i];
            ym_kor[xdb] = egysegek[tipus].y[i];
            eletek[xdb] = egysegek[tipus].elet[i];
            kie_egy[xdb++] = egysegek[tipus].kie[i];
        }
        if (jatekos == 0){
            m->egyforma_db_pirosj++;
        }
        else if(jatekos == 1){
            m->egyforma_db_kekj++;
        }
    }
    free(egysegek[tipus].x);
    free(egysegek[tipus].y);
    free(egysegek[tipus].elet);
    free(egysegek[tipus].kie);
    xm_kor[egysegek[tipus].db] = m->x;
    ym_kor[egysegek[tipus].db] = m->y;
    eletek[egysegek[tipus].db] = egysegek[tipus].kezdoelet;
    kie_egy[egysegek[tipus].db] = m->kie->azon;
    egysegek[tipus].db++;
    egysegek[tipus].x = xm_kor;
    egysegek[tipus].y = ym_kor;
    egysegek[tipus].elet = eletek;
    egysegek[tipus].kie = kie_egy;
}
void SDL_vezerlo(SDL_Renderer *renderer, struct Mezo *lista,struct Egyseg *egysegek,Vezerlesiadatok *vezerlesiadatok) {//&quit,&menu,&torolt, akt_kor,, &jatekos, &ujrajz, &egyseg_val, &kor_vege
    SDL_Event event;
    SDL_WaitEvent(&event);
    switch (event.type) {
        case SDL_KEYUP:
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE:
                    vezerlesiadatok->quit = true;
                    break;
            }
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym) {
            }
            break;
            //eger katintas event
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT && !vezerlesiadatok->beolvas) {
                if (!vezerlesiadatok->menu && !vezerlesiadatok->vege && !vezerlesiadatok->beolvas) {
                    if (eger_vizsgalat(event.motion.x , 244, event.motion.y , 16.5 , event.motion.x , 574 ,event.motion.y , 380.5)) {//>><<
                        for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                            if (vezerlesiadatok->akt_kor[0] == m->x && vezerlesiadatok->akt_kor[1] == m->y && !m->foglalt && m->kie->azon == vezerlesiadatok->jatekos) {
                                if (m->el != 0 && vezerlesiadatok->egyseg_val > 3 && van_eleg_pont(m->kie->mozgopont, egysegek[vezerlesiadatok->egyseg_val].ara)) {
                                    m->kie->mozgopont -= egysegek[vezerlesiadatok->egyseg_val].ara;
                                    ureshely_feltoltes(m, egysegek, vezerlesiadatok->egyseg_val,vezerlesiadatok->jatekos);
                                } else if (vezerlesiadatok->egyseg_val <= 3 && van_eleg_pont(m->kie->allopont, egysegek[vezerlesiadatok->egyseg_val].ara) && m->egyforma_db == 0) {
                                    m->kie->allopont -= egysegek[vezerlesiadatok->egyseg_val].ara;
                                    ureshely_feltoltes(m, egysegek, vezerlesiadatok->egyseg_val,vezerlesiadatok->jatekos);
                                }
                                break;
                            }
                        }
                    }
                    if (eger_vizsgalat(event.motion.x,egysegek[4].eredeti_x,event.motion.y,egysegek[4].eredeti_y - egysegek[4].meret,event.motion.x, egysegek[4].eredeti_x + egysegek[4].meret*2,event.motion.y , egysegek[4].eredeti_y + egysegek[4].meret)){
                        vezerlesiadatok->egyseg_val = 4;
                    }
                    if (eger_vizsgalat(event.motion.x,egysegek[3].eredeti_x- egysegek[3].meret,event.motion.y,egysegek[3].eredeti_y - egysegek[3].meret,event.motion.x, egysegek[3].eredeti_x + egysegek[3].meret,event.motion.y , egysegek[3].eredeti_y + egysegek[3].meret)) {
                        vezerlesiadatok->egyseg_val = 3;
                    }
                    if (eger_vizsgalat(event.motion.x,egysegek[2].eredeti_x,event.motion.y,egysegek[2].eredeti_y - egysegek[2].meret,event.motion.x, egysegek[2].eredeti_x + egysegek[2].meret,event.motion.y , egysegek[2].eredeti_y)) {
                        vezerlesiadatok->egyseg_val = 2;
                    }
                    if (eger_vizsgalat(event.motion.x,egysegek[1].eredeti_x - egysegek[1].meret,event.motion.y,egysegek[1].eredeti_y - egysegek[1].meret,event.motion.x, egysegek[1].eredeti_x + egysegek[1].meret,event.motion.y , egysegek[1].eredeti_y + egysegek[1].meret)){
                        vezerlesiadatok->egyseg_val = 1;
                    }
                    if(eger_vizsgalat(event.motion.x,Width - 93,event.motion.y,Height - 50,event.motion.x, Width - 13,event.motion.y , Height - 20) && !vezerlesiadatok->kor_vege) {
                        if (vezerlesiadatok->jatekos == 0) {
                            vezerlesiadatok->jatekos = 1;
                        } else {
                            vezerlesiadatok->jatekos = 0;
                            vezerlesiadatok->kor_vege = !vezerlesiadatok->kor_vege;
                        }
                        vezerlesiadatok->ujrajz = true;
                    }
                }else if (vezerlesiadatok->vege){
                    if(eger_vizsgalat(event.motion.x, Width/2-50,event.motion.y,Height/2+50,event.motion.x, Width/2+90,event.motion.y , Height/2+100) && !vezerlesiadatok->kor_vege){
                        vezerlesiadatok->menu = !vezerlesiadatok->menu;
                        vezerlesiadatok->vege = !vezerlesiadatok->vege;
                    }
                }
                else {
                    if (event.motion.x > 20 && event.motion.x < 200 && event.motion.y > Height / 2 - 30 && event.motion.y < Height / 2 + 30) {
                        vezerlesiadatok->menu = !vezerlesiadatok->menu;
                        vezerlesiadatok->torolt = true;
                    }
                    if (event.motion.x > Width-200 && event.motion.x < Width-20 && event.motion.y > Height / 2 - 30 && event.motion.y < Height / 2 + 30) {
                        vezerlesiadatok->menu = !vezerlesiadatok->menu;
                        vezerlesiadatok->torolt = true;
                        vezerlesiadatok->beolvas = true;
                    }
                }
            }
            break;
            //Eger helyzete event
        case SDL_MOUSEMOTION:
            if (event.motion.x > 244 && event.motion.y > 16.5 && event.motion.x < 574 && event.motion.y < 380.5 &&
                !vezerlesiadatok->menu && !vezerlesiadatok->vege) {
                char emx[6];
                vezerlesiadatok->akt_kor[0] = (int) ((event.motion.x - 244) / 12);
                vezerlesiadatok->akt_kor[1] = 27 - (int) (event.motion.y - 16.5) / 13;
                sprintf(emx, "%2d", vezerlesiadatok->akt_kor[0]);
                emx[2] = ':';
                sprintf(sizeof(char) * 3 + emx, "%2d", vezerlesiadatok->akt_kor[1]);
                stringRGBA(renderer, 200, Height - 50, emx, 0, 0, 255, 255);
                vezerlesiadatok->ujrajz = true;
            }
            break;
        case SDL_USEREVENT:
            // idozitett esemeny
            break;
        case SDL_QUIT:
            vezerlesiadatok->quit = true;
            break;
    }
}

bool eger_vizsgalat(Sint32 xn1, int xk1, Sint32 xn2, double xk2, Sint32 yk1, int yn1, Sint32 yk2, double yn2) {
    return xn1>xk1 && xn2 > xk2 && yk1<yn1 && yk2 < yn2;
}

void jatek(){
    Palya palya;
    Vezerlesiadatok vezerloadatok;
    Egyseg egysegek[5];
    Jatekos jatekosok[2];
    SDL_Window *window;
    SDL_Renderer *renderer;
    OsszesUt *utak = NULL;
    Mezo *lista = inicializalas_struckturak(egysegek,jatekosok,&vezerloadatok,&palya,Height,Elet);
    sdl_init(&window,&renderer,Width,Height);
    Rajzol_palya(renderer,&palya, &vezerloadatok,Height);
    szomszedok_feltoltese(lista);
    FILE *fpdb = NULL;
    FILE *fp = NULL;
    fajlkezeles(&fp,&fpdb,"r+");
    SDL_Texture *hater = IMG_LoadTexture(renderer, "hatter.png");
    SDL_Texture *gomb1 = IMG_LoadTexture(renderer, "gombvan.png");
    SDL_Texture *gomb2 = IMG_LoadTexture(renderer, "gombtoo.png");
    SDL_Texture *torony = IMG_LoadTexture(renderer, "tornyocska.png");
    SDL_Texture *torony2 = IMG_LoadTexture(renderer, "tornyocskatoo.png");
    SDL_Texture *fal21 = IMG_LoadTexture(renderer, "faltwo.png");
    SDL_Texture *fal22  = IMG_LoadTexture(renderer, "faltww.png");
    SDL_Texture *fal11  = IMG_LoadTexture(renderer, "falone.png");
    SDL_Texture *fal12  = IMG_LoadTexture(renderer, "falonw.png");
    SDL_Texture *sh  = IMG_LoadTexture(renderer, "ship.png");
    SDL_Texture *sh2  = IMG_LoadTexture(renderer, "ship2.png");
    SDL_Texture *hatter2  = IMG_LoadTexture(renderer, "hatter2.png");
    while (!vezerloadatok.quit) {
        if(vezerloadatok.kor_szama == 0 && !vezerloadatok.menu && !vezerloadatok.vege && !vezerloadatok.beolvas){
            fajlkezeles(&fp,&fpdb,"w");
        }
        if (vezerloadatok.beolvas){
            for (Mezo *be = lista->kov;be->kov != NULL;be = be->kov){
                int egysegszam = -1;
                int egysegdb = -1;
                if (fscanf(fp,"%d",&egysegszam) != EOF){
                    fscanf(fpdb,"%d ",&egysegdb);
                    if (egysegszam != 0){
                        if (egysegszam>3){
                            be->kie->mozgopont -= egysegek[egysegszam].ara;
                            for (int i = 0;i<egysegdb;i++){
                                ureshely_feltoltes(be, egysegek, egysegszam,be->kie->azon);
                            }
                        }
                        else{
                            if(be->babu == &palya.egyseg[0]){
                                be->kie->allopont -= egysegek[egysegszam].ara;
                                ureshely_feltoltes(be, egysegek, egysegszam,be->kie->azon);
                            }
                        }
                    }
                }
                else{
                    vezerloadatok.beolvas = !vezerloadatok.beolvas;
                    fajlkezeles(&fp,&fpdb,"a");
                    break;
                }
                vezerloadatok.kor_vege = true;
            }
            if (vezerloadatok.beolvas){
                fscanf(fpdb,"\n");
                fscanf(fp,"\n");
            }
        }

        if (vezerloadatok.menu){

            Rajzol_menu(renderer,hater,gomb1,gomb2,Width,Height);

            SDL_RenderPresent(renderer);
            if (vezerloadatok.torolt) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
            }
        }else if(vezerloadatok.vege) {
            if(vezerloadatok.nyert == 0){
                stringRGBA(renderer,Width/2,Height/2,"Nyert a piros.",255,0,0,255);
            }
            else if(vezerloadatok.nyert == 1){
                stringRGBA(renderer,Width/2,Height/2,"Nyert a kek.",0,0,255,255);
            }else{
                stringRGBA(renderer,Width/2,Height/2,"Dontetlen.",255,0,255,255);
            }
            boxRGBA(renderer,Width/2-50,Height/2+100,Width/2+90,Height/2+50,255,255,255,255);
            stringRGBA(renderer,Width/2-45,Height/2+75,"Vissza a menube.",255,0,255,255);
            SDL_RenderPresent(renderer);
            if (vezerloadatok.torolt) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
            }
        } else{
            if (vezerloadatok.ujrajz) {
                if (hatter2 != NULL) {
                    SDL_Rect src = {0, 0, Width, Height};
                    SDL_Rect dest = {0, 0, Width, Height};
                    SDL_RenderCopy(renderer, hatter2, &src, &dest);
                }
                ki_rajzol(renderer, &vezerloadatok, &palya, Width, Height, torony, torony2, fal22, fal21,fal11,fal12,sh,sh2);
                SDL_RenderPresent(renderer);
            }
            if (vezerloadatok.torolt) {
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                vezerloadatok.torolt = false;
            }
        }
        SDL_vezerlo(renderer, lista, egysegek,&vezerloadatok);//

        if (vezerloadatok.kor_vege) {
            if (!vezerloadatok.beolvas){
                int db = 0;
                if (fp != NULL && fpdb != NULL){
                    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
                        fprintf(fp, "%d " ,m->babu->azon);
                        fprintf(fpdb, "%d " ,m->egyforma_db);
                        db++;
                    }
                    fprintf(fp, "\n");
                    fprintf(fpdb, "\n");
                }
            }
            animacio_mozgok(renderer, &vezerloadatok, &palya, &utak, Width, Height, torony, torony2, fal22, fal21,fal11,fal12,sh,sh2,hatter2);
            vezerloadatok.ujrajz = false;
            vezerloadatok.kor_szama++;
            jatekosok_pontjainak_val(jatekosok,vezerloadatok.kor_szama);
            vezerloadatok.kor_vege = !vezerloadatok.kor_vege;
            if (vezerloadatok.kor_szama == 100 || palya.jatekos[1].elet <= 0 || palya.jatekos[0].elet <= 0 ){
                if(palya.jatekos[1].elet < palya.jatekos[0].elet){
                    vezerloadatok.nyert = 0;
                }else if(palya.jatekos[1].elet > palya.jatekos[0].elet){
                    vezerloadatok.nyert = 1;
                }
                felszabaditt_lista(lista);
                felszabaditt_utak(utak);
                utak = NULL;
                felszabaditt_egysegek(egysegek, 5);

                lista = inicializalas_struckturak(egysegek,jatekosok,&vezerloadatok,&palya,Height,Elet);
                vezerloadatok.vege = true;
                vezerloadatok.ujrajz = true;
                vezerloadatok.menu = false;
                vezerloadatok.ujrajz = false;
                Rajzol_palya(renderer, &palya, &vezerloadatok,Height);
                szomszedok_feltoltese(lista);
                fajlkezeles(&fp,&fpdb,"r+");
                SDL_RenderPresent(renderer);
                if (vezerloadatok.torolt) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                    SDL_RenderClear(renderer);
                }
            }
        }
    }
    if (fp != NULL && fpdb != NULL){
        fclose(fp);
        fclose(fpdb);
    }
    if (hater != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (gomb1 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (gomb2 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (torony != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (torony2 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (fal22 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (fal21 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (fal11 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (fal12 != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (sh != NULL) {
        SDL_DestroyTexture(hater);
    }
    if (sh2 != NULL) {
        SDL_DestroyTexture(hater);
    }
    felszabaditt_lista(lista);
    felszabaditt_utak(utak);
    felszabaditt_egysegek(egysegek, 5);
    SDL_Quit();

}

void fajlkezeles(FILE **fp, FILE **fpdb, char *megnyitasmod) {
    if (*fp != NULL && *fpdb != NULL ){
        fclose(*fp);
        fclose(*fpdb);
    }
    *fp = fopen("save.txt", megnyitasmod);
    *fpdb = fopen("save2.txt", megnyitasmod);
    if (*fpdb == NULL) {
        perror("Nem sikerült megnyitni a fájlt");
    }
    if (*fp == NULL) {
        perror("Nem sikerült megnyitni a fájlt");
    }
}

