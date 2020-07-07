#include <stdio.h>
#include <stdlib.h>

typedef struct n{

    int val;
    struct n *next;
} nodo;
typedef nodo* nPtr;


nPtr create_list(int first_val);
nPtr inserimento(nPtr precedenti, int val);
void print(nPtr sequenza);

int main (){

    int N;
    scanf("%d", &N);
    nPtr sequenza = NULL;
    int val;
    scanf("%d", &val);
    sequenza = create_list(val);
    nPtr next = sequenza;

    for(int i = 0; i < N - 1; i++){
        scanf("%d", &val);
        next = inserimento(next, val);
    }
    print(sequenza);

    return 0;
}

nPtr create_list(int first_val){

    nPtr nuovo = (nPtr)malloc(sizeof(nodo));
    nuovo->val = first_val;
    nuovo->next = NULL;
    return nuovo;
}

nPtr inserimento(nPtr precedenti, int val){
    precedenti->next = (nPtr)malloc(sizeof(nodo));
    precedenti->next->val = val;
    precedenti->next->next = NULL;
    return precedenti->next;
}


void print(nPtr sequenza){

    if(sequenza == NULL)
        return;

    print(sequenza->next);
    printf("%d\n", sequenza->val);
}
