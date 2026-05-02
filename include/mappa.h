/*Libreria per la gestione della mappa del gioco*/
#ifndef MAPPA_H
#define MAPPA_H
#include "tipi.h"

/**
 * Funzione che controlla se è presente una stanza nell'array stanze
 * @param Stanza* vettore delle stanze caricate
 * @param int numero della stanza da trovare
 * @return Bool true se la trova
*/
Bool trova_stanza(Mappa* p, int numero_stanza);

/**
 * Funzione che carica la stanza dal file della mappa
 * @param int numero della stanza da caricare
 * @return stanza caricata nel formato stanza_salvataggio
*/
StanzaSalvataggio* carica_stanza(int numero_stanza);

/**
 * Funzione che converte una stanza caricata dal file .map in una stanza nella memoria del gioco
 * @param StanzaSalvataggio* stanza da convertire
 * @return Stanza* puntatore alla nuova stanza allocata
*/
Stanza* converti_stanza(StanzaSalvataggio* s_s);

/**
 * Funzione che crea una mappa nel gioco e la collega all'eroe
 * @return Mappa* mappa allocata dal giocatore
*/
Mappa* crea_mappa();

/**
 * Funzione che crea un oggetto
 * @param TipoOggetto* tipo dell'oggetto da creare
 * @param int valore dell'oggetto presente nella stanza
 * @return Oggetto* puntatore all'oggetto creato
*/
Oggetto* crea_oggetto(TipoOggetto o, int val);

/**
 * Funzione che crea un mostro
 * @param TipoMostro* tipo del mostro da creare
 * @return Mostro* puntatore al mostro creato
*/
Mostro* crea_mostro(TipoMostro m);
/**
 * Funzione che crea una stanza nella direzione di provenienza dell'eroe
 * @param Stanza* provenienza stanza di provenienza dell'eroe
 * @param char* direzione di provenienza del giocatore
 * @return Stanza* puntatore alla stanza appena creata;
*/
Stanza* crea_stanza(Stanza* provenienza, char* direzione);

/**
 * Funzione che elimina una mappa
 * @param Mappa* mappa da eliminare
*/
void elimina_mappa(Mappa* p);

#endif