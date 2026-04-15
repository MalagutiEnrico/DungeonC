/*Libreria contenente la definizione dei tipi e delle costanti del gioco*/

#define MAX_INVENTARIO 8        //numero di oggetti massimi nell'inventario
#define MAX_DIMINPUT 100        //numero massimo di caratteri inseribili in fase di input
#define MAX_SALUTE 100          //valore massimo di salute dell'eroe

//Definizione dei tipi di oggetto presenti nelle stanze e nell'inventario
typedef enum{
    POZIONE,
    ARMA,
    ARMATURA, 
    CHIAVE,
    TORCIA
}TipoOggetto;

//Definizione dei tipi di mostro incontrabili nel gioco
typedef enum{
    SCHELETRO,
    GOBLIN,
    DRAGO,
    BOSS
}TipoMostro;

//Definizione dei tipi di comando inseribili nel gioco
typedef enum{
    vai,
    guarda,
    prendi,
    usa,
    attacca,
    inventario,
    salva,
    carica,
    mappa,
    help
}TipoComando;

//Definizione della struct oggetto come nodo
typedef struct{
    TipoOggetto tipo;
    Oggetto* next;
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
    Mostro* next;
}Mostro;

//Definizione della lista dei mostri presenti in una stanza
typedef struct{
    Mostro* head;
    int len;
}ListaMostri;

//Definizione della struct stanza
typedef struct Stanza{
    Stanza* nord;           //puntatori alle stanze
    Stanza* sud;
    Stanza* est;
    Stanza* ovest;
    ListaOggetti* oggetti;
    ListaMostri* mostri;
    int numero_oggetti;
    int numero_mostri;
}Stanza;

//struttura dati pila inventario eroe
typedef struct{
    Oggetto* next;
    int len;
}Pila;

//struttura per l'eroe
typedef struct{
    int HP;
    int XP;
    Pila* inventario;
    Stanza* stanza_corrente;
}Eroe;