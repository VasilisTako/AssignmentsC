#include <stdio.h>
#include <stdlib.h>


typedef struct n{
    int dato;
    struct n* left;
    struct n* right;
}nodo;
typedef nodo* nPtr;

nPtr inizializza(int val);
nPtr insert_rec(nPtr albero, int val);
int search (nPtr albero, int val);

int main () {

    int N, val;
    scanf("%d", &N);

    nPtr albero = NULL;
    scanf("%d", &val);
    albero = inizializza(val);

    nPtr root = albero;
    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        root = insert_rec(root, val);
    }
    scanf("%d", &val);
    int res;
    while(val >= 0){
        res = search(albero, val);
        (res < 0) ? printf("NO\n") : printf("%d\n", res);
        scanf("%d", &val);
    }
    free(albero);
    return 0;
}

nPtr inizializza(int val){

    nPtr first_value = (nPtr)malloc(sizeof(nodo));
    first_value->dato = val;
    first_value->left = NULL;
    first_value->right = NULL;
    return first_value;
}

nPtr insert_rec(nPtr albero, int val){

    if(albero == NULL){
        nPtr nuovo = (nPtr)malloc(sizeof(nodo));
        nuovo->dato = val;
        nuovo->left = NULL;
        nuovo->right = NULL;
        return nuovo;
    }
    if(albero->dato < val)
        albero->right = insert_rec(albero->right, val);
    else
        albero->left = insert_rec(albero->left, val);

    return albero;
}

int search(nPtr albero, int key){
    if(albero == NULL)
        return -1;
    if(albero->dato == key)
        return 0;
    int deep = -1;
    if(albero->dato > key)
        deep = search(albero->left, key);
    else
        deep = search(albero->right, key);

    if(deep >= 0)
        return 1 + deep;

    else
        return -1;
}
