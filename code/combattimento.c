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
    if(strcmp(input, "scheletro") == 0)         return SCHELETRO;
    else if(strcmp(input, "goblin") == 0)       return GOBLIN;
    else if(strcmp(input, "drago") == 0)        return DRAGO;
    else if(strcmp(input, "boss") == 0)         return BOSS;
    else                                        return NO_MOSTRO;
}

Bool combattimento(Eroe* e, char* argomento){
    int danno_mostro, danno_eroe, turni=1;
    TipoMostro tipo = tipo_mostro(argomento);
    if(e->stanza_corrente->mostro->tipo == tipo){                   //se il tipo del mostro nella stanza è corrispondente all'input
        Mostro* m = e->stanza_corrente->mostro;
        printf("===========COMBATTIMENTO INIZIATO============\n");
        while(e->HP > 0 && m->HP > 0){                              //ciclo loop, finchè una delle due vite è maggiore di 0
            printf("=====TURNO NUMERO %d=====\n", turni);
            danno_mostro = attacco_mostro(m);                       //calcola i danni del turno
            danno_eroe = attacco_eroe(e);
            if(e->shield - danno_mostro >= 0)                        //se l'eroe ha dello scudo sottrai i danni del mostro dallo scudo
                e->shield -= danno_mostro;
            else if(e->shield - danno_mostro < 0 && e->shield > 0){   //caso in cui il danno risulta maggiore dello scudo dell'eroe
                e->HP = e->HP - (danno_mostro - e->shield);
                e->shield = 0;
            }
            else                                                    //caso in cui lo scudo sia uguale a zero toglie i danni dalla salute dell'eroe
                e->HP -= danno_mostro;
            m->HP -= danno_eroe;
            if(e->HP <= 0)                                          //se l'eroe ha finito la vita termina il gioco
                return true;
            else if(m->HP <= 0){                                    //se il mostro ha finito la vita
                e->XP += m->XP;                                     //aggiungi all'eroe gli XP del mostro
                if(m->tipo == BOSS)                                 //se il mostro era il BOSS fai terminare il gioco
                    return true;
                printf("Hai sconfitto il mostro.\nHai guadagnato %d punti XP\n", m->XP);
                e->stanza_corrente->mostro->tipo = NO_MOSTRO;       //imposta il tipo di mostro a NO_MOSTRO nella stanza corrente dell'eroe
                return false;
            }
            printf("Hai fatto %d danni al mostro, ma il mostro ti ha tolto %d punti vita.\n", danno_eroe, danno_mostro);
            printf("Ti sono rimasti %d HP e %d punti dello scudo\n", e->HP, e->shield);
            printf("Al mostro sono rimasti %d punti vita\n", m->HP);
            turni++;
            system("PAUSE");
        }
    }
    else{
        printf("Mostro non presente all'interno della stanza\n");
    }
    return false;
}