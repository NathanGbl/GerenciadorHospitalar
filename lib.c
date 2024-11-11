#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Geral

ELista *buscarPeloRg(Lista *lista, char rg[12]) {

    ELista *atual = lista->inicio;
    while (atual != NULL && strcmp(atual->dados->rg, rg)) {
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

void menu(int *opcao) {

    printf("Atendimento médico à sua disposição, o que gostaria?\n");
    printf("1. Cadastrar\n");
    printf("2. Atendimento\n");
    printf("3. Pesquisa\n");
    printf("4. Desfazer\n");
    printf("5. Carregar/Salvar\n");
    printf("6. Sobre\n");
    printf("Opção: ");
    scanf("%d", opcao);

}

void menuCadastrar(int *opcao) {

    printf("\t1. Cadastrar novo paciente\n");
    printf("\t2. Consultar paciente cadastrado\n");
    printf("\t3. Mostrar lista completa\n");
    printf("\t4. Atualizar dados de paciente\n");
    printf("\t5. Remover paciente\n");
    printf("\t6. Voltar\n");
    printf("\tOpção: ");
    scanf("%d", opcao);
}

void menuAtendimento(int *opcao) {

    printf("\t1. Enfileirar paciente\n");
    printf("\t2. Desenfileirar paciente\n");
    printf("\t3. Mostrar fila\n");
    printf("\t4. Voltar\n");
    printf("\tOpção: ");
    scanf("%d", opcao);

}

void menuPesquisa(int *opcao) {

    printf("\tMostrar registros ordenados por:\n");
    printf("\t\t1. Por ano\n");
    printf("\t\t2. Por mes\n");
    printf("\t\t3. Por dia\n");
    printf("\t\t4. Por idade\n");
    printf("\t5. Voltar\n");
    printf("Opção: ");
    scanf("%d", opcao);

}

void menuDesfazer(char *confirm) {

    printf("\tDeseja reverter a ultima operacao feita no atendimento?(s/n)\n");
    printf("\tOpção: ");
    limpaBuffer();
    scanf("%c", confirm);

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

int removerLDE(Lista *lista, char rg[12]) {

    ELista *atual = lista->inicio;
    ELista *anterior = NULL;
    if (lista->qtde == 0) {
        return 0;
    } else {
        ELista *atual = buscarPeloRg(lista, rg);
        if (atual == NULL) {
            return 0;
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
    return 1;

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

EFila *dequeue(Fila *queue){

  if (queue->qtde == 0) {
        return NULL;
    }

    EFila *temp = queue->head;
    queue->head = queue->head->proximo;

    if (queue->qtde == 1) {
        queue->tail = NULL;
    } else {
        queue->head->anterior = NULL;
    }
    queue->qtde--;
    return temp;

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
        liberarArvore(vertice->filhoEsq);
        liberarArvore(vertice->filhoDir);
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
        if (x->pai != NULL) {
            if (modo == 1) {
                if (x->dados->entrada->ano > x->pai->dados->entrada->ano) {
                    x->pai->filhoDir = x->filhoEsq;
                } else {
                    x->pai->filhoEsq = x->filhoEsq;
                }
            } else if (modo == 2) {
                if (x->dados->entrada->mes > x->pai->dados->entrada->mes) {
                    x->pai->filhoDir = x->filhoEsq;
                } else {
                    x->pai->filhoEsq = x->filhoEsq;
                }
            } else if (modo == 3) {
                if (x->dados->entrada->dia > x->pai->dados->entrada->dia) {
                    x->pai->filhoDir = x->filhoEsq;
                } else {
                    x->pai->filhoEsq = x->filhoEsq;
                }
            } else if (modo == 4) {
                if (x->dados->idade > x->pai->dados->idade) {
                    x->pai->filhoDir = x->filhoEsq;
                } else {
                    x->pai->filhoEsq = x->filhoEsq;
                }
            }
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
        if (modo == 1) {
            if (x->dados->entrada->ano > x->pai->dados->entrada->ano) {
                x->pai->filhoDir = x->filhoDir;
            } else {
                x->pai->filhoEsq = x->filhoDir;
            }
        } else if (modo == 2) {
            if (x->dados->entrada->mes > x->pai->dados->entrada->mes) {
                x->pai->filhoDir = x->filhoDir;
            } else {
                x->pai->filhoEsq = x->filhoDir;
            }
        } else if (modo == 3) {
            if (x->dados->entrada->dia > x->pai->dados->entrada->dia) {
                x->pai->filhoDir = x->filhoDir;
            } else {
                x->pai->filhoEsq = x->filhoDir;
            }
        } else if (modo == 4) {
            if (x->dados->idade > x->pai->dados->idade) {
                x->pai->filhoDir = x->filhoDir;
            } else {
                x->pai->filhoEsq = x->filhoDir;
            }
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
    if (modo == 1) {
        if (novoPaciente->dados->entrada->ano > atual->dados->entrada->ano) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 2) {
        if (novoPaciente->dados->entrada->mes > atual->dados->entrada->mes) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 3) {
        if (novoPaciente->dados->entrada->dia > atual->dados->entrada->dia) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 4) {
        if (novoPaciente->dados->idade > atual->dados->idade) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else {
        return 0;
    }
  }

  novoPaciente->pai = anterior;
  if (anterior != NULL) {
    if (modo == 1) {
        if (novoPaciente->dados->entrada->ano > atual->dados->entrada->ano) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 2) {
        if (novoPaciente->dados->entrada->mes > atual->dados->entrada->mes) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 3) {
        if (novoPaciente->dados->entrada->dia > atual->dados->entrada->dia) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
    } else if (modo == 4) {
        if (novoPaciente->dados->idade > atual->dados->idade) {
            atual = atual->filhoDir;
        } else {
            atual = atual->filhoEsq;
        }
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

Operacao *criarOperacao(int acao, Registro *dados) {

    Operacao *op = malloc(sizeof(Operacao));
    op->proximo = NULL;
    op->acao = acao;
    op->dados = dados;
    return op;

}

Stack *criarPilha() {

    Stack *pilha = malloc(sizeof(Stack));
    pilha->topo = NULL;
    return pilha;

}

void push(Stack *pilha, Operacao *op) {

    op->proximo = pilha->topo;
    pilha->topo = op;

}

Operacao *pop(Stack *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    Operacao *temp = pilha->topo;
    pilha->topo = temp->proximo;
    return temp;

}

// Cadastrar

Registro *criaRegistro() {

    int idade;
    char rg[12];
    char nome[51];

    printf("\t\tDigite o nome do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", nome);
    printf("\t\tDigite a idade do paciente: ");
    limpaBuffer();
    scanf("%d", &idade);
    printf("\t\tDigite o rg do paciente: ");
    limpaBuffer();
    scanf("%s", rg);
    
    Registro *novoPaciente = malloc(sizeof(Registro));
    novoPaciente->entrada = malloc(sizeof(Data));
    srand(time(NULL));
    int dia = (rand() % 30) + 1;
    int mes = (rand() % 11) + 1;
    int ano = 2024;

    strcpy(novoPaciente->nome, nome);
    novoPaciente->idade = idade;
    strcpy(novoPaciente->rg, rg);
    novoPaciente->entrada->dia = dia;
    novoPaciente->entrada->mes = mes;
    novoPaciente->entrada->ano = ano;
    return novoPaciente;

};

int cadastrarNovoPaciente(Lista *lista) {

    Registro *novoPaciente = criaRegistro();
    inserirLDE(lista, novoPaciente);
    return 1;

}

void consultarPacienteCadastrado(Lista *lista) {

    char rg[12];
    printf("\tDigite o rg do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);
    ELista *paciente = buscarPeloRg(lista, rg);
    if (paciente == NULL) {
        printf("\t\tPaciente não encontrado\n");
        return;
    }
    mostrarDadosPaciente(paciente->dados);

};

void mostrarListaCompleta(Lista *lista) { mostrarLDE(lista); };

void atualizarDadosPaciente(Lista *lista, Registro *novosDados) {

    char rg[12];
    printf("\t\tDigite o rg antigo do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);
    ELista *atual = buscarPeloRg(lista, rg);
    if (atual != NULL) {
        strcpy(atual->dados->nome, novosDados->nome);
        atual->dados->idade = novosDados->idade;
        strcpy(atual->dados->rg, novosDados->rg);
        printf("Dados do paciente atualizados com sucesso.\n");
        return;
    }
    printf("Paciente não encontrado.");

};

int removerPaciente(Lista *lista) { 
    
    char rg[12];
    printf("Digite o rg do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);
    return removerLDE(lista, rg);
    
};

// Atendimento

void enfileirarPaciente(Fila *fila, Lista *lista, Stack *pilha) {

    char rg[12];
    printf("\t\tDigite o rg do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);

    ELista *elista = buscarPeloRg(lista, rg);
    if (elista != NULL) {
        enqueue(fila, elista->dados);
        printf("\t\tPaciente colocado na fila de atendimento.\n");
        Operacao *op = criarOperacao(1, elista->dados);
        push(pilha, op);
        return;
    }
    printf("\t\tPaciente não encontrado.\n");

}

void desenfileirarPaciente (Fila *fila, Stack *pilha) {

    if (fila->qtde == 0) {
        return;
    }

    EFila *paciente = dequeue(fila);
    if (paciente != NULL) {
        Operacao *op = criarOperacao(2, paciente->dados);
        push(pilha, op);
        printf("Paciente desesfileirado com sucesso.\n");
    }

}

void mostrarFila(Fila *fila) {

    EFila *atual = fila->head;
    while(atual != NULL) {
        mostrarDadosPaciente(atual->dados);
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
void desfazer(Stack *pilha, Fila *queue) {

    Operacao *op = pop(pilha);
    if (op != NULL) {
        if (op->acao == 1) {
            queue->tail = queue->tail->anterior;
            queue->tail->proximo = NULL;
            printf("\tAção desfeita com sucesso.\n");
            return;
        } else if (op->acao == 2) {
            EFila *novo = criaCelula(op->dados);
            novo->proximo = queue->head;
            queue->head->anterior = novo;
            queue->head = novo;
            printf("Ação desfeita com sucesso.\n");
            return;
        } else {
            printf("Não há mais ações para desfazer.\n");
            return;
        }
    }

}

// Carregar/Salvar

void leArquivo(Lista *lista) {

    FILE *f = fopen("registros", "rb");
    if (f == NULL) {
        return;
    }
    if (fread(&lista->qtde, sizeof(int), 1, f) != 1) {
        printf("Erro ao ler a quantidade de elementos.\n");
        fclose(f);
        return;
    }
    printf("Quantidade de elementos: %d\n", lista->qtde);
    for (int i = 0; i < lista->qtde; i++) {
        ELista *novo = inicializaELista(NULL);
        novo->dados = malloc(sizeof(Registro));
        novo->dados->entrada = malloc(sizeof(Data));
        fread(novo->dados->nome, sizeof(char), 51, f);
        fread(&novo->dados->idade, sizeof(int), 1, f);
        fread(novo->dados->rg, sizeof(char), 12, f);
        fread(novo->dados->entrada, sizeof(Data), 1, f);
        inserirLDE(lista, novo->dados);
    }
    fclose(f);
    return;

}

void escreveArquivo(Lista *lista) {

    FILE *f = fopen("registros", "wb");

    if (f == NULL) {
        return;
    }
    fwrite(&lista->qtde, sizeof(int), 1, f);

    ELista *atual = lista->inicio;
    while(atual != NULL) {
        fwrite(atual->dados->nome, sizeof(char), 51, f);
        fwrite(&atual->dados->idade, sizeof(int), 1, f);
        fwrite(atual->dados->rg, sizeof(char), 12, f);
        fwrite(atual->dados->entrada, sizeof(Data), 1, f);
        atual = atual->proximo;  
    }
    fclose(f);
    return;

}

void limpaBuffer() {

    int i;
    while ((i = getchar() != '\n' && i != EOF));

}