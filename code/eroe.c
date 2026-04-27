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
    e->sheld = 0;
    e->danno = 0;
    e->inventario = crea_inventario();
    e->mappa = crea_mappa();
    StanzaSalvataggio* s_s = carica_stanza(1);      //carica la stanza numero 1, quella in cui inizia il gioco
    e->stanza_corrente = converti_stanza(s_s);      //e convertila in una stanza adatta al videogioco
    e->mappa->inizio = e->stanza_corrente;          //infine impostala come stanza corrente dell'eroe
    return e;
}

void stampa_stato(Eroe* e){
    printf("\033[31m HP:%d \033[0m\n", e->HP);
    printf("||");
    printf("\033[33mXP:%d\033[0m\n", e->XP);
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
    if(numero_stanza == -1){                            //in caso sia uguale a 0 vuole dire che la stanza non è accessibile
        printf("In questa direzione è presente un muro. Cambia direzione oppure usa una torcia per vedere dove andare\n");
    }
    else if(numero_stanza < -1){                         //caso stanza protetta da chiave
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

TipoOggetto tipo_oggetto(char* input){
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
    if(e->inventario->len == MAX_INVENTARIO){                                   //in caso l'inventario sia già pieno, non metterlo dentro
        printf("Inventario pieno. Usa qualche oggetto per liberare spazio\n");
    }
    else{
        Oggetto* o = (Oggetto*)malloc(sizeof(Oggetto));                             //crea l'oggetto
        controlla_allocazione(o);
        o->tipo = tipo;
        o->next = NULL;
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
        tmp = tmp->next;
    }
    return false;
}

void elimina_oggetto(Inventario* i, Oggetto* o){
    if(i->next->tipo == o->tipo){
        Oggetto* tmp = i->next;
        i->next = i->next->next;
        free(tmp);
        i->len--;
        return;
    }
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
    Bool usato = true;
    if(trova_oggetto(e, o->tipo)){                                                  //se trova l'oggetto
        switch(o->tipo){                                                            //in base al tipo di oggetto
            case POZIONE:
                usa_pozione(e, o->val);
                printf("Pozione utilizzata. Ora hai %d HP\n", e->HP);
                break;
            case ARMA:
                usa_arma(e, o->val);
                printf("Spada Equipaggiata. Ora hai %d danni base\n", e->danno);
                break;
            case ARMATURA:
                usa_armatura(e, o->val);
                printf("Armatura equipaggiata. Ora hai %d punti sheld\n", e->sheld);
                break;
            case CHIAVE:
                usato = usa_chiave(e, o->val);
                break;
            case TORCIA:
                //stampa una descrizione delle porte accessibili dalla stanza
                break;  
        }
        if(usato)                                                                       //se usato è true, allora lo elimina dalla lista
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

void usa_pozione(Eroe* e, int val){
    if((e->HP + val) > MAX_SALUTE)          //se la somma della salute aggiunta supera quella della salute massima, assegna il valore massimo della salute
        e->HP = MAX_SALUTE;
    else
        e->HP = e->HP + val;                //altrimenti aggiungi il valore della pozione
}

void usa_arma(Eroe* e, int val){
    e->danno = val;
}

void usa_armatura(Eroe* e, int val){
    e->sheld = val;
}

Bool usa_chiave(Eroe* e, int val){
    Stanza* s = e->stanza_corrente;             //controlla tra le stanze
    if(s->numero_nord == -val){                 //in caso il valore della stanza nella direzione sia il negativo del valore della chiave, allora la chiave apre quella porta
        s->numero_nord = val;
        return true;
    }
    else if(s->numero_est == -val){
        s->numero_est = val;
        return true;
    }
    else if(s->numero_sud == -val){
        s->numero_sud = val;
        return true;
    }
    else if(s->numero_ovest == -val){
        s->numero_ovest = val;
        return true;
    }
    else{
        printf("Non è possibile utilizzare la chiave");
        return false;
    }
}

void usa_torcia(Eroe* e){
    Stanza* s = e->stanza_corrente;
    if(s->numero_nord == 0){
        printf("Nella stanza a nord puoi entrare\n");
    }
    else if(s->numero_nord < 0){
        printf("La stanza nord è bloccata da chiave\n");
    }
    else{
        printf("Nella stanza nord non puoi entrare\n");
    }

    if(s->numero_sud == 0){
        printf("Nella stanza a sud puoi entrare\n");
    }
    else if(s->numero_sud < 0){
        printf("La stanza sud è bloccata da chiave\n");
    }
    else{
        printf("Nella stanza sud non puoi entrare\n");
    }

    if(s->numero_est == 0){
        printf("Nella stanza a est puoi entrare\n");
    }
    else if(s->numero_est < 0){
        printf("La stanza est è bloccata da chiave\n");
    }
    else{
        printf("Nella stanza est non puoi entrare\n");
    }

    if(s->numero_ovest == 0){
        printf("Nella stanza a ovest puoi entrare\n");
    }
    else if(s->numero_ovest < 0){
        printf("La stanza ovest è bloccata da chiave\n");
    }
    else{
        printf("Nella stanza ovest non puoi entrare\n");
    }
}