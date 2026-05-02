/*libreria di funzioni notevoli del gioco*/
#ifndef UTILITIES_H
#define UTILITIES_H
#include "./tipi.h"
/**
 * Funzione che controlla l'esito dell'allocazione di uno spazio di memoria. In caso sia fallito esce dal programma
 * @param void* puntatore da controllare
*/
void controlla_allocazione(void* ptr);

/**
 * Funzione che divide l'input dell'utente in 2 sottostringhe, la prima contentente il comando principale e la seconda l+eventuale argomento
 * @param char* input preso dall'utente
 * @return char** doppio puntatore all'output (il primo contiene il comando, il secondo l'argomento)
*/
char** dividi_input(char* input);

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
 * Funzione che esegue un comando impartito dall'utente
 * @param Eroe* eroe che vuole eseguire il comando
 * @param TipoComando tipologia del comando da eseguire
 * @param char* stringa argomento del comando
*/
void esegui_comando(Eroe* e, TipoComando cmd, char* argomento);

#endif