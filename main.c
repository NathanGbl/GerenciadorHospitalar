#include "lib.h"
#include <stdio.h>

int main() {

    Lista *listaRegistros = inicializaLista();
    int opcao;
    char confirm;
    while(opcao != 0) {
        menu(&opcao);
        if (opcao == 1) {
            menuCadastrar(&opcao);
        } else if (opcao == 2) {
            menuAtendimento(&opcao);
        } else if (opcao == 3) {
            menuPesquisa(&opcao);
        } else if (opcao == 4) {
            menuDesfazer(confirm);
        } else if (opcao == 5) {
            //escreveArquivo(listaRegistros);
        } else if (opcao == 6) {
            menuSobre();
        }
    }
    return 1;

}