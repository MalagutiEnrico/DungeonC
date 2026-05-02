/*Questo programma converte una mappa dal formato .txt al formato .map
Ogni stanza è allocata quando un giocatore ci entra per la prima volta; è quindi necessario 
identificare ogni stanza con un numero, caricarla nel gioco e poi collegarla con le altre.
Ogni stanza è rappresentata da una riga nel file, e i valori sono separati da uno spazio

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
valore                  valore dell'oggetto presente nella stanza.

Esempio di mappa

                            Stanza 4
                               ^
                               |
        Stanza 3    <-      Stanza 1        ->    Stanza 2
                      (no mostri o oggetti)
La riga nel file.txt della stanza 1 sarà la seguente:
1 4 2 -1 3 0 0 0 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"

int main(){
    int num_stanze;
    StanzaSalvataggio* s = (StanzaSalvataggio*)malloc(sizeof(StanzaSalvataggio));
    FILE* f_txt = fopen("mappa.txt", "r");
    if(f_txt == NULL){
        printf("Errore nell'apertura del file di testo");
        exit(1);
    }
    FILE* f_map = fopen("mappa.map", "wb");
    if(f_map == NULL){
        printf("Errore nell'apertura del file binario di salvataggio\n");
        exit(1);
    }
    fscanf(f_txt, "%d", &num_stanze);
    for(int i=0; i<num_stanze; i++){
        if(fscanf(f_txt, "%d %d %d %d %d %d %d %d", &s->ID, &s->nord, &s->est, &s->sud, &s->ovest, &s->tipo_mostro, &s->tipo_oggetto, &s->valore_oggetto) != 8){
            printf("Errore nella lettura di una riga del file, in particolare la riga numero %d\n", i);
            fclose(f_txt);
            fclose(f_map);
            exit(1);
        }
        fwrite(s, sizeof(StanzaSalvataggio), 1, f_map);
    }
    printf("File convertito correttamente\n");
    fclose(f_txt);
    fclose(f_map);
    free(s);
    return 0;
}