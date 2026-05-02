#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"
#include "../include/combattimento.h"

int attacco_mostro(Mostro* m){
    int danno = (rand() % m->danno) + 1;
    return danno;
}

int attacco_eroe(Eroe* e){
    int danno = (rand() % e->danno) + 1;
    return danno;
}

TipoMostro tipo_mostro(char* input){
    if(strcmp(input, "scheletro") == 0)         return POZIONE;
    else if(strcmp(input, "goblin") == 0)       return ARMA;
    else if(strcmp(input, "drago") == 0)        return ARMATURA;
    else if(strcmp(input, "boss") == 0)         return CHIAVE;
    else                                        return NO_MOSTRO;
}

Bool combattimento(Eroe* e, char* argomento){
    int danno_mostro, danno_eroe, turni=1;
    TipoMostro tipo = tipo_mostro(argomento);
    if(e->stanza_corrente->mostro->tipo == tipo){
        Mostro* m = e->stanza_corrente->mostro;
        printf("===========COMBATTIMENTO INIZIATO============\n");
        while(e->HP > 0 && m->HP > 0){              //ciclo loop, finchè una delle due vite è maggiore di 0
            printf("=====TURNO NUMERO %d=====\n", turni);
            danno_mostro = attacco_mostro(m);
            danno_eroe = attacco_eroe(e);
            if(e->sheld - danno_mostro >= 0)
                e->sheld -= danno_mostro;
            else if(e->sheld - danno_mostro < 0 && e->sheld > 0){   //caso in cui il danno risulta maggiore dello scudo dell'eroe
                e->HP = e->HP - (danno_mostro - e->sheld);
                e->sheld = 0;
            }
            else
                e->HP -= danno_mostro;
            m->HP -= danno_eroe;
            printf("Hai fatto %d danni al mostro, ma il mostro ti ha tolto %d punti vita.", danno_eroe, danno_mostro);
            printf("Ti sono rimasti %d HP e %d punti dello scudo", e->HP, e->sheld);
            turni++;
            system("PAUSE");
            if(e->HP <= 0){
                printf("Sei stato sconfitto\n");
                return false;
            }
            else if(m->HP <= 0){
                printf("Hai sconfitto il mostro.\nHai guadagnato %d punti XP\n", m->XP);
                e->XP += m->XP;
                e->stanza_corrente->tipo_mostro = NO_MOSTRO;
                free(e->stanza_corrente->mostro);
                e->stanza_corrente->mostro = NULL;
                return true;
            }
        }
    }
    else{
        printf("Mostro non presente all'interno della stanza\n");
    }
    return false;
}