#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/utilities.h"
#include "../include/mappa.h"
#include "../include/eroe.h"
#include "../include/combattimento.h"

void controlla_allocazione(void* ptr){
    if(ptr == NULL){
        printf("Errore nell'allocazione della memoria");
        exit(1);
    }
}

void controlla_apertura(FILE* fp){
    if(fp == NULL){
        printf("Errore nell'apertura del file\n");
        exit(1);
    }
}

void clear_buffer(){
    char c;
    while((c = getchar()) && c != '\n'){}
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
    else if(strcmp(input, "esc") == 0)            return ESCI;
    else                                          return INVALIDO;
}

void help(){
    printf("LISTA COMANDI:\n");
    printf("VAI <(nord, sud, est, ovest)>:\tcomando che ti fa andare in una stanza\n");
    printf("GUARDA:\tcomando che ti stampa cosa c'è nella stanza\n");
    printf("PRENDI <(torcia, arma, armatura, pozione)>:\tcomando che ti prende un oggetto\n");
    printf("USA <(torcia, arma, armatura, pozione)>:\tcomando che ti fa usare un oggetto\n");
    printf("ATTACCA <mostro>:\tcomando che ti fa attaccare\n");
    printf("INVENTARIO:\t comando che ti mostra l'inventario\n");
    printf("SALVA:\tcomando che ti fa i dari del gioco\n");
    printf("CARICA:\tcomando che ti carica i dati della partita\n");
    printf("MAPPA:\tcomando che ti mostra la mappa\n");
    printf("HELP:\tcomando che ti mostra i comandi disponibili\n");
}

void esci(Eroe* e){
    char scelta;
    do{
        printf("Vuoi salvare i progressi di gioco prima di uscire(s-n): ");
        scanf("%c", &scelta);
        clear_buffer();
        if(scelta != 's' && scelta != 'n')
            printf("Scelta inserita non valida\n");
    }while(scelta != 's' && scelta != 'n');
    if(scelta == 's')   
    salva_partita(e);
    printf("ARRIVEDERCI, %s\n", e->nome);
    exit(0);
}

void salva_partita(Eroe* e){
    FILE* f = fopen("../saves/partita.sav", "wb");                                                   //apri il file in modalità binaria
    controlla_apertura(f);
    fwrite(e->nome, sizeof(e->nome), 1, f);                                                  //scrivi il nome dell'eroe
    fwrite(&(e->HP), sizeof(e->HP), 1, f);                                                  //scrivi i dati dell'eroe (HP, XP, sheld, danno)
    fwrite(&(e->XP), sizeof(e->XP), 1, f);
    fwrite(&(e->sheld), sizeof(e->sheld), 1, f);
    fwrite(&(e->danno), sizeof(e->danno), 1, f);
    Oggetto* oggetto = e->inventario->next;                                             //crea un oggetto temporaneo per salvare l'inventario
    fwrite(&(e->inventario->len), sizeof(e->inventario->len), 1, f);                        //salva la linghezza dell'inventario
    if(e->inventario->len > 0){
    while(oggetto != NULL){                                                             //salva i dati dell'inventario su file
            fwrite(&(oggetto->tipo), sizeof(oggetto->tipo), 1, f);
            fwrite(&(oggetto->val), sizeof(oggetto->val), 1, f);
            oggetto = oggetto->next;
        }
    }
    Stanza* stanza = e->mappa->inizio;                                                  //crea la stanza temporanea per salvare la mappa
    fwrite(&(e->mappa->numero_stanze), sizeof(e->mappa->numero_stanze), 1, f);              //salva il numero di stanze della mappa (solo quelle allocata)
    while(stanza != NULL){                                                              //salva i dati di tutte le stanze su file
        fwrite(&(stanza->ID), sizeof(stanza->ID), 1, f);
        fwrite(stanza->nome, sizeof(stanza->nome), 1, f);
        fwrite(stanza->nome, sizeof(stanza->nome), 1, f);
        fwrite(&(stanza->numero_nord), sizeof(stanza->numero_nord), 1, f);
        fwrite(&(stanza->numero_est), sizeof(stanza->numero_est), 1, f);
        fwrite(&(stanza->numero_sud), sizeof(stanza->numero_sud), 1, f);
        fwrite(&(stanza->numero_ovest), sizeof(stanza->numero_ovest), 1, f);
        fwrite(&(stanza->oggetto->tipo), sizeof(stanza->oggetto->tipo), 1, f);
        fwrite(&(stanza->oggetto->val), sizeof(stanza->oggetto->val), 1, f);
        fwrite(&(stanza->mostro->tipo), sizeof(stanza->mostro->tipo), 1, f);
        fwrite(&(stanza->mostro->HP), sizeof(stanza->mostro->HP), 1, f);
        fwrite(&(stanza->mostro->XP), sizeof(stanza->mostro->XP), 1, f);
        fwrite(&(stanza->mostro->danno), sizeof(stanza->mostro->danno), 1, f);
        stanza = stanza->next;
    }
    fwrite(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);                //salva l'ID della stanza corrente in cui si trova l'eroe
    fclose(f);
    printf("Dati salvati su file. Il programma può terminare\n");
}

