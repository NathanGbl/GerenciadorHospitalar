#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Lista *inicializaLista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtde = 0;
    return lista;
}

ELista *inicializaELista(Registro *dados) {
    ELista *elista = malloc(sizeof(ELista));
    elista->proximo = NULL;
    elista->dados = dados;
  return elista;
}

void inserirLDE(Lista *lista, Registro *dados) {
    ELista *nova = inicializaELista(dados);
    nova->proximo = lista->inicio;
    lista->inicio = nova;
    lista->qtde++;
}

void removerLDE(Lista *lista, Registro *dados) {
    ELista *atual = lista->inicio;
    ELista *anterior = NULL;
    if (lista->qtde == 0) {
        return;
    } else {
        while (atual != NULL && atual->dados->rg != dados->rg) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL) {
            return;
        }
        if (anterior == NULL) {
            lista->inicio = atual->proximo;
        } else if (atual->proximo == NULL) {
            anterior->proximo = NULL;
        } else {
            anterior->proximo = atual->proximo;
        }
    }
    free(atual);
    lista->qtde--;
}

void mostrarPaciente(Registro *paciente) {
    printf("\tNome: %s\n", paciente->nome);
    printf("\tIdade: %d\n", paciente->idade);
    printf("\tRG: %s\n", paciente->rg);
    printf("\tEntrada: %d/%d/%d\n", 
        paciente->entrada->dia, 
        paciente->entrada->mes, 
        paciente->entrada->ano
    );
}

void mostrarLDE(Lista *lista) {
  ELista *atual = lista->inicio;
  int qtde = 0;
  while (atual != NULL) {
    printf("===== Paciente %d =====\n", qtde);
    mostrarPaciente(atual->dados);
    atual = atual->proximo;
    qtde++;
  }
  printf("\n");
  return;
}

// Cadastrar

Registro *criaRegistro(char *nome, int idade, char *rg) {
    Registro *novoPaciente = malloc(sizeof(Registro));
    srand(time(NULL));
    int dia = (rand() % 30) + 1;
    int mes = (rand() % 11) + 1;
    int ano = (rand() % 2024) + 84;

    while (ano > 2024 || ano < 1940) {
        ano = (rand() % 2024) + 84;
    }

    novoPaciente->nome = nome;
    novoPaciente->idade = idade;
    novoPaciente->rg = rg;
    novoPaciente->entrada->dia = dia;
    novoPaciente->entrada->mes = mes;
    novoPaciente->entrada->ano = ano;
};

int cadastrarNovoPaciente(Lista *lista, ELista *elista, char *nome, int idade, char *rg) {
    Registro *novoPaciente = criaRegistro(nome, idade, rg);
    inserirLDE(lista, novoPaciente);
    return 1;
}

void mostrarDadosPaciente(Registro *paciente) {
    printf("===== Paciente =====\n");
    mostrarPaciente(paciente);
    return;
}

ELista *buscarPeloRg(Lista *lista, char *rg) {
    ELista *atual = lista->inicio;
    while (atual != NULL && atual->dados->rg != rg) {
        atual = atual->proximo;
    }
    return atual;
}

void ConsultarPacienteCadastrado(Lista *lista, char *rg) {
    ELista *paciente = buscarPeloRg(lista, rg);
    if (paciente == NULL) {
        printf("\t\tPaciente não encontrado\n");
        return;
    }
    mostrarDadosPaciente(paciente);
};

void mostrarListaCompleta(Lista *lista) { mostrarLDE(lista); };

int atualizarDadosPaciente(Lista *lista, Registro *paciente, Registro *novosDados) {
    ELista *atual = buscarPeloRg(lista, paciente->rg);
    if (atual != NULL) {
        if (novosDados->nome != "") {
            atual->dados->nome = novosDados->nome;
        }
        if (novosDados->idade != 0) {
            atual->dados->idade = novosDados->idade;
        }
        if (novosDados->rg != "") {
            atual->dados->rg = novosDados->rg;
        }
        return 1;
    }
    return 0;

};

int removerPaciente(Lista *lista, Registro *paciente) { removerLDE(lista, paciente); };

// Atendimento

Fila *inicializaFila() {
    Fila *fila = malloc(sizeof(Fila));
    fila->head = NULL;
    fila->tail = NULL;
    fila->qtde = 0;

    return fila;
}

EFila *inicializaEFila(Registro *dados) {
    EFila *efila = malloc(sizeof(EFila));

    efila->proximo = NULL;
    efila->dados = dados;

    return efila;
}

void enfileirarPaciente(Fila *fila, Registro *dados) {
    EFila *novo = inicializaEFila(dados);
    if (fila->qtde == 0) {
        fila->head = novo;
    } else {
        fila->tail->proximo = novo;
    }
    fila->tail = novo;
    fila->qtde++;
    return;
}

EFila *desenfileirarPaciente (Fila *fila) {
    if (fila->qtde == 0) {
        return -1;
    }

    Registro *paciente = fila->head->dados;
    EFila *temp = fila->head;
    fila->head = fila->head->proximo;

    if (fila->qtde == 1) {
        fila->tail = NULL;
    }
    fila->qtde--;
    free(temp);
    return paciente;
}

void mostrarFila(Fila *fila) {
    EFila *atual = fila->head;
    while(atual != NULL) {
        mostrarPaciente(atual->dados);
        atual = atual->proximo;
    }
    printf("\n");
}

// Pesquisa



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
    printf("Deseja reverter a ultima operacao feita no atendimento? (s/n)\n");
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