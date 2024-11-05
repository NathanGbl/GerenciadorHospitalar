typedef struct Registro{
    char *nome;
	int valor;
	char *rg;
	Data* pai;
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
    struct Elista *proximo;
    int ano;
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

// Menus
void menu() {}

void menuCadastrar() {}

void menuAtendimento() {}

void menuPesquisa() {}

void menuDesfazer() {}

void menuSobre() {}

// Cadastrar
int cadastrarNovoPaciente(Lista *lista, ELista *elista) {}

int ConsultarPacienteCadastrado(Lista *lista, Registro paciente) {}

void mostrarListaCompleta(Lista lista) {}

int atualizarDadosPaciente(Lista lista, Registro paciente, Registro novosDados) {}

int removerPaciente(Lista lista, Registro paciente) {}

// Atendimento

void enfileirarPaciente(Fila fila, Registro paciente) {}

void desenfileirarPaciente(Fila fila) {}

void mostrarFila(Fila fila) {}