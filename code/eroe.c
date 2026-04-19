#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/eroe.h"

Inventario* crea_inventario(){
    Inventario* i = (Inventario*)malloc(sizeof(Inventario));
    controlla_allocazione(i);
    i->len = 0;
    i->next = NULL;
    return i;
}

Eroe* crea_eroe(){
    Eroe* e = (Eroe*)malloc(sizeof(Eroe));
    controlla_allocazione(e);
    e->HP = MAX_SALUTE;
    e->XP = 0;
    e->inventario = crea_inventario();
    //manca la stanza
}