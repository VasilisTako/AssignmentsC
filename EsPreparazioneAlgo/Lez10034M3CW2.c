#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct n{
    int val;
    struct n *next;
}nodo;
typedef nodo* nPtr;

void inserisci(nPtr *lista, int valore);
int media (nPtr lista);
void elimina(nPtr *lista, int m);
void print_list(nPtr lista);

int main () {

    int N;
    scanf("%d", &N);

    nPtr sequenza = NULL;

    int valore;

    for(int i = 0; i < N; i++){
        scanf("%d", &valore);
        inserisci(&sequenza, valore);
    }
    int m = media(sequenza);
    printf("%d\n", m);
    print_list(sequenza);
    elimina(&sequenza, m);
    print_list(sequenza);


    free(sequenza);

    return 0;
}


void inserisci(nPtr *lista, int valore){

    nPtr nuovo = malloc(sizeof(nodo));
    nuovo->val = valore;
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

int media(nPtr lista){
    int sum = 0;
    int i;
    for(i = 0; lista != NULL; i++){
        sum += lista->val;
        lista = lista->next;
    }
    return ceil(sum/i);

}

void elimina(nPtr* lista, int m){

    if(*lista != NULL){
        if((*lista)->val <= m){
            nPtr tmp = *lista;
            *lista = tmp->next;
            free(tmp);
            return elimina(&(*lista), m);
        }
        else
            return elimina(&(*lista)->next, m);
    }
}


void print_list(nPtr lista){
    while(lista != NULL){
        printf("%d ", lista->val);
        lista = lista->next;
    }
    printf("\n");
}
