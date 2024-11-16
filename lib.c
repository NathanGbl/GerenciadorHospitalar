#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Geral

/** 
 * @brief Busca um paciente na lista de registros pelo RG
 * @param lista* Ponteiro para a lista de registros
 * @param rg[12] RG do paciente
 * @return Ponteiro para o elemento da lista que contém o paciente, ou NULL se não foi encontrado
 */
ELista *buscarPeloRg(Lista *lista, char rg[12]) {
    ELista *atual = lista->inicio;
    while (atual != NULL && strcmp(atual->dados->rg, rg)) {
        atual = atual->proximo;
    }
    return atual;
}

/** 
 * @brief Exibe os dados de um paciente
 * @param paciente* Ponteiro para o registro do paciente
 */
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

/** 
 * @brief Exibe os dados do paciente com uma formatação mais trabalhada
 * @param paciente* Ponteiro para o registro do paciente
 */
void mostrarDadosPaciente(Registro *paciente) {
    printf("===== Paciente =====\n");
    mostrarPaciente(paciente);
}

/** 
 * @brief Exibe o menu principal e lê a opção escolhida
 * @param opcao* Ponteiro para a opção escolhida
 */
void menu(int *opcao) {
    printf("Atendimento médico à sua disposição, o que gostaria?\n");
    printf("1. Cadastrar\n");
    printf("2. Atendimento\n");
    printf("3. Pesquisa\n");
    printf("4. Desfazer\n");
    printf("5. Carregar/Salvar\n");
    printf("6. Sobre\n");
    printf("0. Sair\n");
    printf("Opção: ");
    scanf("%d", opcao);
}

/** 
 * @brief Exibe o menu de cadastro e lê a opção escolhida
 * @param opcao* Ponteiro para a opção escolhida
 */
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

/** 
 * @brief Exibe o menu de atendimento e lê a opção escolhida
 * @param opcao* Ponteiro para a opção escolhida
 */
void menuAtendimento(int *opcao) {
    printf("\t1. Enfileirar paciente\n");
    printf("\t2. Desenfileirar paciente\n");
    printf("\t3. Mostrar fila\n");
    printf("\t4. Voltar\n");
    printf("\tOpção: ");
    scanf("%d", opcao);
}

/** 
 * @brief Exibe o menu de pesquisa e lê a opção escolhida
 * @param opcao* Ponteiro para a opção escolhida
 */
void menuPesquisa(int *opcao) {
    printf("\tMostrar registros ordenados por:\n");
    printf("\t\t1. Por ano\n");
    printf("\t\t2. Por mes\n");
    printf("\t\t3. Por dia\n");
    printf("\t\t4. Por idade\n");
    printf("\t\t5. Voltar\n");
    printf("Opção: ");
    scanf("%d", opcao);
}

/** 
 * @brief Exibe uma mensagem de confirmação e recebe a confirmação do usuário
 * @param confirm* Ponteiro para o char confirm
 * @param pilha* Ponteiro para a pilha de operações
 */
void menuDesfazer(char *confirm, Stack *pilha) {
    if (pilha->topo->acao == 1) {
        printf("\tDeseja reverter a ultima operacao de enqueue do paciente com RG: %s feita no atendimento?(s/n)\n", pilha->topo->dados->rg);
    } else if (pilha->topo->acao == 2) {
        printf("\tDeseja reverter a ultima operacao de dequeue do paciente com RG: %s feita no atendimento?(s/n)\n", pilha->topo->dados->rg);
    }
    printf("\tOpção: ");
    limpaBuffer();
    scanf("%c", confirm);
}

/** 
 * @brief Exibe os autores do projeto
 */
void menuSobre() {
    printf("\tAutores:\n");
    printf("\t\tNome: Nathan Gabriel da Fonseca Leite\n");
    printf("\t\tCiclo: Quarto\n");
    printf("\t\tCurso: Ciencia da Computacao\n");
    printf("\t\tDisciplina: Estrutura de Dados\n");
    printf("\t\tData: 14/11/2024\n");

    printf("\t\tNome: Raphael Garavati Erbert\n");
    printf("\t\tCiclo: Quarto\n");
    printf("\t\tCurso: Ciencia da Computacao\n");
    printf("\t\tDisciplina: Estrutura de Dados\n");
    printf("\t\tData: 14/11/2024\n");
}

