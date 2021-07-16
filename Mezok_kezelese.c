#include "Mezok_kezelese.h"

void szomszedok_feltoltese(Mezo *lista) {
    for (Mezo *m = lista->kov; m->kov != NULL; m = m->kov){
        for (Mezo *sz = lista->kov; sz->kov != NULL; sz = sz->kov){
            if(m->y+1 == sz->y && m->x == sz->x){
                m->fel = sz;
            }
            if(m->y-1 == sz->y && m->x == sz->x){
                m->also = sz;
            }
            if(m->x+1 == sz->x && m->y == sz->y){
                m->jobb = sz;
            }
            if(m->x-1 == sz->x && m->y == sz->y){
                m->bal = sz;
            }
        }
    }
}
Mezo *elkereso(Mezo *lista, int x, int y) {
    Mezo *kezdo = NULL;
    int kezdoel = 0;
    Mezo *cel = NULL;
    for (kezdo = lista->kov;kezdo->kov != NULL;kezdo =kezdo->kov) {
        if(kezdo->x == x && kezdo->y == y){
            kezdoel = kezdo->el;
        }
    }
    for (cel = lista->kov;cel->kov != NULL;cel =cel->kov){
        switch (kezdoel) {
            case 1:
                if (cel->x == x+14 && cel->y == y+14){
                    return cel;
                }
                break;
            case 2:
                if (cel->x == x-14 && cel->y == y+14){
                    return cel;
                }
                break;
            case 3:
                if (cel->x == x+14 && cel->y == y-14){
                    return cel;
                }
                break;
            case 4:
                if (cel->x == x-14 && cel->y == y-14){
                    return cel;
                }
                break;
            default:
                break;
        }

    }
    return cel;
}