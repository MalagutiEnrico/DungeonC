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
 * Funzione che controlla se è presente una stanza nell'array stanze
 * @param int* vettore delle stanze caricate
 * @param int dimensione dell'array
 * @param int numero della stanza da trovare
 * @return Bool true se la trova
*/
Bool trova_stanza(int* stanze, int stanze_visitate, int numero_stanza);

/**
 * Funzione che carica la stanza dal file della mappa
 * @param int numero della stanza da caricare
 * @return stanza caricata
*/
StanzaSalvataggio* carica_stanza(int numero_stanza);

/**
 * Funzione che crea una stanza nella direzione di provenienza dell'eroe
 * @param Stanza* provenienza stanza di provenienza dell'eroe
 * @param char* direzione di provenienza del giocatore
 * @return Stanza* puntatore alla stanza appena creata
*/
Stanza* crea_stanza(Stanza* provenienza, char* direzione);