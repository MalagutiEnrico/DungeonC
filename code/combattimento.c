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

Bool combattimento(Eroe* e, Mostro* m){
    int danno_mostro, danno_eroe, turni=1;
    printf("===========COMBATTIMENTO INIZIATO============\n");
    while(e->HP > 0 || m->HP > 0){              //ciclo loop, finchè una delle due vite è maggiore di 0
        printf("=====TURNO NUMERO %d=====\n", turni);
        if(e->sheld - danno_mostro >= 0)
            e->sheld -= danno_mostro;
        else if(e->sheld - danno_mostro < 0){   //caso in cui il danno risulta maggiore dello scudo dell'eroe
            e->HP = e->HP - (danno_mostro + e->sheld);
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
            return true;
        }
    }
}