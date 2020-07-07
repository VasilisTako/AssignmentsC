#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int key;
    struct n* right;
    struct n* left;
}nodo;
typedef nodo* nPtr;

nPtr inizializza (int val);
nPtr insert(nPtr albero, int key);
int path(nPtr albero, int key);
int compare(nPtr first_tree, nPtr second_tree, int k);

int main() {

    int N, k, val;
    scanf("%d %d", &N, &k);

    nPtr first_tree = NULL;
    scanf("%d", &val);
    first_tree = inizializza(val);
    nPtr next = first_tree;
    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        next = insert(next, val);
    }
    nPtr snd_tree = NULL;
    scanf("%d", &val);
    snd_tree = inizializza(val);
    next = NULL;
    next = snd_tree;
    for(int i = 0; i < N-1; i++){
        scanf("%d", &val);
        next = insert(next, val);
    }
    printf("%d\n", compare(first_tree, snd_tree, k));

    free(first_tree);
    free(snd_tree);
    return 0;
}

nPtr inizializza (int val){
    nPtr nuovo = (nPtr)malloc(sizeof(nodo));
    nuovo->key = val;
    nuovo->left = NULL;
    nuovo->right =  NULL;

    return nuovo;
}

nPtr insert(nPtr albero, int key){
    if(albero == NULL){
        nPtr nuovo = (nPtr)malloc(sizeof(nodo));
        nuovo->key = key;
        nuovo->left = NULL;
        nuovo->right =  NULL;
        return nuovo;
    }
    if(albero->key > key)
        albero->left = insert(albero->left, key);
    else
        albero->right = insert(albero->right, key);

    return albero;
}

int path(nPtr albero, int key){
    if(albero->key == key)
        return 0;
    if(albero->key > key)
        return albero->key + path(albero->left, key);
    else
        return albero->key + path(albero->right, key);
}

int compare(nPtr first_tree, nPtr second_tree, int k){
    if(path(first_tree, k) == path(second_tree, k))
        return 1;
    return 0;
}
