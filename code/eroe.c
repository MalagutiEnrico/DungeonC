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

void stampa_inventario(Inventario* i) {
    if (i == NULL) {
        printf("Inventario vuoto.\n");
        return;
    }
    Oggetto* current = i->next;
    printf("Oggetti presenti nell'inventario ");
    while(current != NULL){
        switch(current->tipo){
            case POZIONE:
                printf("Pozione con cura %d\n", current->val);
                break;
            case ARMA:
                printf("Arma con danno %d\n", current->val);
                break;  
            case ARMATURA:
                printf("Armatura con difesa %d\n", current->val);
                break;
            case CHIAVE:
                printf("Questa chiave sblocca una porta %d\n", current->val);
                break;
            case TORCIA:
                printf("Questa torcia ti permette di vedere al buio\n",current->val);
                break;
        }
        current = current->next;
    }
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

void stampa_stato(Eroe* e){
    printf("\033[31m HP:%D \033[0m\n", eroe->HP);
    printf("||");
    printf("\033[33mXP:%d\033[0m\n", eroe->XP);
    printf("||");
    printf("");
    printf("||");
    printf("");
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
    else if(strcmp(input, "arma") == 0)
        return ARMA;
    else if(strcmp(input, "armatura") == 0)
        return ARMATURA;
    else if(strcmp(input, "chiave") == 0)
        return CHIAVE;
    else if(strcmp(input, "torcia") == 0)
        return TORCIA;
    else
        return -1;
}

void prendi_oggetto(Eroe* e, TipoOggetto tipo){
    Oggetto* o = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(o);
    o->tipo = tipo;
    o->next = NULL;
    if(e->inventario->len == MAX_INVENTARIO){
        printf("Inventario pieno. Usa qualche oggetto per liberare spazio\n");
    }
    else{
        if(e->inventario->len == 0){
            e->inventario->next = o;
        }
        else{
            Oggetto* tmp = e->inventario->next;
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = o;
        }
        e->inventario->len++;
    }
}