#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/tipi.h"
#include "../include/eroe.h"
#include "../include/mappa.h"
#include "../include/combattimento.h"
#include "../include/utilities.h"

int main(){
    char input[MAX_DIMINPUT];
    char carica;
    char** comando = NULL;
    Bool vinto = false;
    TipoComando cmd;
    Eroe* e = inizio_gioco();
    printf("Gioco INIZIATO (debug mode)\n");
    while(e->HP > 0 && !vinto){
        stampa_stato(e);
        printf(">");
        scanf("%[^\n]", input);
        clear_buffer();
        comando = dividi_input(input);
        cmd = parse(comando[0]);
        esegui_comando(e, cmd, comando[1]);
        system("PAUSE");
        system("CLS");
    }
    elimina_eroe(e);
    return 0;
}