// Estrutura de Dados

/** 
 * @brief Aloca memória para a LDE, coloca como NULL o ponteiro de inicio e como 0 a quantidade de elementos
 * @return Ponteiro para a lista de registros
 */
Lista *inicializaLista() {
    Lista *lista = malloc(sizeof(Lista));
    lista->inicio = NULL;
    lista->qtde = 0;
    return lista;
}

/** 
 * @brief Aloca memória para a ELista e coloca como NULL o ponteiro de próximo e coloca os dados fornecidos nos dados da ELista criada
 * @param dados* Ponteiro para o registro do paciente
 * @return Ponteiro para o elemento da lista
 */
ELista *inicializaELista(Registro *dados) {
    ELista *elista = malloc(sizeof(ELista));
    elista->proximo = NULL;
    elista->dados = dados;
    return elista;
}

/** 
 * @brief Insere no início da LDE
 * @param lista* Ponteiro para a lista de registros
 * @param dados* Ponteiro para o registro do paciente
 */
void inserirLDE(Lista *lista, Registro *dados) {
    ELista *nova = inicializaELista(dados);
    nova->proximo = lista->inicio;
    lista->inicio = nova;
    lista->qtde++;
}

/** 
 * @brief Insere no final da LDE
 * @param lista* Ponteiro para a lista de registros
 * @param novo* Ponteiro para o novo elemento a ser inserido
 */
void inserirFinalLDE(Lista *lista, ELista *novo) {
    if (lista->inicio == NULL) {
        lista->inicio = novo;
    } else {
        ELista *anterior = NULL;
        ELista *atual = lista->inicio;
        while (atual != NULL) {
            anterior = atual;
            atual = atual->proximo;
        }
        anterior->proximo = novo;
    }
    lista->qtde++;
}

/** 
 * @brief Remove um elemento da lista que tenha o RG igual ao fornecido
 * @param lista* Ponteiro para a lista de registros
 * @param rg[12] RG do paciente
 * @return 1 se o paciente foi removido, 0 caso contrário
 */
int removerLDE(Lista *lista, char rg[12]) {
    ELista *atual = lista->inicio;
    ELista *anterior = NULL;
    if (lista->qtde == 0) {
        return 0;
    } else {
        while (atual != NULL && strcmp(atual->dados->rg, rg)) {
            anterior = atual;
            atual = atual->proximo;
        }
        if (atual == NULL) {
            return 0;
        }
        if (anterior == NULL) {
            lista->inicio = atual->proximo;
        } else {
            anterior->proximo = atual->proximo;
        }
    }
    free(atual);
    lista->qtde--;
    return 1;
}

/** 
 * @brief Exibe todos os pacientes na lista
 * @param lista* Ponteiro para a LDE com os registros dos pacientes
 */
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
}

/** 
 * @brief Cria uma célula da fila com proximo e anterior como NULL e com os dados fornecidos
 * @param paciente* Ponteiro para o registro do paciente
 * @return Ponteiro para a EFila
 */
EFila *criaCelula(Registro *paciente) {
    EFila *efila = malloc(sizeof(EFila));
    efila->proximo = NULL;
    efila->anterior = NULL;
    efila->dados = paciente;
    return efila;
}

/** 
 * @brief Cria uma fila com head e tail como NULL e quantidade de elementos como 0
 * @return Ponteiro para a fila
 */
Fila *criaFila() {
    Fila *queue = malloc(sizeof(Fila));
    queue->head = NULL;
    queue->tail = NULL;
    queue->qtde = 0;
    return queue;
}

/** 
 * @brief Adiciona um paciente à fila
 * @param queue* Ponteiro para a fila
 * @param paciente* Ponteiro para o registro do paciente
 */
