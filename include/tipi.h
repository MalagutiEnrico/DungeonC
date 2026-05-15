/*Libreria contenente la definizione dei tipi e delle costanti del gioco*/
#ifndef TIPI_H
#define TIPI_H

#define MAX_INVENTARIO 8        //numero di oggetti massimi nell'inventario
#define MAX_DIMINPUT 100        //numero massimo di caratteri inseribili in fase di input
#define MAX_DIMDESC 200         //dimensione massima delle descrizioni delle stanze
#define MAX_SALUTE 100          //valore massimo di salute dell'eroe
#define DANNI_INIZIALI 10       //numero di danni che fa all'inizio del gioco
#define LIVELLI 5               //numero di livelli possibile dell'eroe
#define STANZA_CARICAMENTO 1   //stanza iniziale del gioco;

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
    ESCI,
    INVALIDO
}TipoComando;

//Definizione della struct oggetto come nodo
typedef struct Oggetto{
    TipoOggetto tipo;
    int val;
    struct Oggetto* next;
}Oggetto;

//Definizione della lista oggetti presenti nelle stanze
typedef struct ListaOggetti{
    Oggetto* head;
    int len;
}ListaOggetti;

//Definizione della struct mostro come nodo
typedef struct Mostro{
    TipoMostro tipo;
    int HP;
    int XP;
    int danno;
}Mostro;

//definizione stanza caricata da file
typedef struct StanzaSalvataggio{
    int ID;
    int nord;
    int est;
    int sud;
    int ovest;
    TipoMostro tipo_mostro;
    TipoOggetto tipo_oggetto;
    int valore_oggetto;
    char nome[MAX_DIMDESC];
    char desc[MAX_DIMDESC];
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
    char nome[MAX_DIMDESC];
    char desc[MAX_DIMDESC];
    int ID;
    int numero_nord;
    int numero_sud;
    int numero_est;
    int numero_ovest;
}Stanza;

typedef struct Mappa{
    Stanza* inizio;
    int numero_stanze;
}Mappa;

//struttura dati pila inventario eroe
typedef struct Inventario{
    Oggetto* next;
    int len;
}Inventario;

//struttura per l'eroe
typedef struct Eroe{
    char* nome[20];
    int livello;
    int HP;
    int XP;
    int shield;
    int danno;
    Inventario* inventario;
    Stanza* stanza_corrente;
    Mappa* mappa;
}Eroe;

#endif