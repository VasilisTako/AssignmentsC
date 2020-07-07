#include <stdio.h>
#include <stdlib.h>

typedef struct n {
    int key;
    struct n* left;
    struct n* right;
}nodo;
typedef nodo* nPtr;

nPtr inizializza(int key);
nPtr insert(nPtr albero, int key);
void print(nPtr albero);

int main () {

    int N, val;
    scanf("%d", &N);
    nPtr albero = NULL;
    scanf("%d", &val);
    albero = inizializza(val);
    nPtr next = albero;

    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        next = insert(next, val);
    }
    print(albero);
    free(albero);

    return 0;
}


nPtr inizializza(int key){
    nPtr nuovo = (nPtr)malloc(sizeof(nodo));
    nuovo->key = key;
    nuovo->left = NULL;
    nuovo->right = NULL;
    return nuovo;
}

nPtr insert(nPtr albero, int key){
    if(albero == NULL){
        nPtr nuovo = (nPtr)malloc(sizeof(nodo));
        nuovo->key = key;
        nuovo->left = NULL;
        nuovo->right = NULL;
        return nuovo;
    }
    if(albero->key > key)
        albero->left = insert(albero->left, key);
    else
        albero->right = insert(albero->right, key);
    return albero;
}

void print(nPtr albero){
    if(albero->left != NULL)
        print(albero->left);
    printf("%d\n", albero->key);
    if(albero->right != NULL)
        print(albero->right);
}
