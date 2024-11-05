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

EABB *cria_vertice(Registro *dados){
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

void RotacaoDireita(ABB *arvore, EABB *x) {
    x->filhoEsq->pai = x->pai;
    if (x->pai != NULL) {
        if (x->valor > x->pai->valor) {
            x->pai->dir = x->esq;
        } else {
            x->pai->esq = x->esq;
        }
    } else {
        arvore->raiz = x->esq;
    }
    x->pai = x->esq;
    x->esq = x->esq->dir;
    x->pai->dir = x;
    if (x->esq != NULL) {
        x->esq->pai = x;
    }
    printf("Direita em %d\n", x->valor);
}

void RotacaoEsquerda(Arvore *arvore, Vertice *x) {
    x->dir->pai = x->pai;
    if (x->pai != NULL) {
        if (x->valor > x->pai->valor) {
            x->pai->dir = x->dir;
        } else {
            x->pai->esq = x->dir;
        }
    } else {
        arvore->raiz = x->dir;
    }
    x->pai = x->dir;
    x->dir = x->dir->esq;
    x->pai->esq = x;
    if (x->dir != NULL) {
        x->dir->pai = x;
    }
    printf("Esquerda em %d\n", x->valor);
}

void balanceie (Arvore *arvore, Vertice *r) {
    if (fatorBalanceamento(r) >= 2 && fatorBalanceamento(r->dir) >= 0) {
        RotacaoEsquerda(arvore, r);
    } else if (fatorBalanceamento(r) >= 2 && fatorBalanceamento(r->dir) < 0) {
        RotacaoDireita(arvore, r->dir);
        RotacaoEsquerda(arvore, r);
    } else if (fatorBalanceamento(r) <= -2 && fatorBalanceamento(r->esq) <= 0) {
        RotacaoDireita(arvore, r);
    } else if (fatorBalanceamento(r) <= -2 && fatorBalanceamento(r->esq) > 0) {
        RotacaoEsquerda(arvore, r->esq);
        RotacaoDireita(arvore, r);
    }
}

int insere(Arvore *arvore, int valor) {
  Vertice *novo = malloc(sizeof(Vertice));
  novo->dir = NULL;
  novo->esq = NULL;
  novo->pai = NULL;
  novo->valor = valor;

  Vertice *anterior = NULL;
  Vertice *atual = arvore->raiz;

  while (atual != NULL) {
    anterior = atual;
    if (valor <= atual->valor) {
      atual = atual->esq;
    } else {
      atual = atual->dir;
    }
  }

  novo->pai = anterior;
  if (anterior != NULL) {
    if (valor <= anterior->valor) {
      anterior->esq = novo;
    } else {
      anterior->dir = novo;
    }
  } else {
    arvore->raiz = novo;
  }
  arvore->qtde++;

  Vertice *temp = novo->pai;
  while (temp != NULL) {
    balanceie(arvore, temp);
    temp = temp->pai;
  }
  return 1;
}

int remover(Arvore *arvore, Vertice *x) {
    int filhos = 0;

    if (x != NULL && x->esq != NULL) {
        filhos++;
    }
    if (x != NULL && x->dir != NULL) {
        filhos++;
    }

    Vertice *pai = x->pai;
    if (filhos == 0) {
        if (pai != NULL) {
        if (pai->esq == x) {
            pai->esq = NULL;
        } else {
            pai->dir = NULL;
        }
        } else {
        arvore->raiz = NULL;
        }
        arvore->qtde--;
    } else if (filhos == 1) {
        Vertice *filho = x->esq;
        if (filho == NULL)
        filho = x->dir;

        if (pai == NULL)
        arvore->raiz = filho;
        else {
        if (pai->esq == x)
            pai->esq = filho;
        else
            pai->dir = filho;
        }
        filho->pai = pai;
        arvore->qtde--;
    } else {
        Vertice *sucessor = x;
        sucessor = sucessor->dir;
        while (sucessor->esq != NULL)
        sucessor = sucessor->esq;
        x->valor = sucessor->valor;
        return remover(arvore, sucessor);
    }

    return 1;
}

int buscar_e_remover(ABB *arvore, int valor) {
    Vertice *atual = arvore->raiz;
    while (atual != NULL) {
        if (valor < atual->valor) {
            atual = atual->esq;
        } else if (valor > atual->valor) {
            atual = atual->dir;
        } else {
            return remover(arvore, atual);
        }
    }
    return 0;
}

int getValor(Arvore *arvore) { return arvore->qtde; }

void imprimeInOrdem(Vertice *raiz) {
  if (raiz != NULL) {
    imprimeInOrdem(raiz->esq);
    printf("%d ", raiz->valor);
    imprimeInOrdem(raiz->dir);
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

