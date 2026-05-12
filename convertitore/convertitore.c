/*Questo programma converte una mappa dal formato .txt al formato .map
Ogni stanza è allocata quando un giocatore ci entra per la prima volta; è quindi necessario 
identificare ogni stanza con un numero, caricarla nel gioco e poi collegarla con le altre.
Ogni stanza è rappresentata da una riga nel file, e i valori sono separati da uno spazio

Struttura del file txt in input:
NUMERO_STANZE           numero delle stanze presenti nel file

per ogni stanza è presente questa struttura:
ID                      ID della stanza -> serve per identificare la stanza nella mappa
nord                    numeri della stanze presenti nelle varie direzioni della stanza corrente
est
sud
ovest
tipo_mostro             numero del tipo di mostro che è presente nella stanza
tipo_oggetto            numero del tipo di oggetto che è presente nella stanza
valore                  valore dell'oggetto presente nella stanza.

Esempio di mappa

                            Stanza 4
                               ^
                               |
        Stanza 3    <-      Stanza 1        ->    Stanza 2
                      (no mostri o oggetti)
La riga nel file.txt della stanza 1 sarà la seguente:
1 4 2 -1 3 0 0 0 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* f_csv = fopen("../convertitore/mappa.csv", "r");
    FILE* f_bin = fopen("mappa.map", "wb");

    if (!f_csv || !f_bin) {
        printf("Errore apertura file\n");
        return 1;
    }

    char line[1000];
    StanzaSalvataggio s;

    // salta header
    fgets(line, sizeof(line), f_csv);

    while (fscanf(f_csv,
        "%d, \"%199[^\"]\", \"%199[^\"]\", %d, %d, %d, %d, %d, %d, %d",
        &s.ID,
        s.nome,
        s.desc,
        &s.nord,
        &s.est,
        &s.sud,
        &s.ovest,
        &s.tipo_mostro,
        &s.tipo_oggetto,
        &s.valore_oggetto) == 10)
    {
        printf("%d,%s,%s,%d,%d,%d,%d,%d,%d,%d\n",
    s.ID,
    s.nome,
    s.desc,
    s.nord,
    s.est,
    s.sud,
    s.ovest,
    s.tipo_mostro,
    s.tipo_oggetto,
    s.valore_oggetto);
        fwrite(&s, sizeof(StanzaSalvataggio), 1, f_bin);
    }

    fclose(f_csv);
    fclose(f_bin);

    printf("Conversione completata\n");

    return 0;
}