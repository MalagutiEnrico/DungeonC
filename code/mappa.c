#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/tipi.h"
#include "../include/mappa.h"
#include "../include/utilities.h"

Bool trova_stanza(Mappa* stanze, int numero_stanza){
    if(numero_stanza == -1)                                     //stanza non presente
        return false;
    Stanza* current = stanze->inizio;
    while(current != NULL){                                     //scorri ogni stanza della lista
        if(current->ID == numero_stanza){                       //se la trova ritorna a true
            return true;
        }
        current = current->next;
    }
    return false;
}

int indice_stanza(Stanza** stanze, int count, int id){
    int i;
    for(i = 0; i < count; i++){
        if(stanze[i]->ID == id){
            return i;
        }
    }
    return -1;
}

StanzaSalvataggio* carica_stanza(int numero_stanza){
    FILE* f = fopen("../convertitore/mappa.map", "rb");
    controlla_apertura(f);
    StanzaSalvataggio* s = (StanzaSalvataggio*)malloc(sizeof(StanzaSalvataggio)); //crea lo spazio di memoria per la stanza da leggere dal file
    controlla_allocazione(s);
    long offset = (numero_stanza - 1) * sizeof(StanzaSalvataggio);    //sizeof dettato dal numero delle stanze le stanze effettive
    if(fseek(f, offset, SEEK_SET) != 0){                                          //sposta il cursore nella posizione dettata dall'offset
        fclose(f);                                                                //in caso non vada a buon fine chiudi i file e ritorna a NULL
        free(s);
        return NULL;
    }
    fread(s, sizeof(StanzaSalvataggio), 1, f);
    return s;
}

Stanza* converti_stanza(StanzaSalvataggio* s_s){
    Stanza* s = (Stanza*)malloc(sizeof(Stanza));        //alloca lo spazio per una stanza
    controlla_allocazione(s);
    s->ID = s_s->ID;                                    //copia i valori della stanza dal salvataggio in quella gestibile nel gioco
    strcpy(s->nome, s_s->nome);
    strcpy(s->desc, s_s->desc);
    s->numero_nord = s_s->nord;
    s->numero_est = s_s->est;
    s->numero_sud = s_s->sud;
    s->numero_ovest = s_s->ovest;
    s->oggetto = crea_oggetto(s_s->tipo_oggetto, s_s->valore_oggetto);      //crea l'oggetto del tipo e con il valore specificati dal file
    s->mostro = crea_mostro(s_s->tipo_mostro);                              //crea il mostro con il tipo specificato dal file
    return s;
}

Mappa* crea_mappa(){
    Mappa* m = (Mappa*)malloc(sizeof(Mappa));
    controlla_allocazione(m);
    m->inizio = NULL;
    m->numero_stanze = 0;
    return m;
}

Oggetto* crea_oggetto(TipoOggetto o, int val){
    Oggetto* ogg = (Oggetto*)malloc(sizeof(Oggetto));
    controlla_allocazione(ogg);
    ogg->tipo = o;
    ogg->val = val;
    return ogg;
}

Mostro* crea_mostro(TipoMostro m){
    Mostro* mostro = (Mostro*)malloc(sizeof(Mostro));
    controlla_allocazione(mostro);
    mostro->tipo = m;
    switch(m){                                          //in base al tipo di mostro, avrà delle statistiche diverse
        case SCHELETRO:
            mostro->HP = 10;
            mostro->danno = 5;
            mostro->XP = 10;
            break;
        case GOBLIN:
            mostro->HP = 15;
            mostro->danno = 10;
            mostro->XP = 15;
            break;
        case DRAGO:
            mostro->HP = 40;
            mostro->danno = 20;
            mostro->XP = 50;
            break;
        case BOSS:
            mostro->HP = 80;
            mostro->danno = 35;
            mostro->XP = 100;
            break;
        case NO_MOSTRO:
            mostro->HP = 0;
            mostro->danno = 0;
            mostro->XP = 0;
            break;
        default:
            return NULL;
    }
    return mostro;
}

