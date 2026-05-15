#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../include/tipi.h"
#include "../include/eroe.h"
#include "../include/mappa.h"
#include "../include/combattimento.h"
#include "../include/utilities.h"

int main(){
    srand(time(NULL));
    int SOGLIE[LIVELLI] = {10, 20, 50, 100, 200};
    char input[MAX_DIMINPUT];
    char carica;
    char** comando = NULL;
    Bool fine = false;
    TipoComando cmd;
    Eroe* e = inizio_gioco();
    while(!fine){
        stampa_stato(e);
        printf(">");
        scanf("%[^\n]", input);
        clear_buffer();
        comando = dividi_input(input);
        cmd = parse(comando[0]);
        fine = esegui_comando(e, cmd, comando[1]);
        controlla_livello(e, SOGLIE);
        printf("\n\n");
    }
    fine_gioco(e);
    return 0;
}