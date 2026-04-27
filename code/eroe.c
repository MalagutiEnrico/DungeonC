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
    printf("Oggetti presenti nell'inventario: ");
    while(current != NULL){                                                                 //scorri ogni oggetto nell'inventario
        switch(current->tipo){                                                              //output in base al tipo
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
                printf("Questa torcia ti permette di vedere al buio\n");
                break;
        }
        current = current->next;
    }
}

Eroe* crea_eroe(){
    Eroe* e = (Eroe*)malloc(sizeof(Eroe));
    controlla_allocazione(e);
    e->HP = MAX_SALUTE;                             //inizializza i valori dell'eroe
    e->XP = 0;
    e->inventario = crea_inventario();
    e->mappa = crea_mappa();
    StanzaSalvataggio* s_s = carica_stanza(1);      //carica la stanza numero 1, quella in cui inizia il gioco
    e->stanza_corrente = converti_stanza(s_s);      //e convertila in una stanza adatta al videogioco
    e->mappa->inizio = e->stanza_corrente;          //infine impostala come stanza corrente dell'eroe
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
        numero_stanza = stanza_corrente->numero_nord;    //imposta il numero della stanza successiva
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
    if(numero_stanza == 0){                            //in caso sia uguale a 0 vuole dire che la stanza non è accessibile
        printf("In questa direzione è presente un muro. Cambia direzione oppure usa una torcia per vedere dove andare\n");
    }
    else if(numero_stanza < 0){                         //caso stanza protetta da chiave
        printf("Per entrare in questa stanza serve una chiave\n");
    }
    else if(trova_stanza(e->mappa, numero_stanza)){     //se trova la stanza in quelle già caricate, allora la collega alla stanza di provenienza
        s = e->mappa->inizio;
        while(s->ID != numero_stanza)
            s = s->next;
        e->stanza_corrente = s;
    }
    else{                                               //altrimenti la deve creare, caricandola dal file
        e->stanza_corrente = crea_stanza(e->stanza_corrente, direzione);
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
    Oggetto* o = (Oggetto*)malloc(sizeof(Oggetto));                             //crea l'oggetto
    controlla_allocazione(o);
    o->tipo = tipo;
    o->next = NULL;
    if(e->inventario->len == MAX_INVENTARIO){                                   //in caso l'inventario sia già pieno, non metterlo dentro
        printf("Inventario pieno. Usa qualche oggetto per liberare spazio\n");
    }
    else{
        if(e->inventario->len == 0){                                            //caso in cui l'inventario sia vuoto
            e->inventario->next = o;
        }
        else{                                                                   //caso in cui fosse già presente qualche altro oggetto
            Oggetto* tmp = e->inventario->next;
            while(tmp->next != NULL)
                tmp = tmp->next;
            tmp->next = o;
        }
        e->inventario->len++;
    }
}

Bool trova_oggetto(Eroe* e, TipoOggetto o){
    Oggetto* tmp = e->inventario->next;
    while(tmp != NULL){
        if(tmp->tipo == o)
            return true;
    }
    return false;
}

void elimina_oggetto(Inventario* i, Oggetto* o){
    Oggetto* current = i->next;
    while(current != NULL){
        if(current->tipo == o->tipo){
            Oggetto* tmp = current->next;
            current->next = current->next->next;
            free(tmp);
            i->len--;
            return;
        }
        current = current->next;
    }
}

void usa_oggetto(Eroe* e, Oggetto* o){
    if(trova_oggetto(e, o->tipo)){
        switch(o->tipo){
            case POZIONE:
                //aggiunti punti vita
                break;
            case ARMA:
                //aggiungi punti danno
                break;
            case ARMATURA:
                //aumenta i punti ferita massimi
                break;
            case CHIAVE:
                //sblocca una porta con ID uguale
                break;
            case TORCIA:
                //stampa una descrizione delle porte accessibili dalla stanza
                break;  
        }
        elimina_oggetto(e->inventario, o);
    }
    else{
        printf("Oggetto non presente nell'inventario\n");
    }
}

void elimina_inventario(Inventario* i){
    Oggetto* o = i->next;
    while(o != NULL){
        Oggetto* tmp = o;
        o = o->next;
        free(tmp);
    }
    free(i);
}

void usa_torcia(Eroe* e){
    Stanza* s = e->stanza_corrente;
    if(s->numero_nord == 0)
        //caso in cui non ci possa andare
    else if(s->numero_nord < 0)
        //ci può andare ma serve la chiave
    else
        //ci può andare
}