Eroe* carica_partita(){
    Eroe* e = (Eroe*)malloc(sizeof(Eroe));                                              //crea lo spazio per l'eroe
    controlla_allocazione(e);
    FILE* f = fopen("../saves/partita.sav", "rb");
    controlla_apertura(f);
    fread(e->nome, sizeof(e->nome), 1, f);                                               //carica il nome dell'eroe
    fread(&(e->HP), sizeof(e->HP), 1, f);                                               //carica la salute dell'eroe
    fread(&(e->XP), sizeof(e->XP), 1, f);                                               //carica gli XP dell'eroe
    fread(&(e->sheld), sizeof(e->sheld), 1, f);                                         //carica lo scudo
    fread(&(e->danno), sizeof(e->danno), 1, f);                                         //carica il danno minimo
    e->inventario = crea_inventario();                                                  //crea lo spazio per l'inventario
    fread(&(e->inventario->len), sizeof(e->inventario->len), 1, f);                     //leggi quanti elementi ha l'inventario
    if(e->inventario->len > 0){
        Oggetto* coda_oggetti = NULL;                                                               //punta all'ultimo elemento nell'inventario
        for(int i=0; i<e->inventario->len; i++){                                            //per ogni oggetto presente nell'inventario
            Oggetto* oggetto = malloc(sizeof(Oggetto));                                     //crea un oggetto
            controlla_allocazione(oggetto);
            fread(&(oggetto->tipo), sizeof(oggetto->tipo), 1, f);                           //leggi il tipo dell'oggetto
            fread(&(oggetto->val), sizeof(oggetto->val), 1, f);                             //leggi il valore dell'oggetto
            oggetto->next = NULL;                                                           //punta il prossimo a NULL
            if(e->inventario->next == NULL){                                                //se la lista è vuota lo inserisce in testa
                e->inventario->next = oggetto;
                coda_oggetti = oggetto;
            }
            else{                                                                           //altrimenti lo mette in coda
                coda_oggetti->next = oggetto;
                coda_oggetti = oggetto;                                                             //coda deve sempre puntare all'ultimo oggetto
            }
        }
        coda_oggetti->next = NULL;
    }
    e->mappa = crea_mappa();                                                            //crea un mappa
    fread(&(e->mappa->numero_stanze), sizeof(e->mappa->numero_stanze), 1, f);           //leggi il numero delle stanze
    Stanza* coda_stanze = NULL; 
    for(int i=0; i<e->mappa->numero_stanze; i++){                                       //per ogni stanza
        Stanza* stanza = malloc(sizeof(Stanza));                                        //crea la nuova stanza
        controlla_allocazione(stanza);
        fread(&(stanza->ID), sizeof(stanza->ID), 1, f);                                 //leggi l'ID della stanza
        fread(stanza->nome, sizeof(stanza->nome), 1, f);                                //leggi il nome della stanza
        fread(stanza->nome, sizeof(stanza->nome), 1, f);                                //leggi la descrizione della stanza
        fread(&(stanza->numero_nord), sizeof(stanza->numero_nord), 1, f);               //leggi il numero della stanza a nord
        fread(&(stanza->numero_est), sizeof(stanza->numero_est), 1, f);                 //leggi il numero della stanza a est
        fread(&(stanza->numero_sud), sizeof(stanza->numero_sud), 1, f);                 //leggi il numero della stanza a sud
        fread(&(stanza->numero_ovest), sizeof(stanza->numero_ovest), 1, f);             //leggi il numero della stanza a ovest
        Oggetto* oggetto = malloc(sizeof(Oggetto));                                     //crea l'oggetto della stanza
        controlla_allocazione(oggetto);
        fread(&(oggetto->tipo), sizeof(oggetto->tipo), 1, f);                           //leggi il tipo dell'oggetto della stanza
        fread(&(oggetto->val), sizeof(oggetto->val), 1, f);                             //leggi il valore dell'oggetto della stanza
        stanza->oggetto = oggetto;                                                      //collega l'oggetto alla stanza
        Mostro* mostro = malloc(sizeof(Mostro));                                        //crea il mostro della stanza
        controlla_allocazione(mostro);
        fread(&(mostro->tipo), sizeof(mostro->tipo), 1, f);                             //leggi il tipo del mostro
        fread(&(mostro->HP), sizeof(mostro->HP), 1, f);                                 //leggi la salute del mostro
        fread(&(mostro->XP), sizeof(mostro->XP), 1, f);                                 //leggi gli XP assegnati al mostro
        fread(&(mostro->danno), sizeof(mostro->danno), 1, f);                           //leggi il danno minimo del mostro
        stanza->mostro = mostro;                                                        //collega il mostro alla stanza
        if(e->mappa->inizio == NULL){                                                   //se la mappa è vuota lo inserisce in testa
            e->mappa->inizio = stanza;
            coda_stanze = stanza;
        }
        else{                                                                           //altrimenti lo mette in coda
            coda_stanze->next = stanza;
            coda_stanze = stanza;                                                              //coda deve sempre puntare all'ultima stanza
        }
    }
    coda_stanze->next = NULL;
    e->stanza_corrente = (Stanza*)malloc(sizeof(Stanza));
    controlla_allocazione(e->stanza_corrente);
    fread(&(e->stanza_corrente->ID), sizeof(e->stanza_corrente->ID), 1, f);
    Stanza* current = e->mappa->inizio;
    while(current->ID != e->stanza_corrente->ID)                                        //assegna la stanza corrente dell'eroe in base al suo ID
        current = current->next;
    e->stanza_corrente = current;
    fclose(f);
    return e;
}