void enqueue(Fila *queue, Registro *paciente) {
    EFila *novo = criaCelula(paciente);
    if (queue->qtde == 0) {
        queue->head = novo;
        queue->tail = novo;
    } else {
        queue->tail->proximo = novo;
        novo->anterior = queue->tail;
        queue->tail = novo;
    }
    queue->qtde++;
}

/** 
 * @brief Remove um paciente da fila
 * @param queue* Ponteiro para a fila
 * @return Ponteiro para a célula removida da fila
 */
EFila *dequeue(Fila *queue) {
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
    temp->proximo = NULL;
    temp->anterior = NULL;
    return temp;
}

/** 
 * @brief Cria um vértice da árvore
 * @param dados* Ponteiro para o registro do paciente
 * @return Ponteiro para o vértice da árvore
 */
EABB *criaVertice(Registro *dados) {
    EABB* novo = malloc(sizeof(EABB));
    novo->filhoDir = NULL;
    novo->filhoEsq = NULL;
    novo->pai = NULL;
    novo->dados = dados;
    return novo;
}

/** 
 * @brief Cria uma árvore
 * @return Ponteiro para a árvore
 */
ABB *criaArvore() {
    ABB* arvore = malloc(sizeof(ABB));
    arvore->raiz = NULL;
    arvore->qtde = 0;
    return arvore;
}

/** 
 * @brief Libera a memória alocada para a árvore
 * @param vertice Ponteiro para o vértice da árvore
 */
void liberarArvore(EABB* vertice) {
    if (vertice != NULL) {
        liberarArvore(vertice->filhoEsq);
        liberarArvore(vertice->filhoDir);
        free(vertice);
    }
}

/** 
 * @brief Insere um paciente na árvore
 * @param arvore Ponteiro para a árvore
 * @param paciente* Ponteiro para o registro do paciente
 * @param modo Modo de inserção (1: ano, 2: mês, 3: dia, 4: idade)
 * @return 1 se o paciente foi inserido, 0 caso contrário
 */
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
            if (novoPaciente->dados->entrada->ano > anterior->dados->entrada->ano) {
                anterior->filhoDir = novoPaciente;
            } else {
                anterior->filhoEsq = novoPaciente;
            }
        } else if (modo == 2) {
            if (novoPaciente->dados->entrada->mes > anterior->dados->entrada->mes) {
                anterior->filhoDir = novoPaciente;
            } else {
                anterior->filhoEsq = novoPaciente;
            }
        } else if (modo == 3) {
            if (novoPaciente->dados->entrada->dia > anterior->dados->entrada->dia) {
                anterior->filhoDir = novoPaciente;
            } else {
                anterior->filhoEsq = novoPaciente;
            }
        } else if (modo == 4) {
            if (novoPaciente->dados->idade > anterior->dados->idade) {
                anterior->filhoDir = novoPaciente;
            } else {
                anterior->filhoEsq = novoPaciente;
            }
        }
    } else {
        arvore->raiz = novoPaciente;
    }
    arvore->qtde++;
    return 1;
}

/** 
 * @brief Imprime os dados dos pacientes em ordem
 * @param raiz* Ponteiro para um vértice da árvore
 */
void imprimeInOrdem(EABB *raiz) {
    if (raiz != NULL) {
        imprimeInOrdem(raiz->filhoEsq);
        mostrarDadosPaciente(raiz->dados);
        imprimeInOrdem(raiz->filhoDir);
    }
}

/** 
 * @brief Cria uma operação
 * @param acao Ação realizada (1: enqueue, 2: dequeue)
 * @param dados* Ponteiro para o registro do paciente
 * @return Ponteiro para a operação
 */
Operacao *criarOperacao(int acao, Registro *dados) {
    Operacao *op = malloc(sizeof(Operacao));
    op->proximo = NULL;
    op->acao = acao;
    op->dados = dados;
    return op;
}

/** 
 * @brief Cria uma pilha com o topo como NULL
 * @return Ponteiro para a pilha
 */
Stack *criarPilha() {
    Stack *pilha = malloc(sizeof(Stack));
    pilha->topo = NULL;
    return pilha;
}

/** 
 * @brief Adiciona uma operação à pilha
 * @param pilha* Ponteiro para a pilha
 * @param op* Ponteiro para a operação
 */
