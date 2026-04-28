/*libreria di funzioni notevoli del gioco*/
#ifndef UTILITIES_H
#define UTILITIES_H

/**
 * Funzione che salva la partita
 * @param Eroe* eroe da salvare nel file 
 */
void salva_partita(Eroe* e);

/**
 * Funzione che carica la partita 
 * @param Eroe* eroe da caricare in partita
 */
void carica_partita(Eroe* e);

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