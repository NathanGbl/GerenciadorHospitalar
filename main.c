#include "lib.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {

    Stack *pilha = criarPilha();
    Lista *listaRegistros = inicializaLista();
    Fila *filaPacientes = criaFila();
    int opcao = -1;
    char confirm;
    while(opcao != 0) {
        menu(&opcao);
        if (opcao == 1) {
            menuCadastrar(&opcao);
            if (opcao == 1 && cadastrarNovoPaciente(listaRegistros)) {
                printf("\tPaciente cadastrado com sucesso.\n");
            } else if (opcao == 2) {
                consultarPacienteCadastrado(listaRegistros);
            } else if (opcao == 3) {
                mostrarListaCompleta(listaRegistros);
            } else if (opcao == 4) {
                Registro *novosDados = criaRegistro();
                atualizarDadosPaciente(listaRegistros, novosDados);
            } else if (opcao == 5) {
                removerPaciente(listaRegistros);
            }
        } else if (opcao == 2) {
            menuAtendimento(&opcao);
            if (opcao == 1) {
                enfileirarPaciente(filaPacientes, listaRegistros, pilha);
            } else if (opcao == 2) {
                desenfileirarPaciente(filaPacientes, pilha);
            } else if (opcao == 3) {
                mostrarFila(filaPacientes);
            }
        } else if (opcao == 3) {
            menuPesquisa(&opcao);
            if (opcao == 1) {
                mostrarPorAno(listaRegistros);
            } else if (opcao == 2) {
                mostrarPorMes(listaRegistros);
            } else if (opcao == 3) {
                mostrarPorDia(listaRegistros);
            } else if (opcao == 4) {
                mostrarPorIdade(listaRegistros);
            }
        } else if (opcao == 4) {
            menuDesfazer(confirm);
            confirm = tolower(confirm);
            if (strcmp(&confirm, "s")) {
                desfazer(pilha, filaPacientes);
            }
        } else if (opcao == 5) {
            if (listaRegistros->inicio == NULL) {
                printf("\t\tLEU\n");
                leArquivo(listaRegistros);
            } else {
                printf("\t\tESCREVEU\n");
                escreveArquivo(listaRegistros);
            }
        } else if (opcao == 6) {
            menuSobre();
        }
    }
    return 1;

}