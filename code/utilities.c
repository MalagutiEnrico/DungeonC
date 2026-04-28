#include "../include/utilities.h"

void controlla_allocazione(void* ptr){
    if(ptr == NULL){
        printf("Errore nell'allocazione della memoria o nell'apertura di un file");
        exit(1);
    }
}

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

void help(){
    printf("LISTA COMANDI:\n");
    printf("VAI <direzione>:\tcomando che ti fa andare in una stanza\n");
    printf("GUARDA:\tcomando che ti stampa cosa c'è nella stanza\n");
    printf("PRENDI <oggetto>:\tcomando che ti prende un oggetto\n");
    printf("USA <oggetto>:\tcomando che ti fa usare un oggetto\n");
    printf("ATTACCA <mostro>:\tcomando che ti fa attaccare\n");
    printf("INVENTARIO:\t comando che ti mostra l'inventario\n");
    printf("SALVA:\tcomando che ti fa i dari del gioco\n");
    printf("CARICA:\tcomando che ti carica i dati della partita\n");
    printf("MAPPA:\tcomando che ti mostra la mappa\n");
}