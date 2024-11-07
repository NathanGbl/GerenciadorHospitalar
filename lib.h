typedef struct Registro{
    char *nome;
	int idade;
	char *rg;
	Data* entrada;
} Registro;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct Lista{
    ELista *inicio;
	int qtde;
} Lista;

typedef struct ELista {
    Registro *dados;
    struct ELista *proximo;
} ELista;

typedef struct Fila{
    EFila *head;
    EFila *tail;
    int qtde;
} Fila;

typedef struct EFila {
    Registro *dados;
    struct EFila *anterior;
    struct EFila *proximo;
} EFila;

typedef struct ABB{
    EABB *raiz;
    int qtde;
} ABB;

typedef struct EABB {
    Registro *dados;
    EABB *filhoEsq;
    EABB *filhoDir;
    EABB *pai;
} EABB;

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

ELista *buscarPeloRg(Lista *lista, char *rg) {}

void mostrarPaciente(Registro *paciente) {}

void mostrarDadosPaciente(Registro *paciente) {}

void menu(int *opcao) {}

void menuCadastrar(int *opcao) {}

void menuAtendimento(int *opcao) {}

void menuPesquisa(int *opcao) {}

// Estrutura de Dados

Lista *inicializaLista() {}

ELista *inicializaELista(Registro *dados) {}

void inserirLDE(Lista *lista, Registro *dados) {}

void removerLDE(Lista *lista, Registro *dados) {}

void mostrarLDE(Lista *lista) {}

EFila *criaCelula(Registro *paciente){}

Fila *criaFila(){}

void enqueue(Fila *queue, Registro *paciente){}

void dequeue(Fila *queue){}

EABB *criaVertice(Registro *dados){}

ABB *criaArvore(){}

void liberarArvore(EABB* vertice) {}

int max(int x, int y) {}

int altura (EABB *x) {}

int fatorBalanceamento(EABB *x) {}

void RotacaoDireita(ABB *arvore, EABB *x, int modo) {}

void RotacaoEsquerda(ABB *arvore, EABB *x, int modo) {}

void balanceie (ABB *arvore, EABB *r, int modo) {}

int inserirArvore(ABB *arvore, Registro *paciente, int modo) {}

void imprimeInOrdem(EABB *raiz) {}

// Cadastrar

Registro *criaRegistro(char *nome, int idade, char *rg) {};

int cadastrarNovoPaciente(Lista *lista, ELista *elista, char *nome, int idade, char *rg) {}

void ConsultarPacienteCadastrado(Lista *lista, char *rg) {};

void mostrarListaCompleta(Lista *lista) {};

int atualizarDadosPaciente(Lista *lista, Registro *paciente, Registro *novosDados) {};

int removerPaciente(Lista *lista, Registro *paciente) { removerLDE(lista, paciente); };

// Atendimento

void enfileirarPaciente(Fila *fila, Registro *dados) {}

EFila *desenfileirarPaciente (Fila *fila) {}

void mostrarFila(Fila *fila) {}

// Pesquisa

void mostrarPorAno(Lista *lista) {}

void mostrarPorMes(Lista *lista) {}

void mostrarPorDia(Lista *lista) {}

void mostrarPorIdade(Lista *lista) {}

int desfazer(Stack *pilha, Fila *queue) {}

// Carregar/Salvar

void leArquivo(Lista *lista) {}

void escreveArquivo(Lista *lista) {}

void limpaBuffer() {}