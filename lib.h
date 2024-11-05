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
} EABB;

// LDE

Lista *inicializaLista() {};

ELista *inicializaELista(Registro *dados) {};

void inserirLDE(Lista *lista, Registro *dados) {};

void removerLDE(Lista *lista, Registro *dados) {};

void mostrarLDE(Lista *lista) {};



// Cadastrar
Registro *criaRegistro(char *nome, int idade, char *rg) {};

int cadastrarNovoPaciente(Lista *lista, ELista *elista, char *nome, int idade, char *rg) {};

void ConsultarPacienteCadastrado(Lista *lista, char *rg) {};

void mostrarListaCompleta(Lista *lista) {};

int atualizarDadosPaciente(Lista *lista, Registro *paciente, Registro *novosDados) {};

int removerPaciente(Lista *lista, Registro *paciente) {};

// Atendimento

void enfileirarPaciente(Fila *fila, Registro *paciente) {};

void desenfileirarPaciente(Fila *fila) {};

void mostrarFila(Fila *fila) {};

// Menus
void menu() {};

void menuCadastrar() {};

void menuAtendimento() {};

void menuPesquisa() {};

void menuDesfazer() {};

void menuSobre() {};