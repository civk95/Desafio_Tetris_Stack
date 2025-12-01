#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// definição da struct
struct Peca {
    char nome;      
    int id;         
};

// constantes para configuração do sistema
#define TAMANHO_FILA 5
#define TIPOS_PECAS 4

// variáveis globais para a fila circular
struct Peca fila[TAMANHO_FILA];
int frente = 0;     
int tras = 0;       
int contador = 0;   
int proximoId = 0;  

// protótipos das funções
void inicializarFila();
struct Peca gerarPeca();
void exibirFila();
void jogarPeca();
void inserirPeca();
void mostrarMenu();

int main() {
    int opcao;
    
    // inicializa o gerador de números aleatórios
    srand(time(NULL));
    
    printf("=== TETRIS STACK - SISTEMA DE FILA DE PECAS ===\n");
    printf("Desenvolvido por ByteBros para ensino de logica\n\n");
    
    // inicializa a fila com peças iniciais
    inicializarFila();
    
    do {
        exibirFila();
        mostrarMenu();
        
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                jogarPeca();
                break;
            case 2:
                inserirPeca();
                break;
            case 0:
                printf("Saindo do Tetris Stack... Ate a proxima!\n");
                break;
            default:
                printf("Opcao invalida! Tente 1, 2 ou 0.\n");
        }
        
        printf("\n");
    } while(opcao != 0);
    
    return 0;
}

// função para inicializar a fila com peças iniciais
void inicializarFila() {
    printf("Inicializando fila com pecas iniciais...\n");
    
    for(int i = 0; i < TAMANHO_FILA; i++) {
        fila[tras] = gerarPeca();
        tras = (tras + 1) % TAMANHO_FILA;
        contador++;
    }
    
    printf("Fila inicializada com %d pecas!\n", contador);
}

// função para gerar uma nova peça aleatória
struct Peca gerarPeca() {
    struct Peca novaPeca;
    
    // tipos de peças disponíveis
    char tipos[] = {'I', 'O', 'T', 'L'};
    
    // gera um tipo aleatório
    novaPeca.nome = tipos[rand() % TIPOS_PECAS];
    
    // atribui um ID único e incrementa o contador
    novaPeca.id = proximoId++;
    
    return novaPeca;
}

// função para exibir o estado atual da fila
void exibirFila() {
    printf("=== FILA DE PECAS FUTURAS ===\n");
    
    if(contador == 0) {
        printf("Fila vazia! Nenhuma peca disponivel.\n");
        return;
    }
    
    printf("Pecas na fila (%d/%d):\n", contador, TAMANHO_FILA);
    
    // percorre a fila circular exibindo todas as peças
    int indice = frente;
    for(int i = 0; i < contador; i++) {
        printf("[%c %d] ", fila[indice].nome, fila[indice].id);
        indice = (indice + 1) % TAMANHO_FILA;
    }
    printf("\n");
    
    // mostra qual peça está na frente (próxima a ser jogada)
    printf("Proxima peca: [%c %d]\n", fila[frente].nome, fila[frente].id);
}

// função para mostrar o menu de opções
void mostrarMenu() {
    printf("\n=== OPCOES DE ACAO ===\n");
    printf("1 - Jogar peca (dequeue)\n");
    printf("2 - Inserir nova peca (enqueue)\n");
    printf("0 - Sair\n");
}

// função para jogar a peça da frente (remover da fila)
void jogarPeca() {
    if(contador == 0) {
        printf("ERRO: Fila vazia! Nao ha pecas para jogar.\n");
        return;
    }
    
    struct Peca pecaJogada = fila[frente];
    
    printf("Jogando peca: [%c %d]\n", pecaJogada.nome, pecaJogada.id);
    
    // remove a peça da frente (avança o índice da frente)
    frente = (frente + 1) % TAMANHO_FILA;
    contador--;
    
    printf("Peca jogada com sucesso! Pecas restantes: %d\n", contador);
}

// função para inserir uma nova peça no final da fila
void inserirPeca() {
    if(contador >= TAMANHO_FILA) {
        printf("ERRO: Fila cheia! Capacidade maxima de %d pecas atingida.\n", TAMANHO_FILA);
        printf("Jogue algumas pecas para liberar espaco.\n");
        return;
    }
    
    // gera uma nova peça
    struct Peca novaPeca = gerarPeca();
    
    printf("Inserindo nova peca: [%c %d]\n", novaPeca.nome, novaPeca.id);
    
    // adiciona a nova peça no final da fila
    fila[tras] = novaPeca;
    tras = (tras + 1) % TAMANHO_FILA;
    contador++;
    
    printf("Nova peca inserida com sucesso! Total de pecas: %d\n", contador);
}