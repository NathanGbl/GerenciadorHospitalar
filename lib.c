#include <lib.h>

void menu() {
    printf("1. Cadastrar\n");
    printf("2. Atendimento\n");
    printf("3. Pesquisa\n");
    printf("4. Desfazer\n");
    printf("5. Carregar/Salvar\n");
    printf("6. Sobre\n");
}

void menuCadastrar() {
    printf("\t1. Cadastrar novo paciente\n");
    printf("\t2. Consultar paciente cadastrado\n");
    printf("\t3. Mostrar lista completa\n");
    printf("\t4. Atualizar dados de paciente\n");
    printf("\t5. Remover paciente\n");
}

void menuAtendimento() {
    printf("\t1. Enfileirar paciente\n");
    printf("\t2. Desenfileirar cadastrado\n");
    printf("\t3. Mostrar fila\n");
}

void menuPesquisa() {
    printf("\tMostrar registros ordenados por:\n");
    printf("\t\t1. Por ano\n");
    printf("\t\t2. Por mes\n");
    printf("\t\t3. Por dia\n");
    printf("\t\t4. Por idade\n");
}

void menuDesfazer() {
    printf("Deseja reverter a ultima operacao feita no atendimento? (s/n)");
}

void menuSobre() {
    printf("\tAutores:\n");
    printf("\t\tNome: Nathan Gabriel da Fonseca Leite\n");
    printf("\t\tCiclo: \n");
    printf("\t\tCurso: Ciencia da Computacao\n");
    printf("\t\tDisciplina: Estrutura de Dados\n");
    printf("\t\tData:\n");

    printf("\t\tNome: Raphael Garavati Erbert\n");
    printf("\t\tCiclo: \n");
    printf("\t\tCurso: Ciencia da Computacao\n");
    printf("\t\tDisciplina: Estrutura de Dados\n");
    printf("\t\tData: \n");
}