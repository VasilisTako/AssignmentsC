#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define DIM_MAX 101

typedef struct n{
    char* paziente;
    struct n* next;
    struct n* prev;
}nodo;

typedef struct {
    struct n* head;
    struct n* tail;
    int counter;
}estremi;


void inizializza (estremi* lista){

    lista->head = NULL;
    lista->tail = NULL;
    lista->counter = 0;
}

void enqueue(estremi* lista, char* nome){

    nodo* nuovo = (nodo*)malloc(sizeof(nodo));
    nuovo->paziente = (char*)malloc(DIM_MAX * sizeof(char));
    strcpy(nuovo->paziente, nome);
    nuovo->next = NULL;

    if(lista->head == NULL && lista->tail == NULL){
        nuovo->prev = NULL;
        lista->head = nuovo;
        lista->tail = nuovo;
    }
    else{
        nuovo->prev = lista->tail;
        lista->tail->next = nuovo;
        lista->tail = nuovo;
    }
    lista->counter++;
}

void dequeue(estremi* lista){

    nodo* delete = lista->head;
    lista->counter--;
    if(delete->next == NULL)
        inizializza(lista);
    else
        lista->head = delete->next;
    free(delete);
}

void print(estremi* lista){

    nodo* scorri = lista->head;
    while(scorri != NULL){
        printf("%s\n", scorri->paziente);
        scorri = scorri->next;
    }
}

void swap (nodo* a, nodo* b){

    char* tmp = malloc(101 * sizeof(char));
    strcpy(tmp, a->paziente);
    strcpy(a->paziente, b->paziente);
    strcpy(b->paziente, tmp);
}

void sort(estremi* lista){

    if(lista->counter < 2)
        return;
    nodo* min;

    for(nodo* i = lista->head; i->next != NULL; i = i->next){
        min = i;
        for(nodo* j = i->next; j != NULL; j = j->next){
            if(strcmp(min->paziente, j->paziente) > 0)
                min = j;
        }
        swap(i, min);
    }
}


int main () {

    estremi lista;
    inizializza(&lista);
    int choice;
    char paziente[101];
    scanf("%d", &choice);

    while(choice > 0){
        if(choice == 1){
            scanf("%s", paziente);
            enqueue(&lista,paziente);
        }
        else if(choice == 2){
            dequeue(&lista);
        }
        scanf("%d", &choice);
    }
    if(lista.head != NULL){
        //print(&lista);
        sort(&lista);
        print(&lista);
    }
    printf("$\n");
    free(lista.head);
    return 0;
}