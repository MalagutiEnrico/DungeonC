#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/mappa.h"

Bool trova_stanza(int* stanze, int stanze_visitate, int numero_stanza){
    for(int i=0; i<stanze_visitate; i++){
        if(stanze[i] == numero_stanza)
            return true;
    }
    return false;
}

StanzaSalvataggio* carica_stanza(int numero_stanza){
    FILE* f = fopen("mappa.map", "rb");
    controlla_allocazione(f);
    StanzaSalvataggio* s = (StanzaSalvataggio*)malloc(sizeof(StanzaSalvataggio));
    controlla_allocazione(s);
    long int offset = sizeof(int) + numero_stanza * sizeof(StanzaSalvataggio);    //sizeof dettato dal numero delle stanze + le stanze effettive
    if(fseek(f, offset, SEEK_SET) != 0){
        fclose(f);
        free(s);
        return NULL;
    }
    fread(s, sizeof(StanzaSalvataggio), 1, f);
    fclose(f);
    return s;
}

Stanza* converti_stanza(StanzaSalvataggio* s_s){
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));        //alloca lo spazio per una stanza
    controlla_allocazione(s);
    s->numero_nord = s_s->nord;                                //copia i valori dei puntatori
    s->numero_est = s_s->est;
    s->numero_sud = s_s->sud;
    s->numero_ovest = s_s->ovest;
    s->tipo_oggetto = s_s->tipo_oggetto;
    s->tipo_mostro = s_s->tipo_mostro;
    return s;
}

Oggetto* crea_oggetto(TipoOggetto o){
    Oggetto* ogg = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(ogg);
    ogg->tipo = o;
    switch(o){
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
    }
    return ogg;
}

Mostro* crea_mostro(TipoMostro m){
    Mostro* mostro = (Mostro*)malloc(sizeof(Mostro));
    controlla_allocazione(mostro);
    mostro->tipo = m;
    mostro->next = NULL;
    switch(m){
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
            mostro->HP = 0;
            break;
    }
    return mostro;
}

Stanza* crea_stanza(Stanza* provenienza, char* direzione){
    StanzaSalvataggio* s_s = NULL;
    Stanza* s = NULL;
    if(!strcmp(direzione, "nor")){                       //in base alla direzione collega le stanza
        if(provenienza->numero_nord == -1){                              //caso in cui la stanza non esista
            return NULL;
        }
        else{                                           //la stanza esiste
            s_s = carica_stanza(provenienza->nord);               //carica la struttura da file
            s = converti_stanza(s_s);                   //la converte in una stanza del gioco
            provenienza->nord = s;                      //imposta i collegamenti con la stanza di provenienza
            s->sud = provenienza;
        }
    }
    else if(!strcmp(direzione, "est")){
        if(provenienza->numero_est == -1){
            return NULL;
        }
        else{
            s_s = carica_stanza(provenienza->est);
            s = converti_stanza(s_s);
            provenienza->est = s;
            s->ovest = provenienza;
        }
    }
    else if(!strcmp(direzione, "sud")){
        if(provenienza->numero_sud == -1){
            return NULL;
        }
        else{
            s_s = carica_stanza(provenienza->sud);
            s = converti_stanza(s_s);
            provenienza->sud = s;
            s->nord = provenienza;
        }
    }
    else if(!strcmp(direzione, "ove")){
        if(provenienza->numero_ovest == -1){
            return NULL;
        }
        else{
            s_s = carica_stanza(provenienza->ovest);
            s = converti_stanza(s_s);
            provenienza->ovest = s;
            s->est = provenienza;
        }
    }
    else{
        return NULL;                                            //caso in cui la direzione non sia valida   
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
        free(tmp->oggetto);                                      //libera la memoria della lista di oggetti 
        free(tmp->mostro);                                        //libera la memoria della lista di mostri                                       //libera la memoria del puntatore alla stanza ovest
        free(tmp);
    }
    free(p);
}