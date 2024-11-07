#include "lib.h"
#include <stdio.h>

int main() {

    Lista *listaRegistros = inicializaLista();
    int opcao;
    char confirm;
    while(opcao != 0) {
        menu(&opcao);
    }

}