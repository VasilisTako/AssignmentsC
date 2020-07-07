#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int key;
    struct n* left;
    struct n* center;
    struct n* right;
}nodo;
typedef nodo* nPtr;

nPtr initialize (int val);
nPtr insert(nPtr next, int key);
int count(nPtr albero);

int main () {

    int N, val;
    scanf("%d", &N);

    nPtr albero = NULL;
    scanf("%d", &val);
    albero = initialize(val);
    nPtr append = albero;

    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        append = insert(append, val);
    }
    printf("%d\n", count(albero));
    free(albero);
    return 0;
}

nPtr initialize (int val){
    nPtr nuovo = (nPtr)malloc(sizeof(nodo));
    nuovo->key = val;
    nuovo->center = NULL;
    nuovo->left = NULL;
    nuovo->right = NULL;

    return nuovo;
}

nPtr insert(nPtr albero, int key){

    if(albero == NULL){
        nPtr nuovo = (nPtr)malloc(sizeof(nodo));
        nuovo->key = key;
        nuovo->center = NULL;
        nuovo->left = NULL;
        nuovo->right = NULL;
        return nuovo;
    }

    if(key % albero->key == 0)
        albero->center = insert(albero->center, key);
    else if(albero->key > key)
        albero->left = insert(albero->left, key);
    else
        albero->right = insert(albero->right, key);

    return albero;
}

int count(nPtr albero){

    if(albero == NULL)
        return 0;
    if(albero->left != NULL && albero->center != NULL && albero->right != NULL)
        return 1 + count(albero->left) + count(albero->center) + count(albero->right);
    else
        return count(albero->left) + count(albero->center) + count(albero->right);
}
