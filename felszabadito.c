#include "felszabadito.h"

void felszabaditt_egysegek(struct Egyseg *egysegek, int meret) {
    for (int i = 0; i < meret; i++) {
        free(egysegek[i].x);
        free(egysegek[i].y);
        free(egysegek[i].elet);
        free(egysegek[i].kie);
    }
}
void felszabaditt_lista(Mezo *lista) {
    while (lista) {
        Mezo *temp = lista->kov;
        free(lista);
        lista = temp;
    }
}