#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void salva_partita(Eroe* e){
    FILE* f = fopen("partita.sav", "wb");
    controlla_allocazione(f);
    fwrite(&(e->HP), sizeof(e->HP), 1, f);
    fwrite(&(e->XP), sizeof(e->XP), 1, f);
    fwrite(&(e->sheld), sizeof(e->sheld), 1, f);
    fwrite(&(e->danno), sizeof(e->danno), 1, f);
    Oggetto* oggetto_tmp = e->inventario->next;
    fwrite(&(e->inventario->len), sizeof(e->inventario->len), 1, f);
    while(oggetto_tmp != NULL){
        fwrite(&(oggetto_tmp->tipo), sizeof(oggetto_tmp->tipo), 1, f);
        fwrite(&(oggetto_tmp->val), sizeof(oggetto_tmp->val), 1, f);
        oggetto_tmp = oggetto_tmp->next;
    }
    Stanza* stanza_tmp = e->mappa->inizio;
    fwrite(&(e->mappa->numero_stanze), sizeof(e->mappa->numero_stanze), 1, f);
    while(stanza_tmp != NULL){
        fwrite(&(stanza_tmp->ID), sizeof(stanza_tmp->ID), 1, f);
        fwrite(&(stanza_tmp->oggetto->tipo), sizeof(stanza_tmp->oggetto->tipo), 1, f);
        fwrite(&(stanza_tmp->oggetto->val), sizeof(stanza_tmp->oggetto->val), 1, f);
        fwrite(&(stanza_tmp->mostro->tipo), sizeof(stanza_tmp->mostro->tipo), 1, f);
        fwrite(&(stanza_tmp->mostro->val), sizeof(stanza_tmp->mostro->val), 1, f);
        stanza_tmp = stanza_tmp->next;
    }
    fwrite(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);
    fclose(f);
    printf("Dati salvati su file. Il programma può terminare\n");
}

Eroe* carica_partita(){
    Eroe* e = (Eroe*)malloc(sizeof(Eroe));
    controlla_allocazione(e);
    FILE* f = fopen("partita.sav", "rb");
    controlla_allocazione(f);
    fread(&(e->HP), sizeof(e->HP), 1, f);
    fread(&(e->XP), sizeof(e->XP), 1, f);
    fread(&(e->sheld), sizeof(e->sheld), 1, f);
    fread(&(e->danno), sizeof(e->danno), 1, f);
    fread(&(e->inventario->len), sizeof(e->inventario->len), 1, f);
    Oggetto* oggetto_tmp = e->inventario->next;
    while(oggetto_tmp != NULL){
        fread(&(oggetto_tmp->tipo), sizeof(oggetto_tmp->tipo), 1, f);
        fread(&(oggetto_tmp->val), sizeof(oggetto_tmp->val), 1, f);
        oggetto_tmp = oggetto_tmp->next;
    }
    Stanza* stanza_tmp = e->mappa->inizio;
    while(stanza_tmp != NULL){
        fread(&(stanza_tmp->ID), sizeof(stanza_tmp->ID), 1, f);
        fread(&(stanza_tmp->oggetto->tipo), sizeof(stanza_tmp->oggetto->tipo), 1, f);
        fread(&(stanza_tmp->oggetto->val), sizeof(stanza_tmp->oggetto->val), 1, f);
        fread(&(stanza_tmp->mostro->tipo), sizeof(stanza_tmp->mostro->tipo), 1, f);
        fread(&(stanza_tmp->mostro->val), sizeof(stanza_tmp->mostro->val), 1, f);
        stanza_tmp = stanza_tmp->next;
    }
    fread(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);
    fclose(f);
    return e;
}