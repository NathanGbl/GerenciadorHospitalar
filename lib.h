#include <stdio.h>

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Registro{
    char nome[51];
    int idade;
    char rg[12];
  Data* entrada;
} Registro;

typedef struct ELista {
    Registro *dados;
    struct ELista *proximo;
} ELista;

typedef struct Lista{
    ELista *inicio;
  int qtde;
} Lista;

typedef struct EFila {
    Registro *dados;
    struct EFila *anterior;
    struct EFila *proximo;
} EFila;

typedef struct Fila{
    EFila *head;
    EFila *tail;
    int qtde;
} Fila;

typedef struct EABB {
    Registro *dados;
    struct EABB *filhoEsq;
    struct EABB *filhoDir;
    struct EABB *pai;
} EABB;

typedef struct ABB{
    EABB *raiz;
    int qtde;
} ABB;

typedef struct Operacao {
    int acao;
    Registro *dados;
    struct Operacao *proximo;
} Operacao;

typedef struct Stack {
    Operacao *topo;
    int qtde;
} Stack;

// Geral

ELista *buscarPeloRg(Lista *lista, char rg[12]);

void mostrarPaciente(Registro *paciente);

void mostrarDadosPaciente(Registro *paciente);

void menu(int *opcao);

void menuCadastrar(int *opcao);

void menuAtendimento(int *opcao);

void menuPesquisa(int *opcao);

void menuDesfazer(char *confirm, Stack *pilha);

void menuSobre();

// Estrutura de Dados

Lista *inicializaLista();

ELista *inicializaELista(Registro *dados);

void inserirLDE(Lista *lista, Registro *dados);

int removerLDE(Lista *lista, char rg[12]);

void mostrarLDE(Lista *lista);

EFila *criaCelula(Registro *paciente);

Fila *criaFila();

void enqueue(Fila *queue, Registro *paciente);

EFila *dequeue(Fila *queue);

EABB *criaVertice(Registro *dados);

ABB *criaArvore();

void liberarArvore(EABB* vertice);

Operacao *criarOperacao(int acao, Registro *dados);

Stack *criarPilha();

void push(Stack *pilha, Operacao *op);

Operacao *pop(Stack *pilha);

/* 
    Modo = 1 => constroi pelo ano
    Modo = 2 => constroi pelo mes
    Modo = 3 => constroi pelo dia
    Modo = 4 => constroi pelo idade
 */

int inserirArvore(ABB *arvore, Registro *paciente, int modo);

void imprimeInOrdem(EABB *raiz);

// Cadastrar

Registro *criaRegistro();

int cadastrarNovoPaciente(Lista *lista);

void consultarPacienteCadastrado(Lista *lista);

void mostrarListaCompleta(Lista *lista);

void atualizarDadosPaciente(Lista *lista, Registro *novosDados);

int removerPaciente(Lista *lista);

// Atendimento

void enfileirarPaciente(Fila *fila, Lista *lista, Stack *pilha);

void desenfileirarPaciente (Fila *fila, Stack *pilha);

void mostrarFila(Fila *fila);

// Pesquisa

void mostrarPorAno(Lista *lista);

void mostrarPorMes(Lista *lista);

void mostrarPorDia(Lista *lista);

void mostrarPorIdade(Lista *lista);

// Desfazer
// acao == 1 => enqueue
// acao == 2 => dequeue
void desfazer(Stack *pilha, Fila *queue);

// Carregar/Salvar

void leArquivo(Lista *lista);

void escreveArquivo(Lista *lista);

void limpaBuffer();