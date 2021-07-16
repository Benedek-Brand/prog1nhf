#include "utkereses.h"

double tavolsag(int ax, int ay, int bx, int by) {
    return sqrt(pow(ax-bx,2)+pow(ay-by,2));
}
OsszesUt *utakmegforditasa(Mezo *lista, Egyseg *egysegek,OsszesUt *utak) {
    for (int i = 0;i <egysegek[4].db;i++) {
        Ut *ujutak = NULL;
        Mezo *cel = elkereso(lista, egysegek[4].x[i], egysegek[4].y[i]);
        Mezo *ut = utkereses(lista, egysegek[4].x[i], egysegek[4].y[i], cel->x, cel->y);
        if (cel->szarmazik != NULL){
            ujutak = elore_beszur(ujutak, cel);
        }
        for (Mezo *kkk = ut ; kkk->szarmazik != NULL; kkk = kkk->szarmazik){
            ujutak = elore_beszur(ujutak, kkk);
        }
        utak = elore_beszur_utat(utak, ujutak);
    }
    return utak;
}
void felszabaditt_utak(OsszesUt *utak) {
    while (utak) {
        utak = felszabaditt_egyutak(utak);
    }
}
bool osszesvizsgalt(Mezo *lista) {
    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
        if(!m->vizsgalt){
            return true;
        }
    }
    return false;
}
Mezo *sorbavizsgalando(Mezo *lista) {
    Mezo *legkozelebb = NULL;
    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
        if ((legkozelebb == NULL || m->cel_tav < legkozelebb->cel_tav) && m->vizsgalando && !m->vizsgalt ){
            legkozelebb = m;
        }
    }
    return legkozelebb;
}
void vizsgal_szomszed(struct Mezo *vizsgalando,struct Mezo *end,struct Mezo *szomszed) {
    if(szomszed != NULL && !szomszed->foglalt) {
        double szarmazottolvalotav = vizsgalando->loc_cel_tav + tavolsag(vizsgalando->x, vizsgalando->y, szomszed->x, szomszed->y);
        if (szarmazottolvalotav < szomszed->loc_cel_tav) {
            szomszed->vizsgalando = true;
            szomszed->szarmazik = vizsgalando;
            szomszed->loc_cel_tav = szarmazottolvalotav;
            szomszed->cel_tav = szomszed->loc_cel_tav + tavolsag(szomszed->x, szomszed->y, end->x, end->y);
        }
    }
}
Mezo *utkereses(Mezo *lista,int ex, int ey, int mx, int my) {
    Mezo *start = NULL;
    Mezo *end = NULL;
    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
        m->vizsgalt = false;
        m->cel_tav = INFINITY;
        m->loc_cel_tav = INFINITY;
        m->szarmazik = NULL;
        m->vizsgalando = false;
        if (m->x == ex && m->y == ey){
            start = m;
        }
        if (m->x == mx && m->y == my){
            end = m;
        }
    }
    start->loc_cel_tav = 0.0f;
    start->cel_tav = tavolsag(start->x,start->y,end->x,end->y);
    start->vizsgalando = true;
    while (osszesvizsgalt(lista)){
        Mezo *vizsgalando = sorbavizsgalando(lista);
        if (vizsgalando == NULL){
            break;
        }
        vizsgalando->vizsgalt = true;
        double szarmazottolvalotav = 0;
        vizsgal_szomszed(vizsgalando,end,vizsgalando->fel);
        vizsgal_szomszed(vizsgalando,end,vizsgalando->jobb);
        vizsgal_szomszed(vizsgalando,end,vizsgalando->also);
        vizsgal_szomszed(vizsgalando,end,vizsgalando->bal);

    }
    Mezo *legkozelebb = NULL;
    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov) {
        if ((legkozelebb == NULL || m->cel_tav > legkozelebb->cel_tav) && m->vizsgalando && m->vizsgalt ){
            legkozelebb = m;
        }
    }
    if (end->szarmazik == NULL){
        if(end != legkozelebb){
            end = utkereses(lista, ex, ey, legkozelebb->x, legkozelebb->y);
        }
        else{
            end = start;
        }
    }
    return end;
}
Ut *elore_beszur(Ut *utak, Mezo *mezo) {
    Ut *uj = (Ut*) malloc(sizeof(Ut));
    uj->lepes = mezo;
    uj->kov = utak;
    return uj;
}
OsszesUt *elore_beszur_utat(OsszesUt *ujutak, Ut *utak) {
    OsszesUt *uj = (OsszesUt*) malloc(sizeof(OsszesUt));
    uj->egyik = utak;
    uj->kov = ujutak;
    return uj;
}
void felszabaditt_ut(struct Ut *ut) {
    while (ut) {
        Ut *temp = ut->kov;
        free(ut);
        ut = temp;
    }
}
OsszesUt *felszabaditt_egyutak(OsszesUt *utak) {
    felszabaditt_ut(utak->egyik);
    OsszesUt *temp = utak->kov;
    free(utak);
    return temp;
}
void felszabaditt_kor(struct KorElemei *elemek) {
    while (elemek) {
        KorElemei *temp = elemek->kov;
        free(elemek);
        elemek = temp;
    }
}
void helyek_eggy_adott_koron_belul(Mezo *lista, Egyseg *egyseg, int i, int tipus) {
    if (egyseg[tipus].range < 0) {
        return;
    }
    int x = egyseg[tipus].x[i];
    int y = egyseg[tipus].y[i];
    KorElemei *elerhetok = NULL;
    for(int xkor = x-egyseg[tipus].range;xkor<x+egyseg[tipus].range;xkor++){
        for(int ykor = y-egyseg[tipus].range;ykor<y+egyseg[tipus].range;ykor++){
            Mezo *elert = NULL;
            for (elert = lista->kov;elert->kov != NULL ; elert = elert->kov) {
                if (elert->x == xkor && elert->y == ykor){
                    if (elert != NULL && tavolsag(xkor,ykor,egyseg[tipus].x[i],egyseg[tipus].y[i]) <= egyseg[tipus].range){
                        KorElemei *uj = (KorElemei*)malloc(sizeof(KorElemei));
                        uj->eleme = elert;
                        uj->kov = elerhetok;
                        elerhetok = uj;
                    }
                    break;
                }
            }
        }
    }
    int tdb = -1;
    //ellenséges mozgo eggység-e
    for (KorElemei *elem = elerhetok;elem != NULL;elem = elem->kov){
        for (int m = 0; m<egyseg[4].db;m++){
            bool xten = elem->eleme->x == egyseg[4].x[m];
            bool yten = elem->eleme->y == egyseg[4].y[m];
            bool megyvazonos = ((tdb == -1 && elem->eleme->babu == &egyseg[4] &&  elem->eleme->babu->kie[m] != egyseg[tipus].kie[i]) || (tdb != -1 && egyseg[tipus].kie[i] != egyseg[4].kie[tdb]));
            bool tavazonosvmegy = (tdb == -1 || ((tdb != -1 && (tavolsag(egyseg[4].x[m],egyseg[4].y[m],egyseg[tipus].x[i],egyseg[tipus].y[i])>tavolsag(egyseg[4].x[tdb],egyseg[4].y[tdb],egyseg[tipus].x[i],egyseg[tipus].y[i]))) || (tavolsag(egyseg[4].x[m],egyseg[4].y[m],egyseg[tipus].x[i],egyseg[tipus].y[i])==tavolsag(egyseg[4].x[tdb],egyseg[4].y[tdb],egyseg[tipus].x[i],egyseg[tipus].y[i]))) && ((egyseg[4].elet[m] < egyseg[4].elet[tdb]) && egyseg[4].elet[m]>0));
            if (xten && yten  && megyvazonos  && tavazonosvmegy){
                tdb = m;
            }
        }
    }
    if (tdb != -1){
        egyseg[4].elet[tdb] -= egyseg[tipus].sebzes;
    }
    else if (tipus == 4){
        int tamadandoegyseg = -1;
        for (int egysegf=1;egysegf<4;egysegf++){
            for (KorElemei *elem = elerhetok;elem != NULL;elem = elem->kov){
                for (int m = 0; m<egyseg[egysegf].db;m++){
                    bool xten = elem->eleme->x == egyseg[egysegf].x[m];
                    bool yten = elem->eleme->y == egyseg[egysegf].y[m];
                    bool megyvazonos = ((tdb == -1 && elem->eleme->babu == &egyseg[egysegf] &&  elem->eleme->babu->kie[m] != egyseg[tipus].kie[i]) || (tdb != -1 && egyseg[tipus].kie[i] != egyseg[egysegf].kie[tdb]));
                    bool tavazonosvmegy = (tdb == -1 || ((tdb != -1 && (tavolsag(egyseg[egysegf].x[m],egyseg[egysegf].y[m],egyseg[tipus].x[i],egyseg[tipus].y[i])>tavolsag(egyseg[egysegf].x[tdb],egyseg[egysegf].y[tdb],egyseg[tipus].x[i],egyseg[tipus].y[i]))) || (tavolsag(egyseg[egysegf].x[m],egyseg[egysegf].y[m],egyseg[tipus].x[i],egyseg[tipus].y[i])==tavolsag(egyseg[egysegf].x[tdb],egyseg[egysegf].y[tdb],egyseg[tipus].x[i],egyseg[tipus].y[i]))) && ((egyseg[egysegf].elet[m] < egyseg[egysegf].elet[tdb]) && egyseg[egysegf].elet[m]>0));
                    if (xten && yten  && megyvazonos  && tavazonosvmegy){
                        tdb = m;
                        tamadandoegyseg = egysegf;
                    }
                }
            }
        }
        if (tdb != -1){
            egyseg[tamadandoegyseg].elet[tdb] -= egyseg[tipus].sebzes;
        }
    }
    felszabaditt_kor(elerhetok);
}