void push(Stack *pilha, Operacao *op) {
    op->proximo = pilha->topo;
    pilha->topo = op;
}

/** 
 * @brief Remove uma operação da pilha
 * @param pilha* Ponteiro para a pilha
 * @return Ponteiro para a operação removida
 */
Operacao *pop(Stack *pilha) {
    if (pilha->topo == NULL) {
        return NULL;
    }
    Operacao *temp = pilha->topo;
    pilha->topo = temp->proximo;
    return temp;
}

// Cadastrar

/** 
 * @brief Pede os dados necessários para criar um registro de paciente e cria o registro
 * @return Ponteiro para o registro do paciente
 */
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
    int ano = 1960 + rand() % 65;

    strcpy(novoPaciente->nome, nome);
    novoPaciente->idade = idade;
    strcpy(novoPaciente->rg, rg);
    novoPaciente->entrada->dia = dia;
    novoPaciente->entrada->mes = mes;
    novoPaciente->entrada->ano = ano;
    return novoPaciente;
}

/** 
 * @brief Cadastra um novo paciente na lista
 * @param lista* Ponteiro para a lista de registros
 * @return 1 se o paciente foi cadastrado com sucesso
 */
int cadastrarNovoPaciente(Lista *lista) {
    Registro *novoPaciente = criaRegistro();
    inserirLDE(lista, novoPaciente);
    return 1;
}

/**
 * @brief Consulta um paciente cadastrado na lista pelo RG.
 * @param lista* Ponteiro para a LDE que contenha os registros.
 */
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
}

/**
 * @brief Mostra a lista completa de pacientes.
 * @param lista* Ponteiro para a LDE que contenha os registros.
 */
void mostrarListaCompleta(Lista *lista) {
    mostrarLDE(lista);
}

/**
 * @brief Atualiza os dados de um paciente na lista com os dados fornecidos do novo registro.
 * @param lista* Ponteiro para a lista de registros.
 * @param novosDados* Ponteiro para os novos dados do paciente.
 */
