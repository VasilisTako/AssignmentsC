#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int dato;
    struct n *prev;
    struct n *next;
}nodo;
typedef nodo *nPtr;

typedef struct {
    struct n *head;
    struct n *tail;
}estremi;

void inizializza_lista(estremi *lista);
void insert(estremi *lista, int valore);
void stampa_inverso(estremi *lista);

int main () {

    int N;
    scanf("%d", &N);

    int valore;
    estremi lista;
    inizializza_lista(&lista);

    for(int i = 0; i < N; i++){
        scanf("%d", &valore);
        insert(&lista, valore);
    }

    stampa_inverso(&lista);
    return 0;
}

void inizializza_lista(estremi *lista){
    lista->head = NULL;
    lista->tail = NULL;
}


void insert(estremi *lista, int valore){

    nPtr nuovo = malloc(sizeof(nodo));
    nuovo->dato = valore;
    nuovo->next = NULL;

    if(lista->tail == NULL){
        nuovo->prev = NULL;
        lista->tail = nuovo;
    }
    else{
        nuovo->prev = lista->tail;
        lista->tail->next = nuovo;
        lista->tail = nuovo;
    }
}

void stampa_inverso(estremi *lista){

    nPtr scorri = lista->tail;

    while(scorri != NULL){
        printf("%d\n", scorri->dato);
        scorri = scorri->prev;
    }
    //printf("\n");
}
