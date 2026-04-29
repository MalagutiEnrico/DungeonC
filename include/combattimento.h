/*Libreria per la gestione del combattimento nel gioco*/
#ifndef COMBATTIMENTO_H
#define COMBATTIMENTO_H
include "tipi.h"
#include "eroe.h"
#include "mostro.h"

/**
 * Funzione che calcola l'attacco di un mostro
 * @param Mostro* mostro che deve attaccare
 * @return danno del mostro
*/
int attacco_mostro(Mostro* m);

/**
 * Funzione che calcola l'attacco di un mostro
 * @param Eroe* eroe che deve attaccare
 * @return danno dell'eroe
*/
int attacco_eroe(Eroe* e);

/**
 * Funzione che svolge un attacco
 * @param Eroe* eroe che vuole attaccare
 * @param Mostro* mostro da attaccare
 * @return Bool true se l'eroe vince, altrimenti false se perde
*/
Bool combattimento(Eroe* e, Mostro* m);

#endif