void atualizarDadosPaciente(Lista *lista, Registro *novosDados) {
    char rg[12];
    printf("\t\tDigite o rg antigo do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);
    ELista *atual = buscarPeloRg(lista, rg);
    if (atual != NULL) {
        mostrarDadosPaciente(atual->dados);
        strcpy(atual->dados->nome, novosDados->nome);
        atual->dados->idade = novosDados->idade;
        strcpy(atual->dados->rg, novosDados->rg);
        printf("Dados do paciente atualizados com sucesso.\n");
        return;
    }
    printf("Paciente não encontrado.");
}

/**
 * @brief Remove um paciente da lista pelo RG.
 * @param lista* Ponteiro para a lista de registros.
 * @return 1 se o paciente foi removido, 0 caso contrário.
 */
int removerPaciente(Lista *lista) {
    char rg[12];
    printf("\tDigite o rg do paciente: ");
    limpaBuffer();
    scanf("%[^\n]", rg);
    return removerLDE(lista, rg);
}

/**
 * @brief Enfileira um paciente para a fila de atendimento.
 * @param fila* Ponteiro para a fila de atendimento.
 * @param lista* Ponteiro para a lista de registros.
 * @param pilha* Ponteiro para a pilha de operações.
 */
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

/**
 * @brief Desenfileira um paciente da fila de atendimento.
 * @param fila* Ponteiro para a fila de atendimento.
 * @param pilha* Ponteiro para a pilha de operações.
 */
void desenfileirarPaciente(Fila *fila, Stack *pilha) {
    if (fila->qtde == 0) {
        return;
    }

    EFila *paciente = dequeue(fila);
    if (paciente != NULL) {
        Operacao *op = criarOperacao(2, paciente->dados);
        push(pilha, op);
        printf("\tPaciente desesfileirado com sucesso.\n");
    }
}

/**
 * @brief Mostra todos os pacientes na fila de atendimento.
 * @param fila* Ponteiro para a fila de atendimento.
 */
void mostrarFila(Fila *fila) {
    EFila *atual = fila->head;
    while(atual != NULL) {
        mostrarDadosPaciente(atual->dados);
        atual = atual->proximo;
    }
    printf("\n");
}

/**
 * @brief Constroi a árvore diferenciando o ano e imprime in-ordem.
 * @param lista* Ponteiro para a lista de registros.
 */
void mostrarPorAno(Lista *lista) {
    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    while (atual != NULL) {
        inserirArvore(arvore, atual->dados, 1);
        atual = atual->proximo;
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);
}

/**
 * @brief Constroi a árvore diferenciando o mês e imprime in-ordem.
 * @param lista* Ponteiro para a lista de registros.
 */
void mostrarPorMes(Lista *lista) {
    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    while (atual != NULL) {
        inserirArvore(arvore, atual->dados, 2);
        atual = atual->proximo;
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);
}

/**
 * @brief Constroi a árvore diferenciando o dia e imprime in-ordem.
 * @param lista* Ponteiro para a lista de registros.
 */
void mostrarPorDia(Lista *lista) {
    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    while (atual != NULL) {
        inserirArvore(arvore, atual->dados, 3);
        atual = atual->proximo;
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);
}

/**
 * @brief Constroi a árvore diferenciando a idade e imprime in-ordem.
 * @param lista* Ponteiro para a lista de registros.
 */
void mostrarPorIdade(Lista *lista) {
    ABB *arvore = criaArvore();
    ELista *atual = lista->inicio;
    while (atual != NULL) {
        inserirArvore(arvore, atual->dados, 4);
        atual = atual->proximo;
    }
    imprimeInOrdem(arvore->raiz);
    liberarArvore(arvore->raiz);
}

/**
 * @brief Desfaz a última operação de enfileiramento(1) ou desenfileiramento(2).
 * @param pilha* Ponteiro para a pilha de operações.
 * @param queue* Ponteiro para a fila de atendimento.
 */
void desfazer(Stack *pilha, Fila *queue) {
    Operacao *op = pop(pilha);
    if (op != NULL) {
        if (op->acao == 1) {
            queue->tail = queue->tail->anterior;
            if (queue->tail != NULL) {
                queue->tail->proximo = NULL;
            } else {
                queue->head = NULL;
            }
            printf("\tAção desfeita com sucesso.\n");
            return;
        } else if (op->acao == 2) {
            EFila *novo = criaCelula(op->dados);
            novo->proximo = queue->head;
            if (queue->head != NULL) {
                queue->head->anterior = novo;
            }
            queue->head = novo;
            printf("\tAção desfeita com sucesso.\n");
            return;
        } else {
            printf("\tNão há mais ações para desfazer.\n");
            return;
        }
    }
}

/**
 * @brief Lê os dados de um arquivo binário e os insere no final da LDE para manter a ordem.
 * @param lista* Ponteiro para a lista de registros.
 */
void leArquivo(Lista *lista) {
    FILE *file = fopen("registros", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    Registro temp;

    while (fread(&temp, sizeof(Registro) - sizeof(Data*), 1, file) == 1) {
        ELista *novo = malloc(sizeof(ELista));
        novo->dados = malloc(sizeof(Registro));
        *novo->dados = temp;
        novo->dados->entrada = malloc(sizeof(Data));

        fread(novo->dados->entrada, sizeof(Data), 1, file);

        inserirFinalLDE(lista, novo);
    }

    fclose(file);
}

/**
 * @brief Escreve os dados da lista em um arquivo binário.
 * @param lista* Ponteiro para a lista de registros.
 */
void escreveArquivo(Lista *lista) {
    FILE *file = fopen("registros", "wb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    ELista *atual = lista->inicio;
    while (atual != NULL) {
        fwrite(atual->dados, sizeof(Registro) - sizeof(Data*), 1, file);

        fwrite(atual->dados->entrada, sizeof(Data), 1, file);

        atual = atual->proximo;
    }
    fclose(file);
}

/**
 * @brief Recebe a quebra de linha para não atrapalhar os próximos scanf.
 */
void limpaBuffer() {

    int i;
    while ((i = getchar() != '\n' && i != EOF));

}