Stanza* crea_stanza(Stanza* provenienza, char* direzione){
    StanzaSalvataggio* s_s = NULL;
    Stanza* s = NULL;
    if(!strcmp(direzione, "nord")){                             //in base alla direzione collega le stanza                                          //la stanza esiste
        s_s = carica_stanza(provenienza->numero_nord);          //carica la struttura da file
        s = converti_stanza(s_s);                               //la converte in una stanza del gioco
        provenienza->nord = s;                                  //imposta i collegamenti con la stanza di provenienza
        s->sud = provenienza;
    }
    else if(!strcmp(direzione, "est")){
        s_s = carica_stanza(provenienza->numero_est);
        s = converti_stanza(s_s);
        provenienza->est = s;
        s->ovest = provenienza;
    }
    else if(!strcmp(direzione, "sud")){
        s_s = carica_stanza(provenienza->numero_sud);
        s = converti_stanza(s_s);
        provenienza->sud = s;
        s->nord = provenienza;
    }
    else if(!strcmp(direzione, "ovest")){
        s_s = carica_stanza(provenienza->numero_ovest);
        s = converti_stanza(s_s);
        provenienza->ovest = s;
        s->est = provenienza;
    }
    s->oggetto = crea_oggetto(s_s->tipo_oggetto, s_s->valore_oggetto);                  //crea l'oggetto di tipo specificato dal file
    s->mostro = crea_mostro(s_s->tipo_mostro);                                          //crea il mostro ti tipo specificato dal file
    free(s_s);                                                                          //libera la memoria della stanza del salvataggio
    s->next = NULL;                                                                     //punta a NULL così diventa l'ultima stanza a essere caricata
    return s;
}

void descrivi_stanza(Stanza* s){
printf("%s\n", s->desc);                                                                                //stampa la descrizione della stanza
    switch(s->oggetto->tipo){                                                                           //per ogni oggetto, scrivi una breve descrizione
        case NO_OGGETTO:
            printf("La stanza non contiene oggetti\n");
            break;
        case POZIONE:
            printf("La stanza contiene una pozione, Se sei ferito potrebbe aiutarti a curarti\n");
            break;
        case ARMA:
            printf("La stanza contiene un'arma, potrebbe aiutarti a sconfiggere i mostri\n");
            break;
        case ARMATURA:   
            printf("La stanza contiene un'armatura, potrebbe aiutarti a difenderti dai mostri\n");
            break;
        case CHIAVE:
            printf("La stanza contiene una chiave, potrebbe aiutarti a sbloccare una porta chiusa\n");
            break;
        case TORCIA:
            printf("La stanza contiene una torcia, potrebbe aiutarti a vedere al buio\n");
            break;  
    }
    switch(s->mostro->tipo){                                                                            //per ogni mostro scrivi una breve descrizione
        case NO_MOSTRO:
            printf("La stanza non contiene mostri\n");
            break;
        case SCHELETRO:
            printf("La stanza contiene uno scheletro, potrebbe darti fastidio, ma non è molto pericoloso\n");
            break;
        case GOBLIN:
            printf("La stanza contiene un goblin, non è molto agressivo ma potrebbe toglierti qualche punto vita, stai attento\n");
            break;
        case DRAGO:   
            printf("La stanza contiene un drago, è molto pericoloso, se non sei abbastanza forte può ucciderti in pochi colpi, stai molto attento\n");
            break;
        case BOSS:
            printf("La stanza contiene IL BOSS DICARA, è estremamente pericoloso, se non sei abbastanza forte potrebbe codificarti e ucciderti in un colpo solo\n");
            break;
    } 
}

