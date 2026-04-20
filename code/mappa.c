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

Bool trova_stanza(int* stanze, int stanze_visitate, int numero_stanza){
    for(int i=0; i<stanze_visitate; i++){
        if(stanze[i] == numero_stanza)
            return true;
    }
    return false;
}

StanzaSalvataggio* carica_stanza(int numero_stanza){
    FILE f = fopen("mappa.map", "rb");
    controlla_allocazione(f);
    StanzaSalvataggio* s = malloc(sizeof(StanzaSalvataggio));
    controlla_allocazione(s);
    long int offset = numero_stanza * sizeof(int);
    fseek(f, offset, SEEK_SET);
    fread(s, sizeof(stanza), 1, f);
    fclose(f);
    return s;
}

Stanza* crea_stanza(Stanza* provenienza, char* direzione){
    int stanza_successiva;
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));                            //crea la nuova stanza
    StanzaSalvataggio* s_s = (StanzaSalvataggio*)malloc(sizeof(StanzaSalvataggio));
    controlla_allocazione(s);
    if(strcmp(direzione, "nor")){                                           //in base alla direzione collega le stanza
        stanza_successiva = s->nord;
        if(num == -1){
            printf("Stanza non accessibile\n");
        }
        else{
            s_s = carica_stanza(stanza_successiva);                         //carica la stanza presente nella posizione
        }
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