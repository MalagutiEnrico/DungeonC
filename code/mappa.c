#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/mappa.h"

Bool trova_stanza(Mappa* stanze, int numero_stanza){
    if(numero_stanza == -1)                                     //stanza non presente
        return false;
    Stanza* current = stanze->inizio;
    while(current != NULL){                                     //scorri ogni stanza della lista
        if(current->ID == numero_stanza){                       //se la trova ritorna a true
            return true;
        }
        current = current->next;
    }
    return false;
}

StanzaSalvataggio* carica_stanza(int numero_stanza){
    FILE* f = fopen("mappa.map", "rb");
    controlla_allocazione(f);
    StanzaSalvataggio* s = (StanzaSalvataggio*)malloc(sizeof(StanzaSalvataggio)); //crea lo spazio di memoria per la stanza da leggere dal file
    controlla_allocazione(s);
    long int offset = sizeof(int) + numero_stanza * sizeof(StanzaSalvataggio);    //sizeof dettato dal numero delle stanze + le stanze effettive
    if(fseek(f, offset, SEEK_SET) != 0){                                          //sposta il cursore nella posizione dettata dall'offset
        fclose(f);                                                                //in caso non vada a buon fine chiudi i file e ritorna a NULL
        free(s);
        return NULL;
    }
    fread(s, sizeof(StanzaSalvataggio), 1, f);                                    //salva la stanza nella struct
    fclose(f);
    return s;
}

Stanza* converti_stanza(StanzaSalvataggio* s_s){
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));        //alloca lo spazio per una stanza
    controlla_allocazione(s);
    s->ID = s_s->ID;                                    //copia i valori della stanza dal salvataggio in quella gestibile nel gioco
    s->numero_nord = s_s->nord;
    s->numero_est = s_s->est;
    s->numero_sud = s_s->sud;
    s->numero_ovest = s_s->ovest;
    s->tipo_oggetto = s_s->tipo_oggetto;
    s->tipo_mostro = s_s->tipo_mostro;
    return s;
}

Mappa* crea_mappa(){
    Mappa* m = (Mappa*)malloc(sizeof(Mappa));
    controlla_allocazione(m);
    m->inizio = NULL;
    m->numero_stanze = 0;
    return m;
}

Oggetto* crea_oggetto(TipoOggetto o){
    Oggetto* ogg = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(ogg);
    ogg->tipo = o;
    switch(o){                                          //in base al tipo di oggetto avrà un valore diverso.
        case POZIONE:
            //potere curativo della pozione
            break;
        case ARMA:
            //punti danno dell'arma
            break;
        case ARMATURA:
            //punti danno aggiunti dall'armatura
            break;
        case CHIAVE:
            //numero della porta
            break;
        default:
            return NULL;
    }
    return ogg;
}

Mostro* crea_mostro(TipoMostro m){
    Mostro* mostro = (Mostro*)malloc(sizeof(Mostro));
    controlla_allocazione(mostro);
    mostro->tipo = m;
    mostro->next = NULL;
    switch(m){                                          //in base al tipo di mostro, avrà delle statistiche diverse
        case SCHELETRO:
            mostro->HP = 10;
            break;
        case GOBLIN:
            mostro->HP = 15;
            break;
        case DRAGO:
            mostro->HP = 40;
            break;
        case BOSS:
            mostro->HP = 80;
            break;
        default:
            return NULL;
            break;
    }
    return mostro;
}

Stanza* crea_stanza(Stanza* provenienza, char* direzione){
    StanzaSalvataggio* s_s = NULL;
    Stanza* s = NULL;
    if(!strcmp(direzione, "nor")){                          //in base alla direzione collega le stanza                                          //la stanza esiste
        s_s = carica_stanza(provenienza->numero_nord);             //carica la struttura da file
        s = converti_stanza(s_s);                           //la converte in una stanza del gioco
        provenienza->nord = s;                              //imposta i collegamenti con la stanza di provenienza
        s->sud = provenienza;
    }
    else if(!strcmp(direzione, "est")){
        s_s = carica_stanza(provenienza->numero_est);
        s = converti_stanza(s_s);
        provenienza->est = s;
        s->ovest = provenienza;
    }
    else if(!strcmp(direzione, "sud")){
        s_s = carica_stanza(provenienza->numero_sud);
        s = converti_stanza(s_s);
        provenienza->sud = s;
        s->nord = provenienza;
    }
    else if(!strcmp(direzione, "ove")){
        s_s = carica_stanza(provenienza->numero_ovest);
        s = converti_stanza(s_s);
        provenienza->ovest = s;
        s->est = provenienza;
    }
    free(s_s);                                                  //libera la memoria della stanza salvata
    s->oggetto = crea_oggetto(s->tipo_oggetto);                 //crea l'oggetto di tipo specificato dal file
    s->mostro = crea_mostro(s->tipo_mostro);                    //crea il mostro ti tipo specificato dal file
    return s;
}

void elimina_mappa(Mappa* p){
    Stanza* s = p->inizio;
    while(s != NULL){
        Stanza* tmp = s;
        s = s->next;
        free(tmp->oggetto);                                     //libera la memoria della lista di oggetti 
        free(tmp->mostro);                                      //libera la memoria della lista di mostri                                       //libera la memoria del puntatore alla stanza ovest
        free(tmp);
    }
    free(p);
}