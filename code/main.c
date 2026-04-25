#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"

/**
 * Funzione che prende l'input inserito dall'utente e lo converte in un comando
 * @param char* stringa del comando dell'utente
 * @return TipoComando tipo del comando inserito dall'utente
*/
TipoComando parse(char* input){
    char prime_3[4];
    strncpy(prime_3, input, 3);
    prime_3[3] = '\0';
    if(strcmp(prime_3, "vai") == 0)                 return VAI;
    else if(strcmp(prime_3, "gua") == 0)            return GUARDA;
    else if(strcmp(prime_3, "pre") == 0)            return PRENDI;
    else if(strcmp(prime_3, "usa") == 0)            return USA;
    else if(strcmp(prime_3, "att") == 0)            return ATTACCA;
    else if(strcmp(prime_3, "inv") == 0)            return INVENTARIO;
    else if(strcmp(prime_3, "sal") == 0)            return SALVA;
    else if(strcmp(prime_3, "car") == 0)            return CARICA;
    else if(strcmp(prime_3, "map") == 0)            return MAPPA;
    else if(strcmp(prime_3, "hel") == 0)            return HELP;
}

int main(){
    char input[MAX_DIMINPUT];
    fgets(input, MAX_DIMINPUT, stdin);
    TipoComando dato = parse(input);
}