void stampa_mappa_ascii(Eroe* e, int numero_stanze){
    const int passo_colonna = 6;
    const int passo_riga = 2;
    const int max_righe = 45;
    const int max_colonne = 140;
    int count, i, j;
    int head = 0;
    int tail = 0;
    int min_x, max_x, min_y, max_y;
    int righe, colonne;
    Bool layout_conflitto = false;
    Stanza* current;
    Stanza** stanze;
    int* x;
    int* y;
    Bool* assegnata;
    int* queue;
    char** griglia;

    if(e == NULL || e->mappa == NULL || e->mappa->inizio == NULL || e->stanza_corrente == NULL){
        printf("Mappa non disponibile\n");
        return;
    }

    count = numero_stanze;
    if(count <= 0){
        printf("Nessuna stanza esplorata\n");
        return;
    }

    stanze = (Stanza**)malloc(sizeof(Stanza*) * count);
    x = (int*)malloc(sizeof(int) * count);
    y = (int*)malloc(sizeof(int) * count);
    assegnata = (Bool*)malloc(sizeof(Bool) * count);
    queue = (int*)malloc(sizeof(int) * count);
    controlla_allocazione(stanze);
    controlla_allocazione(x);
    controlla_allocazione(y);
    controlla_allocazione(assegnata);
    controlla_allocazione(queue);

    current = e->mappa->inizio;
    i = 0;
    while(current != NULL && i < count){
        stanze[i] = current;
        x[i] = 0;
        y[i] = 0;
        assegnata[i] = false;
        current = current->next;
        i++;
    }
    count = i;
    if(count <= 0){
        printf("Nessuna stanza esplorata\n");
        free(stanze);
        free(x);
        free(y);
        free(assegnata);
        free(queue);
        return;
    }

    i = indice_stanza(stanze, count, e->stanza_corrente->ID);
    if(i < 0){
        i = 0;
    }
    assegnata[i] = true;
    queue[tail++] = i;

    while(head < tail){
        int idx = queue[head++];
        int vicino_idx;
        Stanza* stanza = stanze[idx];

        if(stanza->numero_nord > 0){
            vicino_idx = indice_stanza(stanze, count, stanza->numero_nord);
            if(vicino_idx >= 0){
                if(!assegnata[vicino_idx]){
                    x[vicino_idx] = x[idx];
                    y[vicino_idx] = y[idx] - 1;
                    assegnata[vicino_idx] = true;
                    queue[tail++] = vicino_idx;
                }
                else if(x[vicino_idx] != x[idx] || y[vicino_idx] != y[idx] - 1){
                    layout_conflitto = true;
                }
            }
        }
        if(stanza->numero_est > 0){
            vicino_idx = indice_stanza(stanze, count, stanza->numero_est);
            if(vicino_idx >= 0){
                if(!assegnata[vicino_idx]){
                    x[vicino_idx] = x[idx] + 1;
                    y[vicino_idx] = y[idx];
                    assegnata[vicino_idx] = true;
                    queue[tail++] = vicino_idx;
                }
                else if(x[vicino_idx] != x[idx] + 1 || y[vicino_idx] != y[idx]){
                    layout_conflitto = true;
                }
            }
        }
        if(stanza->numero_sud > 0){
            vicino_idx = indice_stanza(stanze, count, stanza->numero_sud);
            if(vicino_idx >= 0){
                if(!assegnata[vicino_idx]){
                    x[vicino_idx] = x[idx];
                    y[vicino_idx] = y[idx] + 1;
                    assegnata[vicino_idx] = true;
                    queue[tail++] = vicino_idx;
                }
                else if(x[vicino_idx] != x[idx] || y[vicino_idx] != y[idx] + 1){
                    layout_conflitto = true;
                }
            }
        }
        if(stanza->numero_ovest > 0){
            vicino_idx = indice_stanza(stanze, count, stanza->numero_ovest);
            if(vicino_idx >= 0){
                if(!assegnata[vicino_idx]){
                    x[vicino_idx] = x[idx] - 1;
                    y[vicino_idx] = y[idx];
                    assegnata[vicino_idx] = true;
                    queue[tail++] = vicino_idx;
                }
                else if(x[vicino_idx] != x[idx] - 1 || y[vicino_idx] != y[idx]){
                    layout_conflitto = true;
                }
            }
        }
    }

    {
        int cursor_x = 0;
        int cursor_y = 2;
        for(i = 0; i < count; i++){
            if(!assegnata[i]){
                x[i] = cursor_x++;
                y[i] = cursor_y;
                assegnata[i] = true;
                layout_conflitto = true;
            }
        }
    }

    min_x = max_x = x[0];
    min_y = max_y = y[0];
    for(i = 1; i < count; i++){
        if(x[i] < min_x) min_x = x[i];
        if(x[i] > max_x) max_x = x[i];
        if(y[i] < min_y) min_y = y[i];
        if(y[i] > max_y) max_y = y[i];
    }

    righe = (max_y - min_y) * passo_riga + 1;
    colonne = (max_x - min_x) * passo_colonna + 5;

    griglia = (char**)malloc(sizeof(char*) * righe);
    controlla_allocazione(griglia);
    for(i = 0; i < righe; i++){
        griglia[i] = (char*)malloc(sizeof(char) * (colonne + 1));
        controlla_allocazione(griglia[i]);
        for(j = 0; j < colonne; j++){
            griglia[i][j] = ' ';
        }
        griglia[i][colonne] = '\0';
    }

    for(i = 0; i < count; i++){
        int r = (y[i] - min_y) * passo_riga;
        int c = (x[i] - min_x) * passo_colonna;
        char label[8];

        if(stanze[i]->ID == e->stanza_corrente->ID){
            strcpy(label, "[* ]");
        }
        else{
            snprintf(label, sizeof(label), "[%02d]", stanze[i]->ID);
        }

        for(j = 0; j < 4; j++){
            griglia[r][c + j] = label[j];
        }
    }

    for(i = 0; i < count; i++){
        int idx_vicino;
        int r1 = (y[i] - min_y) * passo_riga;
        int c1 = (x[i] - min_x) * passo_colonna;

        if(stanze[i]->numero_est > 0){
            idx_vicino = indice_stanza(stanze, count, stanze[i]->numero_est);
            if(idx_vicino >= 0){
                int r2 = (y[idx_vicino] - min_y) * passo_riga;
                int c2 = (x[idx_vicino] - min_x) * passo_colonna;
                if(r1 == r2 && abs(c1 - c2) == passo_colonna){
                    int from = (c1 < c2) ? c1 + 4 : c2 + 4;
                    int to = (c1 < c2) ? c2 - 1 : c1 - 1;
                    for(j = from; j <= to; j++){
                        griglia[r1][j] = '-';
                    }
                }
            }
        }
        if(stanze[i]->numero_sud > 0){
            idx_vicino = indice_stanza(stanze, count, stanze[i]->numero_sud);
            if(idx_vicino >= 0){
                int r2 = (y[idx_vicino] - min_y) * passo_riga;
                int c2 = (x[idx_vicino] - min_x) * passo_colonna;
                if(c1 == c2 && abs(r1 - r2) == passo_riga){
                    int rr = (r1 < r2) ? r1 + 1 : r2 + 1;
                    griglia[rr][c1 + 2] = '|';
                }
            }
        }
    }

    printf("Mappa esplorata:\n");
    for(i = 0; i < righe; i++){
        printf("%s\n", griglia[i]);
        free(griglia[i]);
    }
    free(griglia);
    if(layout_conflitto){
        printf("Nota: layout approssimato per collegamenti non planari.\n");
    }
    printf("Legenda: [* ] = posizione giocatore, [nn] = stanza esplorata\n");

    free(stanze);
    free(x);
    free(y);
    free(assegnata);
    free(queue);
}

void elimina_mappa(Mappa* p){
    Stanza* s = p->inizio;
    while(s != NULL){
        Stanza* tmp = s;
        s = s->next;
        free(tmp->oggetto);                                     //libera la memoria della lista di oggetti 
        free(tmp->mostro);                                      //libera la memoria della lista di mostri                                       //libera la memoria del puntatore alla stanza ovest
        free(tmp);
    }
    free(p);
}