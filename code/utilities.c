#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utilities.h"
#include "../include/mappa.h"
#include "../include/eroe.h"
#include "../include/combattimento.h"

void controlla_allocazione(void* ptr){
    if(ptr == NULL){
        printf("Errore nell'allocazione della memoria o nell'apertura di un file");
        exit(1);
    }
}

char** dividi_input(char* input){
    char** output = malloc(2 * sizeof(char*));                  //crea il doppio puntatore
    output[0] = malloc(4*sizeof(char));                         //crea la prima stringa
    strncpy(output[0], input, 3);                               //copia i primi 3 caratteri per il comando
    output[0][3] = '\0';
    int i = strlen(input) - 1;                                  //calcola la lunghezza totale della stringa
    while (i >= 0 && (input[i] == '\n' || input[i] == ' '))     //e scopri quanto è lunga la seconda parola fermandoti al primo spazio
        i--;
    int end = i;                                                //salva l'indice di inizio dell'ultima parola
    while (i >= 0 && input[i] != ' ')                           //trova l'inizio della parola
        i--;
    int len = end - i;                                          //e calcolane la lunghezza
    output[1] = malloc((len + 1)*sizeof(char));
    strncpy(output[1], input + i + 1, len);                     //crea e copia la stringa
    output[1][len] = '\0';
    return output;
}

TipoComando parse(char* input){
    if(strcmp(input, "vai") == 0)                 return VAI;
    else if(strcmp(input, "gua") == 0)            return GUARDA;
    else if(strcmp(input, "pre") == 0)            return PRENDI;
    else if(strcmp(input, "usa") == 0)            return USA;
    else if(strcmp(input, "att") == 0)            return ATTACCA;
    else if(strcmp(input, "inv") == 0)            return INVENTARIO;
    else if(strcmp(input, "sal") == 0)            return SALVA;
    else if(strcmp(input, "car") == 0)            return CARICA;
    else if(strcmp(input, "map") == 0)            return MAPPA;
    else if(strcmp(input, "hel") == 0)            return HELP;
    else                                        return INVALIDO;
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
    FILE* f = fopen("partita.sav", "wb");                                                   //apri il file in modalità binaria
    controlla_allocazione(f);
    fwrite(&(e->HP), sizeof(e->HP), 1, f);                                                  //scrivi i dati dell'eroe (HP, XP, sheld, danno)
    fwrite(&(e->XP), sizeof(e->XP), 1, f);
    fwrite(&(e->sheld), sizeof(e->sheld), 1, f);
    fwrite(&(e->danno), sizeof(e->danno), 1, f);
    Oggetto* oggetto_tmp = e->inventario->next;                                             //crea un oggetto temporaneo per salvare l'inventario
    fwrite(&(e->inventario->len), sizeof(e->inventario->len), 1, f);                        //salva la linghezza dell'inventario
    while(oggetto_tmp != NULL){                                                             //salva i dati dell'inventario su file
        fwrite(&(oggetto_tmp->tipo), sizeof(oggetto_tmp->tipo), 1, f);
        fwrite(&(oggetto_tmp->val), sizeof(oggetto_tmp->val), 1, f);
        oggetto_tmp = oggetto_tmp->next;
    }
    Stanza* stanza_tmp = e->mappa->inizio;                                                  //crea la stanza temporanea per salvare la mappa
    fwrite(&(e->mappa->numero_stanze), sizeof(e->mappa->numero_stanze), 1, f);              //salva il numero di stanze della mappa (solo quelle allocata)
    while(stanza_tmp != NULL){                                                              //salva i dati di tutte le stanze su file
        fwrite(&(stanza_tmp->ID), sizeof(stanza_tmp->ID), 1, f);
        fwrite(&(stanza_tmp->oggetto->tipo), sizeof(stanza_tmp->oggetto->tipo), 1, f);
        fwrite(&(stanza_tmp->oggetto->val), sizeof(stanza_tmp->oggetto->val), 1, f);
        fwrite(&(stanza_tmp->mostro->tipo), sizeof(stanza_tmp->mostro->tipo), 1, f);
        fwrite(&(stanza_tmp->mostro->HP), sizeof(stanza_tmp->mostro->HP), 1, f);
        fwrite(&(stanza_tmp->mostro->XP), sizeof(stanza_tmp->mostro->XP), 1, f);
        fwrite(&(stanza_tmp->mostro->danno), sizeof(stanza_tmp->mostro->danno), 1, f);
        stanza_tmp = stanza_tmp->next;
    }
    fwrite(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);                //salva l'ID della stanza corrente in cui si trova l'eroe
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
        fread(&(stanza_tmp->mostro->HP), sizeof(stanza_tmp->mostro->HP), 1, f);
        fread(&(stanza_tmp->mostro->XP), sizeof(stanza_tmp->mostro->XP), 1, f);
        fread(&(stanza_tmp->mostro->danno), sizeof(stanza_tmp->mostro->danno), 1, f);
        stanza_tmp = stanza_tmp->next;
    }
    fread(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);
    fclose(f);
    return e;
}

void esegui_comando(Eroe* e, TipoComando cmd, char* argomento){
    Bool esito;
    switch(cmd){
        case VAI:
            cambia_stanza(e, argomento);
            break;
        case GUARDA:
            //stampa la descrizione della stanza
            break;
        case PRENDI:
            prendi_oggetto(e, tipo_oggetto(argomento));
            break;
        case USA:
            usa_oggetto(e, argomento);
            break;
        case ATTACCA:
            esito = combattimento(e, argomento);
            break;
        case INVENTARIO:
            stampa_inventario(e->inventario);
            break;
        case SALVA:
            salva_partita(e);
            break;
        case MAPPA:
            //funzione stampa mappa
            break;
        case HELP:
            help();
            break;
        case INVALIDO:
            printf("Comando non valido. Digita help per vedere i comandi disponibili\n");
            break;
    }
}