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