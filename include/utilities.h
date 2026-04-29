/*libreria di funzioni notevoli del gioco*/
#ifndef UTILITIES_H
#define UTILITIES_H
#include "./tipi.h"

/**
 * Funzione che salva la partita
 * @param Eroe* eroe da salvare nel file partita.sav
 */
void salva_partita(Eroe* e);

/**
 * Funzione che carica la partita 
 * @return Eroe* eroe caricato dal file
 */
Eroe* carica_partita();

/**
 * Funzione che controlla l'esito dell'allocazione di uno spazio di memoria. In caso sia fallito esce dal programma
 * @param void* puntatore da controllare
*/
void controlla_allocazione(void* ptr);

/**
 * Funzione che prende l'input inserito dall'utente e lo converte in un comando
 * @param char* stringa del comando dell'utente
 * @return TipoComando tipo del comando inserito dall'utente
*/
TipoComando parse(char* input);

/**
 * Funzione che stampa la lista dei comandi disponibili
*/
void help();

#endif