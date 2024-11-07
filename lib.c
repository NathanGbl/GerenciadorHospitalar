#include <lib.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Geral

ELista *buscarPeloRg(Lista *lista, char *rg) {

    ELista *atual = lista->inicio;
    while (atual != NULL && atual->dados->rg != rg) {
        atual = atual->proximo;
    }
    return atual;

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

void mostrarDadosPaciente(Registro *paciente) {

    printf("===== Paciente =====\n");
    mostrarPaciente(paciente);
    return;

}

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

// Estrutura de Dados

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

EFila *criaCelula(Registro *paciente){

	EFila *efila = malloc(sizeof(EFila));
	efila->proximo = NULL;
	efila->anterior = NULL;
	efila->dados = paciente;
	return efila;

}

Fila *criaFila(){

	Fila *queue = malloc(sizeof(Fila));
	queue->head = NULL;
	queue->tail = NULL;
	queue->qtde = 0;
	return queue;

}

void enqueue(Fila *queue, Registro *paciente){

	EFila *novo = criaCelula(paciente);
    if (queue->qtde == 0) {
        queue->head = novo;
    } else {
        queue->tail->proximo = novo;
        novo->anterior = queue->tail;
    }
    queue->tail = novo;
    queue->qtde++;
    return;

}

void dequeue(Fila *queue){

	if (queue->qtde == 0) {
        return;
    }

    EFila *temp = queue->head;
    queue->head = queue->head->proximo;

    if (queue->qtde == 1) {
        queue->tail = NULL;
    } else {
        queue->head->anterior = NULL;
    }
    queue->qtde--;
    free(temp);

}

EABB *criaVertice(Registro *dados){

	EABB* novo = malloc(sizeof(EABB));
	novo->filhoDir = NULL;
	novo->filhoEsq = NULL;
	novo->pai = NULL;
	novo->dados = dados;
	return novo;

}

ABB *criaArvore(){

	ABB* arvore = malloc(sizeof(ABB));
	arvore->raiz = NULL;
	arvore->qtde = 0;
	return arvore;

}

void liberarArvore(EABB* vertice) {

    if (vertice != NULL) {
        liberar_arvore(vertice->filhoEsq);
        liberar_arvore(vertice->filhoDir);
        free(vertice);
    }

}

int max(int x, int y) {
    return x >= y ? x : y;
}

int altura (EABB *x) {

    if (x == NULL) {
        return -1;
    }
    return max(altura(x->filhoEsq), altura(x->filhoDir)) + 1;

}

int fatorBalanceamento(EABB *x) {
    return altura(x->filhoDir) - altura(x->filhoEsq);
}

/* 
    Modo = 1 => constroi pelo ano
    Modo = 2 => constroi pelo mes
    Modo = 3 => constroi pelo dia
    Modo = 4 => constroi pelo idade
 */

void RotacaoDireita(ABB *arvore, EABB *x, int modo) {

    x->filhoEsq->pai = x->pai;
    if (x->pai != NULL) {
        if (modo == 1 && x->dados->entrada->ano > x->pai->dados->entrada->ano) {
            x->pai->filhoDir = x->filhoEsq;
        } else if (modo == 2 && x->dados->entrada->mes > x->pai->dados->entrada->mes) {
            x->pai->filhoDir = x->filhoEsq;
        } else if (modo == 3 && x->dados->entrada->dia > x->pai->dados->entrada->dia) {
            x->pai->filhoDir = x->filhoEsq;
        } else if (modo == 4 && x->dados->idade > x->pai->dados->idade) {
            x->pai->filhoDir = x->filhoEsq;
        } else {
            x->pai->filhoEsq = x->filhoEsq;
        }
    } else {
        arvore->raiz = x->filhoEsq;
    }
    x->pai = x->filhoEsq;
    x->filhoEsq = x->filhoEsq->filhoDir;
    x->pai->filhoDir = x;
    if (x->filhoEsq != NULL) {
        x->filhoEsq->pai = x;
    }

}

void RotacaoEsquerda(ABB *arvore, EABB *x, int modo) {

    x->filhoDir->pai = x->pai;
    if (x->pai != NULL) {
        if (modo == 1 && x->dados->entrada->ano > x->pai->dados->entrada->ano) {
            x->pai->filhoDir = x->filhoDir;
        } else if (modo == 2 && x->dados->entrada->mes > x->pai->dados->entrada->mes) {
            x->pai->filhoDir = x->filhoDir;
        } else if (modo == 3 && x->dados->entrada->dia > x->pai->dados->entrada->dia) {
            x->pai->filhoDir = x->filhoDir;
        } else if (modo == 4 && x->dados->idade > x->pai->dados->idade) {
            x->pai->filhoDir = x->filhoDir;
        } else {
            x->pai->filhoEsq = x->filhoDir;
        }
    } else {
        arvore->raiz = x->filhoDir;
    }
    x->pai = x->filhoDir;
    x->filhoDir = x->filhoDir->filhoEsq;
    x->pai->filhoEsq = x;
    if (x->filhoDir != NULL) {
        x->filhoDir->pai = x;
    }

}

void balanceie (ABB *arvore, EABB *r, int modo) {

    if (fatorBalanceamento(r) >= 2 && fatorBalanceamento(r->filhoDir) >= 0) {
        RotacaoEsquerda(arvore, r, modo);
    } else if (fatorBalanceamento(r) >= 2 && fatorBalanceamento(r->filhoDir) < 0) {
        RotacaoDireita(arvore, r->filhoDir, modo);
        RotacaoEsquerda(arvore, r , modo);
    } else if (fatorBalanceamento(r) <= -2 && fatorBalanceamento(r->filhoEsq) <= 0) {
        RotacaoDireita(arvore, r, modo);
    } else if (fatorBalanceamento(r) <= -2 && fatorBalanceamento(r->filhoEsq) > 0) {
        RotacaoEsquerda(arvore, r->filhoEsq, modo);
        RotacaoDireita(arvore, r, modo);
    }

}

int inserirArvore(ABB *arvore, Registro *paciente, int modo) {

  EABB *novoPaciente = criaVertice(paciente);

  EABB *anterior = NULL;
  EABB *atual = arvore->raiz;

  while (atual != NULL) {
    anterior = atual;
    if (modo == 1 && novoPaciente->dados->entrada->ano > atual->dados->entrada->ano) {
        atual = atual->filhoDir;
    } else if (modo == 2 && novoPaciente->dados->entrada->mes > atual->dados->entrada->mes) {
        atual = atual->filhoDir;
    } else if (modo == 3 && novoPaciente->dados->entrada->dia > atual->dados->entrada->dia) {
        atual = atual->filhoDir;
    } else if (modo == 4 && novoPaciente->dados->idade > atual->dados->idade) {
        atual = atual->filhoDir;
    } else {
        atual = atual->filhoEsq;
    }
  }

  novoPaciente->pai = anterior;
  if (anterior != NULL) {
    if (novoPaciente->dados->entrada->ano < anterior->dados->entrada->ano ||
        novoPaciente->dados->entrada->mes < atual->dados->entrada->mes ||
        novoPaciente->dados->entrada->dia < atual->dados->entrada->dia ||
        novoPaciente->dados->idade > atual->dados->idade) {
      anterior->filhoEsq = novoPaciente;
    } else {
      anterior->filhoDir = novoPaciente;
    }
  } else {
    arvore->raiz = novoPaciente;
  }
  arvore->qtde++;

  EABB *temp = novoPaciente->pai;
  while (temp != NULL) {
    balanceie(arvore, temp, modo);
    temp = temp->pai;
  }
  return 1;
  
}

void imprimeInOrdem(EABB *raiz) {

  if (raiz != NULL) {
    imprimeInOrdem(raiz->filhoEsq);
    mostrarDadosPaciente(raiz->dados);
    imprimeInOrdem(raiz->filhoDir);
  }

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

void mostrarPorAno(Lista *lista) {

    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    for (int i = 0; i < lista->qtde; i++) {
        inserirArvore(arvore, atual->dados, 1);
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);

}

void mostrarPorMes(Lista *lista) {

    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    for (int i = 0; i < lista->qtde; i++) {
        inserirArvore(arvore, atual->dados, 2);
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);

}

void mostrarPorDia(Lista *lista) {

    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    for (int i = 0; i < lista->qtde; i++) {
        inserirArvore(arvore, atual->dados, 3);
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);

}

void mostrarPorIdade(Lista *lista) {

    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    for (int i = 0; i < lista->qtde; i++) {
        inserirArvore(arvore, atual->dados, 4);
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);

}

// Desfazer
// acao == 1 => enqueue
// acao == 2 => dequeue
int desfazer(Stack *pilha, Fila *queue) {

    if (pilha->topo != NULL) {
        if (pilha->topo->acao == 1) {
            EFila *temp = queue->tail;
            queue->tail->anterior->proximo = NULL;
            queue->tail = queue->tail->anterior;
            free(temp);
        } else if (pilha->topo->acao == 2) {
            EFila *novo = criaCelula(pilha->topo->dados);
            novo->proximo = queue->head;
            queue->head->anterior = novo;
            queue->head = novo;
        } else {
            return 0;
        }
        return 1;
    } else {
        return 0;
    }

}

// Carregar/Salvar

void le_arquivo(Lista *lista) {

    FILE *f = fopen("registros", "rb");
    if (f == NULL) {
        return;
    }
    fread(lista->qtde, sizeof(int), 1, f);
    
    for (int i = 0; i < lista->qtde; i++) {
        ELista *novo;
        fread(novo, sizeof(ELista) -sizeof(ELista*), 1, f);
    }
    return;

}

void escreve_arquivo(Lista *lista) {

    FILE *f = fopen("tarefas", "wb");

    if (f == NULL) {
        return;
    }
    fwrite(lista, sizeof(Lista), 1, f);
    fclose(f);
  
}

void clean_buffer() {

    int i;
    while ((i = getchar() != '\n' && i != EOF));

}