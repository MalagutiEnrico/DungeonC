#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"

TipoComando parse(char* input){
    char prime_3[4];
    strncpy(prime_3, input, 3);
    prime_3[3] = '\0';
   
    if(strcmp(prime_3, "vai") == 0){
        //funzione che sposta il giocatore
    }
    else if(strcmp(prime_3, "usa") == 0){
        //funzione che usa un oggetto
    }
    else if(strcmp(prime_3, "help") == 0){
        //funzione che ti aiuta
    }
    else if(strcmp(prime_3, "salva") == 0){
        //funzione che salva i dati
    }
    else if(strcmp(prime_3, "mappa") == 0){
        //funzione per la mappa
    }
    else if(strcmp(prime_3, "guarda") == 0){
        //funzione guarda stanza
    }
    else if(strcmp(prime_3, "prendi") == 0){
        //funzione che prende un oggetto
    }
    else if(strcmp(prime_3, "carica") == 0){
        //funzione che carica i dati
    }
    else if(strcmp(prime_3, "attacca") == 0){
        //funzione che attacca il mostro
    }
    else if(strcmp(prime_3, "inventario") == 0){
        //funzione per vedere l'inventario
    }
}

void stampa_stato(Eroe* e){
    
}

int main(){
    char input[MAX_DIMINPUT];
    fgets(input, MAX_DIMINPUT, stdin);
    TipoComando dato = parse(input);
}