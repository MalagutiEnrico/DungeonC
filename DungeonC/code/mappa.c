#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/mappa.h"

void riempi_lista_oggetti(ListaOggetti* l){
    int numero_oggetti = rand() % MAX_OGGETTI;                  //genera un numero casuale di oggetti
    Oggetto* o = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(o);
    for(int i=0; i<numero_oggetti; i++){
        Oggetto* tmp = (Oggetto*)malloc(sizeof(Oggetto));       //crea l'oggetto temporaneo
        controlla_allocazione(tmp);
        tmp->tipo = rand() % NUM_OGGETTI;                       //crea un oggetto casuale
        if(i == 0){                                             //se è la prima interazione, allora lo inserisce all'inizio della lista
            l->head = tmp;
        }
        else{                                                   //altrimenti lo inserisce in coda
            o->next = tmp;
        }
        o = tmp;
        l->len++;                                               //aggiorno la lunghezza della lista
    }
    o->next = NULL;                                             //finito il ciclo, punta a NULL
}

ListaOggetti* crea_lista_oggetti(){
    ListaOggetti* l = (ListaOggetti*)malloc(sizeof(ListaOggetti));
    controlla_allocazione(p);
    riempi_lista_oggetti(&l);
    return l;
}

void riempi_lista_mostri(ListaMostri* l){
    int numero_mostri = rand() % NUM_MOSTRI;
    Mostro* m = (Mostro*)malloc(sizeof(Mostro));
    controlla_allocazione(m);
    for(int i=0; i<numero_mostri; i++){
        Mostro* tmp = (Mostro*)malloc(sizeof(Mostro));          //crea l'oggetto temporaneo
        controlla_allocazione(tmp);
        tmp->tipo = rand() % NUM_MOSTRI;                        //crea un oggetto casuale
        if(i == 0){                                             //se è la prima interazione, allora lo inserisce all'inizio della lista
            l->head = tmp;
        }
        else{                                                   //altrimenti lo inserisce in coda
            o->next = tmp;
        }
        o = tmp;
        l->len++; 
    }
}

ListaMostri* crea_lista_mostri(){
    ListaMostri* l = (ListaMostri*)malloc(sizeof(ListaMostri));
    controlla_allocazione(l);
    riempi_lista_mostri(&l);
}

Mappa* crea_mappa(){
    Mappa* p = (Mappa)malloc(sizeof(Mappa));
    controlla_allocazione(p);
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));                //crea la prima stanza del gioco
    controlla_allocazione(s);
    p->inizio = s;                                              //assegnala all'inizio della lista
    s->sud = NULL;                                              //cancella la stanza sud, non può uscire dal dungeon
    return p;   
}

Stanza* crea_stanza(Mappa* p, Stanza* provenienza, char* direzione){
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));                //crea la nuova stanza
    controlla_allocazione(s);
    if(strcmp(direzione, "nor")){                               //in base alla direzione collega le stanza
        provenienza->nord = s;
        s->sud = provenienza;
    }
    else if(strcmp(direzione, "est")){
        provenienza->est = s;
        s->ovest = provenienza;
    }
    else if(strcmp(direzione, "sud")){
        provenienza->sud = s;
        s->ovest = provenienza;
    }
    else if(strcmp(direzione, "ove")){
        provenienza->ovest = s;
        s->est = provenienza;
    }
    s->oggetti = crea_lista_oggetti();                          //popola la stanza di oggetti
    s->mostri = crea_lista_mostri();                            //popola la stanza di mostri
    return s;
}

/*Funzione che crea una nuova stanza. manca la mappatura generale (fine della mappa)
e manca la gestione delle direzioni delle altre stanze, in maniera casuale (?)*/