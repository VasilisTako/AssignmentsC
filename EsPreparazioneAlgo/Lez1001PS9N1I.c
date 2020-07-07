#include <stdio.h>
#include <stdlib.h>
#define P 999149


typedef struct n{
    int val;
    struct n* next;
}nodo;
typedef nodo* nPtr;


void insert(nPtr* lista, int val);
void print_tab(nPtr* array, int dim);
int h(int val, int n, int a, int b);        //Puo' essere fatta nella define
int conflitti(nPtr *lista, int dim);
int length(nPtr* lista, int dim);

int main () {
    int N, a, b;
    scanf("%d", &N);

    nPtr *array = (nPtr*)malloc(2*N * sizeof(nPtr));
    scanf("%d", &a);
    scanf("%d", &b);
    int val;
    int fun;

    for(int i = 0; i < N; i++){
        scanf("%d", &val);
        fun = h(val, N, a, b);
        printf("h(%d) = %d\n", val, fun);
        insert(&array[fun], val);
    }
    print_tab(array, 2*N); //Stampa la tabella
    printf("%d\n", conflitti(array, 2*N));

    free(array);
    return 0;
}


int h(int val, int n, int a, int b){
    return (((a*val+b) % P) % (2*n));
}

void insert(nPtr* lista, int val){

    nPtr nuovo = (nPtr)malloc(sizeof(nodo));
    nuovo->val = val;
    nuovo->next = NULL;

    nPtr precedente = NULL;
    nPtr corrente = *lista;
    while(corrente != NULL){
        precedente = corrente;
        corrente = corrente->next;
    }
    if(precedente == NULL){
        nuovo->next = *lista;
        *lista = nuovo;
    }
    else{
        precedente->next = nuovo;
        nuovo->next = corrente;
    }
}

int conflitti(nPtr *lista, int dim){

    int max = 0;
    int parziale = 0;

    int counter = 0;
    nPtr scorri;
    for(int i = 0; i < dim; i++){
        scorri = lista[i];
        parziale = 0;
        while(scorri != NULL){
            parziale++;
            if(scorri->next != NULL)
                counter++;
            scorri = scorri->next;
        }
        if(parziale > max)
            max = parziale;
    }
    printf("%d\n", max);
    return counter;
}




void print_tab(nPtr* array, int dim){

    nPtr scorri;
    for(int i = 0; i < dim; i++){
        scorri = array[i];
        printf("%d-> ", i);

        while(scorri != NULL){
            printf("%d-> ", scorri->val);
            scorri = scorri->next;
        }
        printf("NULL\n");
    }
}
