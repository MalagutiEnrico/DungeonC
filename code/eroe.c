#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/eroe.h"
#include "../include/mappa.h"

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
    e->mappa = crea_mappa();
    StanzaSalvataggio* s_s = carica_stanza(1);
    e->stanza_corrente = converti_stanza(s_s);
    e->mappa->inizio = e->stanza_corrente;
    return e;
}

void cambia_stanza(Eroe* e, char* direzione){
    int numero_stanza;
    Stanza* s = NULL;
    Stanza* stanza_corrente = e->stanza_corrente;
    if(!strcmp(direzione, "nor")){                       //in base alla direzione collega le stanza
        numero_stanza = stanza_corrente->numero_nord;
    }
    else if(!strcmp(direzione, "est")){
        numero_stanza = stanza_corrente->numero_est;
    }
    else if(!strcmp(direzione, "sud")){
        numero_stanza = stanza_corrente->numero_sud;
    }
    else if(!strcmp(direzione, "ove")){
        numero_stanza = stanza_corrente->numero_ovest;
    }
    if(numero_stanza == -1){
        printf("In questa direzio è presente un muro. Cambia direzione oppure usa una torcia per vedere dove andare\n");
    }
    else if(trova_stanza(e->mappa, numero_stanza)){                          //se trova la stanza, allora la collega
        s = e->mappa->inizio;
        while(s->ID != numero_stanza)
            s = s->next;
        e->stanza_corrente = s;
    }
    else{                                                               //altrimenti la deve creare
        e->stanza_corrente = crea_stanza(e->stanza_corrente, direzione);                                                          //altrimenti la imposta come stanza corrente
    }
}

TipoOggetto tipo_oggetto(char input){
    if(strcmp(input, "pozione") == 0)
        return POZIONE;
}

void prendi_oggetto(Eroe* e, TipoOggetto tipo){
    Oggetto* o = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(o);
    o->tipo = tipo;
    if(e->inventario->len == 0){
        e->inventario->next = o;
    }
}