/*Libreria per la gestione dell'eroe nel gioco*/
#include "tipi.h"

/**
 * Funzione che crea un inventario di oggetti
 * @return Inventario* puntatore all'inventario
*/
Inventario* crea_inventario();

/**
 * Funzione che stampa lo stato dell'inventario dell'eroe
 * @param Inventario* inventario da stampare
*/
void stampa_inventario(Inventario* i);

/**
 * Funzione che crea un eroe
 * @return Eroe* puntatore all'eroe
*/
Eroe* crea_eroe();

/**
 * Funzione che stampa a video lo stato dell'eroe
 * @param Eroe* eroe di cui stampare lo stato
*/
void stampa_stato(Eroe* e);

/**
 * Funzione che permette ad un eroe di cambiare una stanza
 * @param Eroe* e eroe del gioco che desidera cambiare stanza
 * @param char* direzione che l'eroe vuole intraprendere
 * 
*/
void cambia_stanza(Eroe* e, char* direzione);

/**
 * Funzione che ritorna al tipo di oggetto in base all'input dell'utente
 * @param char* input dell'utente
 * @return TipoOggetto tipo dell'oggetto selezionato
*/
TipoOggetto tipo_oggetto(char input);

/**
 * Funzione che aggiunge un oggetto all'inventario dell'utente
 * @param Eroe* a cui aggiungere l'oggetto
 * @param TipoOggetto tipo dell'oggetto da aggiungere
*/
void prendi_oggetto(Eroe* e, TipoOggetto tipo);