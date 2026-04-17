/*Libreria per la gestione della mappa del gioco*/
#include "tipi.h"

/**
 * Funzione che popola una lista di oggetti in modo casuale, che andranno a popolare le stanze
 * @param ListaOggetti* lista degli oggetti da popolare
*/
void riempi_lista_oggetti(ListaOggetti* l);

/**
 * Funzione che crea una lista di oggetti che popolano le stanze
 * @return puntatore alla lista di oggetti
*/
ListaOggetti* crea_lista_oggetti();

/**
 * Funzione che crea una lista di mostri che popolano le stanze
 * @return puntatore alla lista
*/
ListaMostri* crea_lista_mostri();

/**
 * Funzione che crea la mappa del gioco
 * @return puntatore alla mappa del gioco
*/
Mappa* crea_mappa();

/**
 * Funzione che crea una stanza nella direzione di provenienza dell'eroe
 * @param Mappa* mappa dove creare la stanza
 * @param Stanza* provenienza stanza di provenienza dell'eroe
 * @param char* direzione di provenienza del giocatore
 * @return Stanza* puntatore alla stanza appena creata
*/
Stanza* crea_stanza(Mappa* p, Stanza* provenienza, char* direzione);