Bool esegui_comando(Eroe* e, TipoComando cmd, char* argomento){
    Bool esito = false;
    switch(cmd){
        case VAI:
            cambia_stanza(e, argomento);
            break;
        case GUARDA:
            descrivi_stanza(e->stanza_corrente);
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
            stampa_mappa_ascii(e, e->mappa->numero_stanze);
            break;
        case HELP:
            help();
            break;
        case ESCI:
            esci(e);
            break;
        case INVALIDO:
            printf("Comando non valido. Digita help per vedere i comandi disponibili\n");
            break;
    }
    return esito;
}

Eroe* inizio_gioco(){
    Eroe* e = NULL;
    char carica;
    do{
        printf("Vuoi caricare una partita salvata? (s/n): ");
        scanf("%c", &carica);
        clear_buffer();
        if(carica != 's' && carica != 'n'){
            printf("Comando non valido. Digita s o n\n");
        }
    } while(carica != 's' && carica != 'n');
    if(carica == 's'){
        e = carica_partita();
        printf("Partita caricata da file\n");
    }
    else{
        e = crea_eroe();
        printf("Partita creata nuova\n");
        system("CLS");
    }
    printf("================================\n");
    printf("||        DUNGEON C           ||\n");
    printf("||   GIOCO NEL DUNGEON IN C   ||\n");
    printf("================================\n");
    printf("Fiato corto. Vista annebbiata. Un vuoto pneumatico dove dovrebbero esserci i tuoi ricordi. Non sai chi sei. Ma sai dove sei: nell'abisso.\n");
    printf("Una luce spettrale illumina una lettera che giace sul pavimento umido.\nLa raccogli, mentre una consapevolezza gelida ti scivola lungo la schiena leggendo quelle poche, brutali righe: ");
    printf("Sei morto. Questo e' il tuo purgatorio di pietra. \nEsci vivo da questo Dungeon, o la tua storia finirà qui, nel buio, dove nessuno ricordera' il tuo nome.\n");
    system("PAUSE");
    system("CLS");
    help();
    return e;
}

void fine_gioco(Eroe* e){
    system("CLS");
    if(e->HP <= 0){
        printf("====================================\n");
        printf("||           GAME OVER            ||\n");
        printf("|| RITENTA, E FAI SCELTE MIGLIORI ||\n");
        printf("====================================\n");
    }
    else{
        printf("========================\n");
        printf("||      HAI VINTO     ||\n");
        printf("|| Hai ottenuto %dXP  ||\n", e->XP);
        printf("========================\n");
    }
    elimina_eroe(e);
}