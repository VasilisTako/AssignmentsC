#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int x;
    struct n *next;
}nodo;
typedef nodo *nPtr;

void insert(nPtr *testa, int valore);
int search(nPtr *testa, int valore);
void print_list(nPtr lista);

int main () {

    int N;
    scanf("%d",&N);
    nPtr lista = NULL;
    int valore;
    for(int i = 0; i < N; i++){
        scanf("%d", &valore);
        insert(&lista, valore);
    }

    int controllo = 0;
    while(controllo >= 0){
        scanf("%d", &valore);
        controllo = search(&lista, valore);
        printf("%d\n", controllo);

    }
    return 0;

}

void insert(nPtr *testa, int valore){

    nPtr nuovo = malloc(sizeof(nodo));
    nuovo->x = valore;
    nuovo->next = NULL;

    nPtr precedente = NULL;
    nPtr corrente = *testa;
    while(corrente != NULL){
        precedente = corrente;
        corrente = corrente->next;
    }
    if(precedente == NULL){
        nuovo->next = *testa;
        *testa = nuovo;
    }
    else{
        precedente->next = nuovo;
        nuovo->next = NULL;
    }
}

int search(nPtr *testa, int valore){

    nPtr precedente = NULL;
    nPtr corrente = *testa;
    nPtr swap;
    for(int i = 0; corrente != NULL; i++){

        if(corrente->x == valore){
            if(precedente == NULL)
                return i;
            swap = corrente;
            precedente->next = corrente->next;
            //free(corrente);
            swap->next = *testa;
            *testa = swap;
            return i;
        }
        precedente = corrente;
        corrente = corrente->next;
    }
    return -1;
}

void print_list(nPtr lista){
    while(lista != NULL){
        printf("%d\n", lista->x);
        lista = lista->next;
    }
    printf("\n\n");
}
