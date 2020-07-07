#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int val;
    struct n* next;
}nodo;
typedef nodo* nPtr;



nPtr inizializza (int first_val);
nPtr insert(nPtr coda, int x);
void sum(nPtr *lista);
int rec_sum(nPtr lista);
void print(nPtr lista);

int main () {

    int N;
    scanf("%d", &N);
    nPtr lista = NULL;

    int val;
    scanf("%d", &val);
    lista = inizializza(val);
    nPtr coda = lista;
    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        coda = insert(coda, val);
    }
    print(lista);
    sum(&lista);
    print(lista);

    free(coda);
    free(lista);
    return 0;
}

nPtr inizializza (int first_val){
    nPtr nuovo = malloc(sizeof(nodo));
    nuovo->val = first_val;
    nuovo->next = NULL;
    return nuovo;
}

nPtr insert(nPtr coda, int x){
    coda->next = malloc(sizeof(nodo));
    coda->next->val = x;
    coda->next->next = NULL;
    return coda->next;
}

void sum(nPtr *lista){
    nPtr scorri = *lista;

    while(scorri != NULL){
        scorri->val = rec_sum(scorri);
        scorri = scorri->next;
    }
}

int rec_sum(nPtr lista){

    if(lista->next == NULL)
        return 0;
    return lista->next->val + rec_sum(lista->next);
}


void print(nPtr lista){
    while(lista != NULL){
        printf("%d ", lista->val);
        lista = lista->next;
    }
    printf("\n");
}
