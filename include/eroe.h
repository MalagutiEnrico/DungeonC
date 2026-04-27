/*Libreria per la gestione dell'eroe nel gioco*/
#ifndef EROE_H
#define EROE_H
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
TipoOggetto tipo_oggetto(char* input);

/**
 * Funzione che aggiunge un oggetto all'inventario dell'utente
 * @param Eroe* a cui aggiungere l'oggetto
 * @param TipoOggetto tipo dell'oggetto da aggiungere
*/
void prendi_oggetto(Eroe* e, TipoOggetto tipo);

/**
 * Funzione che controlla se è presente un oggetto nell'inventario dell'eroe
 * @param Eroe* eroe in cui controllare l'oggetto
 * @param TipoOggetto tipo dell'oggetto da controllare
 * @return true se lo trova
*/
Bool trova_oggetto(Eroe* e, TipoOggetto o);

/**
 * Funzione che elimina un oggetto dall'inventario
 * @param Inventario* inventario da cui eliminare l'oggetto
 * @param Oggetto* oggetto da eliminare
*/
void elimina_oggetto(Inventario* i, Oggetto* o);

/**
 * Funzione che permette all'eroe di usare un oggetto
 * @param Eroe* eroe che vuole utilizzare l'oggetto
 * @param Oggetto* oggetto da utilizzare
 * 
*/
void usa_oggetto(Eroe* e, Oggetto* o);

/**
 * Funzione che utilizza una pozione per curare l'eroe
 * @param Eroe* eroe da curare
 * @param int valore curativo della pozione
*/
void usa_pozione(Eroe* e, int val);

/**
 * Funzione che usa un'arma per incrementare i danni minimi dell'eroe
 * @param Eroe* eroe da incrementare
 * @param int valore curativo della pozione
*/
void usa_arma(Eroe* e, int val);

/**
 * Funzione che usa un'arma per incrementare i danni minimi dell'eroe
 * @param Eroe* eroe da incrementare
 * @param int valore curativo della pozione
*/
void usa_armatura(Eroe* e, int val);

/**
 * Funzione che controlla se è possibile aprire una porta con la chiave
 * @param Eroe* eroe che vuole aprire la porta
 * @param val valore della chiave (codice della porta da aprire, ma in negativo (es. porta da aprire numero 7; codice chiave = -7))
 * @return true se la chiave ha aperto la stanza; false il contrario
*/
Bool usa_chiave(Eroe* e, int val);

/**
 * Funzione che usa una torcia per descrivere la stanza
 * @param Eroe* eroe che deve visualizzare la stanza
*/
void usa_torcia(Eroe* e);

#endif