/*Questo programma converte una mappa dal formato .txt al formato .map

Struttura del file txt in input:
NUMERO_STANZE           numero delle stanze presenti nel file

per ogni stanza è presente questa struttura:
ID                      ID della stanza -> serve per identificare la stanza nella mappa
nord                    numeri della stanze presenti nelle varie direzioni della stanza corrente
est
sud
ovest
tipo_mostro             numero del tipo di mostro che è presente nella stanza
tipo_oggetto            numero del tipo di oggetto che è presente nella stanza

Ogni stanza è rappresentata da una riga nel file, e i valori sono separati da uno spazio

Ogni stanza è allocata quando un giocatore ci entra per la prima volta; è quindi necessario 
identificare ogni stanza con un numero, caricarla nel gioco e poi collegarla con le altre.
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./include/tipi.h"

StanzaSalvataggio* get_stanza(char nome_file, int *id){
    StanzaSalvataggio* s = (StanzaSalvataggio)*(sizeof(StanzaSalvataggio));
    controlla_allocazione(s);
    FILE* f = fopen(nome_file, "r");
    controlla_allocazione(f);
    fscanf("%d", &*id);
    fscanf("%d", s->ID);
    fscanf("%d", s->nord);
    fscanf("%d", s->est);
    fscanf("%d", s->sud);
    fscanf("%d", s->ovest);
    fscanf("%d", s->tipo_mostro);
    fscanf("%d", s->tipo_oggetto);
    fclose(f);
    return s;
}

void carica_stanza_bin(char nome_file, StanzaSalvataggio* stanze, int numero_stanze){
    FILE* f = fopen(nome_file, "wb");
    controlla_allocazione(f);
    fwrite(stanze[i], sizeof(StanzaSalvataggio), numero_stanze, f);
    fclose(f);
}

int main(){
    StanzaSalvataggio *s = NULL;
    
}