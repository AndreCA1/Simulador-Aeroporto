#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//1° iteração serão pousados dois e decolado um
//2° iteração serão decolados três 
//3° iteração serão pousados dois e decolado um
//4° iteração serão decolados três 
//Assim por diante, exeto se um avião estiver na primeira posição da fila de pouso com 1 de combustivel, nesse caso:
//n° iteração serão pousados dois aviões como de costume e um na pista 3
//Vc so irá descobir que o avião caiu na hora que ele sair da fila, caso tenha caido vai pro proximo

int IdInicial = 0;
//Para gerar de 0 a 3 é preciso colocar 4 no rand()
#define avioesmax 4
#define combustivelmax 20

typedef struct {
    int id, combustivel;
} TipoAviao;

typedef struct Celula * apontador;

typedef struct Celula{
    TipoAviao item;
    apontador prox;
} Celula;

typedef struct {
    apontador primeiro, ultimo;
    int tam;
} TipoFila;

void criaFilaVazia(TipoFila *Fila){
    Fila->primeiro = (apontador) malloc(sizeof(Celula));
    Fila->ultimo = (apontador) malloc(sizeof(Celula));

    if(Fila->primeiro == NULL || Fila->ultimo == NULL){
        printf("\nErro ao alocar memória!");
        EXIT_FAILURE;
    }
    Fila->primeiro = NULL;
    Fila->ultimo = Fila->primeiro;
    Fila->tam = 0;
}

void Insere(TipoFila *Fila, TipoAviao aviao){
    apontador aux = (apontador) malloc(sizeof(Celula));

    if(aux == NULL){
        printf("\nErro ao alocar memória!");
        EXIT_FAILURE;
    }

    aux->item = aviao;
    aux->prox = NULL;

    if(Fila->primeiro != NULL){
        Fila->ultimo->prox = aux;
        Fila->ultimo = aux;
        Fila->tam++;
    } else{
        Fila->primeiro = aux;
        Fila->ultimo = Fila->primeiro;
        Fila->tam++;
    }
}

void Retira(TipoFila *Fila, TipoAviao *aviao){
    *aviao = Fila->primeiro->item;
    Fila->primeiro = Fila->primeiro->prox;
    Fila->tam--;
}

void geraAvioes(TipoFila *pouso1, TipoFila *pouso2, TipoFila *pouso3, TipoFila *pouso4, TipoFila *decola1, TipoFila *decola2, TipoFila *decola3){
    TipoAviao aviao;

    //Gera avioes pouso
    int qnt = rand() % avioesmax;

    for(int i = 0; i < qnt; i++){
        aviao.id = IdInicial + 1;
        aviao.combustivel = (rand() % combustivelmax) + 1;

        //Verifica qual a menor fila e insere nela
        if((pouso1->tam <= pouso2->tam) && (pouso1->tam <= pouso3->tam) && (pouso1->tam <= pouso4->tam)){
            Insere(pouso1, aviao);
        } else if((pouso2->tam < pouso1->tam) && (pouso2->tam <= pouso3->tam) && (pouso2->tam <= pouso4->tam)){
            Insere(pouso2, aviao);
        } else if((pouso3->tam < pouso1->tam) && (pouso3->tam <= pouso4->tam)){
            Insere(pouso3, aviao);
        } else {
            Insere(pouso4, aviao);
        }
        //Acrescenta 1 a variavel ID
        IdInicial++;  
    }

    //Gera avioes decolagem
    qnt = rand() % avioesmax;

    for(int i = 0; i < qnt; i++){
        aviao.id = IdInicial + 1;
        aviao.combustivel = 20;

        //Verifica qual a menor fila e insere nela
        if((decola1->tam <= decola2->tam) && (decola1->tam <= decola3->tam)){
            Insere(decola1, aviao);
        } else if((decola2->tam <= decola3->tam)){
            Insere(decola2, aviao);
        } else {
            Insere(decola3, aviao);
        }
        //Acrescenta 1 a variavel ID
        IdInicial++;  
    }
}

void LeFilas(TipoFila pouso1, TipoFila pouso2, TipoFila pouso3, TipoFila pouso4, TipoFila decola1, TipoFila decola2, TipoFila decola3){
    apontador aviao;

    aviao = pouso1.primeiro;
    printf("\nFILAS DE POUSO\n\nFila 1(%d aviões):\n\n", pouso1.tam);
    for (int i = 0; i < pouso1.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }

    aviao = pouso2.primeiro;
    printf("\nFila 2(%d aviões):\n\n", pouso2.tam);
    for (int i = 0; i < pouso2.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }
    
    aviao = pouso3.primeiro;
    printf("\nFila 3(%d aviões):\n\n", pouso3.tam);
    for (int i = 0; i < pouso3.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }

    aviao = pouso4.primeiro;
    printf("\nFila 4(%d aviões):\n\n", pouso4.tam);
    for (int i = 0; i < pouso4.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }

    aviao = decola1.primeiro;
    printf("\nFILAS DE DECOLAGEM\n\nFila 1(%d aviões):\n\n", pouso4.tam);
    for (int i = 0; i < decola1.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }

    aviao = decola2.primeiro;
    printf("\nFila 2(%d aviões):\n\n", pouso4.tam);
    for (int i = 0; i < decola2.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }

    aviao = decola3.primeiro;
    printf("\nFila 3(%d aviões):\n\n", pouso4.tam);
    for (int i = 0; i < decola3.tam; i++){
        printf("%d\t%d\n", aviao->item.id, aviao->item.combustivel);
        aviao = aviao->prox;
    }
}

int main(){
    srand(time(NULL));
    //Fila de pouso 1 e 2 para a pista 1 e filas 3 e 4 para a pista 2
    TipoFila pouso1, pouso2, pouso3, pouso4;
    //Uma fila pára cada pista de decolagem
    TipoFila decola1, decola2, decola3;

    TipoAviao aviao;

    //Inicia Filas Vazias
    criaFilaVazia(&pouso1);
    criaFilaVazia(&pouso2);
    criaFilaVazia(&pouso3);
    criaFilaVazia(&pouso4);
    criaFilaVazia(&decola1);
    criaFilaVazia(&decola2);
    criaFilaVazia(&decola3);

    //
    while(1){
        LeFilas(pouso1,pouso2,pouso3,pouso4,decola1,decola2,decola3);
        printf("Pressione qualquer tecla para avançar uma unidade de tempo\n");
        getchar();
        geraAvioes(&pouso1,&pouso2,&pouso3,&pouso4,&decola1,&decola2,&decola3);
    }
    return 0;
}