/*Libreria contenente la definizione dei tipi e delle costanti del gioco*/
#ifndef TIPI_H
#define TIPI_H

#define MAX_INVENTARIO 8        //numero di oggetti massimi nell'inventario
#define MAX_DIMINPUT 100        //numero massimo di caratteri inseribili in fase di input
#define MAX_SALUTE 100          //valore massimo di salute dell'eroe
#define MAX_OGGETTI 5           //numero massimo di oggetti in una stanza

//Definizione delle variabili booleane
typedef enum{
    false,
    true,
}Bool;

//Definizione dei tipi di oggetto presenti nelle stanze e nell'inventario
typedef enum{
    NO_OGGETTO,
    POZIONE,
    ARMA,
    ARMATURA, 
    CHIAVE,
    TORCIA
}TipoOggetto;

//Definizione dei tipi di mostro incontrabili nel gioco
typedef enum{
    NO_MOSTRO,
    SCHELETRO,
    GOBLIN,
    DRAGO,
    BOSS
}TipoMostro;

//Definizione dei tipi di comando inseribili nel gioco
typedef enum{
    VAI,
    GUARDA,
    PRENDI,
    USA,
    ATTACCA,
    INVENTARIO,
    SALVA,
    CARICA,
    MAPPA,
    HELP,
    INVALIDO
}TipoComando;

//Definizione della struct oggetto come nodo
typedef struct Oggetto{
    TipoOggetto tipo;
    int val;
    struct Oggetto* next;
}Oggetto;

//Definizione della lista oggetti presenti nelle stanze
typedef struct{
    Oggetto* head;
    int len;
}ListaOggetti;

//Definizione della struct mostro come nodo
typedef struct Mostro{
    TipoMostro tipo;
    int HP;
    int XP;
    int danno;
    struct Mostro* next;
}Mostro;

//Definizione della lista dei mostri presenti in una stanza
typedef struct{
    Mostro* head;
    int len;
}ListaMostri;

//definizione stanza caricata da file
typedef struct{
    int ID;
    int nord;
    int sud;
    int est;
    int ovest;
    TipoOggetto tipo_oggetto;
    TipoMostro tipo_mostro;
    int valore_oggetto;
}StanzaSalvataggio;

//Definizione della struct stanza
typedef struct Stanza{
    struct Stanza* next;
    struct Stanza* nord;
    struct Stanza* sud;
    struct Stanza* est;
    struct Stanza* ovest;
    Oggetto* oggetto;
    Mostro* mostro;
    TipoOggetto tipo_oggetto;
    TipoMostro tipo_mostro;
    int ID;
    int numero_nord;
    int numero_sud;
    int numero_est;
    int numero_ovest;
    int valore_oggetto;
}Stanza;

typedef struct{
    Stanza* inizio;
    int numero_stanze;
}Mappa;

//struttura dati pila inventario eroe
typedef struct{
    Oggetto* next;
    int len;
}Inventario;

//struttura per l'eroe
typedef struct{
    int HP;
    int XP;
    int sheld;
    int danno;
    Inventario* inventario;
    Stanza* stanza_corrente;
    Mappa* mappa;
}Eroe;

#endif