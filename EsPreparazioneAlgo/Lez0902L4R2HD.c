#include <stdio.h>
#include <stdlib.h>

typedef struct n{
    int key;
    struct n* left;
    struct n* right;
}nodo;
typedef nodo* nPtr;

int n_seq();
nPtr inizializza(int first_val);
nPtr insert(nPtr albero, int valore);
int height (nPtr albero);

int main () {

    int N, val;
    if((N = n_seq()) < 0){
        printf("%d\n", N);
        return -1;
    }
    nPtr albero = NULL;
    scanf("%d", &val);
    albero = inizializza(val);
    nPtr root = albero;

    for (int i = 0; i < N-1; ++i) {
        scanf("%d", &val);
        root = insert(root, val);
    }
    printf("%d\n", height(albero));
    free(albero);
    return 0;
}

int n_seq(){
    int N;
    scanf("%d", &N);
    if(N == 0)
        return -1;
    else
        return N;

}

nPtr inizializza(int first_val){
    nPtr primo = malloc(sizeof(nodo));
    primo->key = first_val;
    primo->left = NULL;
    primo->right = NULL;
    return primo;
}

nPtr insert(nPtr albero, int valore){
    if(albero == NULL){
        nPtr nuovo = malloc(sizeof(nodo));
        nuovo->key = valore;
        nuovo->right = NULL;
        nuovo->left = NULL;
        return nuovo;
    }
    if(albero->key < valore)
        albero->right = insert(albero->right, valore);
    else
        albero->left = insert(albero->left, valore);

    return albero;
}

int height (nPtr albero){
    if(albero == NULL)
        return 0;
    int h_sx = height(albero->left);
    int h_dx = height(albero->right);
    return 1+((h_sx > h_dx) ? h_sx : h_dx);
}