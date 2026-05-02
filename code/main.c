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
    char** comando = NULL;
    Bool vinto = false;
    TipoComando cmd;
    Eroe* e = crea_eroe();
    printf("Gioco INIZIATO (debug mode)");
    while(e->HP > 0 && !vinto){
        scanf("%[^\n]", input);
        comando = dividi_input(input);
        cmd = parse(comando[0]);
        esegui_comando(e, cmd, comando[1]);
    }
    elimina_eroe(e);
    return 0;
}