#include "Minden_inicializalasi_elem.h"

void inic_egyseg(Egyseg *egysegek,int Height) {
    memset(&egysegek[0], 0, sizeof(Egyseg));
    memset(&egysegek[1], 0, sizeof(Egyseg));
    memset(&egysegek[2], 0, sizeof(Egyseg));
    memset(&egysegek[3], 0, sizeof(Egyseg));
    memset(&egysegek[4], 0, sizeof(Egyseg));
    egysegek[0].range = -1;
    //fal
    egysegek[1].azon = 1;
    egysegek[1].eredeti_x = 30;
    egysegek[1].eredeti_y = Height - 35;
    egysegek[1].meret = 10;
    egysegek[1].ara = 1;
    egysegek[1].kezdoelet = 30;
    egysegek[2].range = -1;
    //bastya
    egysegek[2].eredeti_x = 50;
    egysegek[2].eredeti_y = Height - 25;
    egysegek[2].meret = 20;
    egysegek[2].azon = 2;
    egysegek[2].ara = 5;
    egysegek[2].kezdoelet = 75;
    egysegek[2].sebzes = 10;
    egysegek[2].range = 3;
    //palyzs
    egysegek[3].eredeti_x = 90;
    egysegek[3].eredeti_y = Height - 35;
    egysegek[3].meret = 10;
    egysegek[3].azon = 3;
    egysegek[3].ara = 4;
    egysegek[3].kezdoelet = 90;
    egysegek[3].range = -1;
    //felderítő
    egysegek[4].eredeti_x = 110;
    egysegek[4].eredeti_y = Height - 35;
    egysegek[4].meret = 10;
    egysegek[4].azon = 4;
    egysegek[4].ara = 1;
    egysegek[4].kezdoelet = 15;
    egysegek[4].sebzes = 5;
    egysegek[4].range = 5;
}
Mezo *inic_listaelso() {
    Mezo *lista = (Mezo *) malloc(sizeof(Mezo));
    memset(lista, 0, sizeof(Mezo));
    lista->kov = (Mezo *) malloc(sizeof(Mezo));
    memset(lista->kov, 0, sizeof(Mezo));
    lista->kov->elozo = lista;
    return lista;
}
void inic_jatekosok(struct Jatekos *jatekosok,int Elet) {
    memset(jatekosok, 0, sizeof(Jatekos) * 2);
    jatekosok[0].elet = Elet;
    jatekosok[1].elet = Elet;
    jatekosok[0].allopont = 20;//5 pont körönként majd 10 körönként plusz egy pont
    jatekosok[1].allopont = 20;
    jatekosok[0].mozgopont = 5;//25% veszíteni körönként
    jatekosok[1].mozgopont = 5;
    jatekosok[1].azon = 1;
}
Mezo *inicializalas_struckturak(Egyseg *egysegek, Jatekos jatekosok[2], Vezerlesiadatok *vezerloadatok,Palya *palya,int Height, int Elet) {
    inic_egyseg(egysegek,Height);
    inic_jatekosok(jatekosok,Elet);
    vezerloadatok->quit = false;
    vezerloadatok->vege = false;
    vezerloadatok->start = true;
    vezerloadatok->torolt = true;
    vezerloadatok->ujrajz = true;
    vezerloadatok->kor_vege = false;
    vezerloadatok->menu = true;
    vezerloadatok->beolvas = false;
    vezerloadatok->jatekos = 0;
    vezerloadatok->kor_szama = 0;
    vezerloadatok->egyseg_val = 1;
    palya->egyseg = egysegek;
    palya->jatekos = jatekosok;
    palya->mezo = inic_listaelso();
    return palya->mezo;
}