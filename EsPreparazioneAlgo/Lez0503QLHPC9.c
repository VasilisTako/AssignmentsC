#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int legge(int **a, int *len); //Legge un array di interi da input
void swap (int *a, int *b);
int distribuzione(int a[], int sx, int px, int dx);
void quicksort(int a[], int sx, int dx);
int pari_dispari(int a[], int sx, int dx);

int main() {

    int i, n, *A;

    if( legge(&A, &n))
        return 1;

    int separatore = pari_dispari(A, 0, n-1);

    srand(time(NULL));
    quicksort(A, 0, separatore);
    quicksort(A, separatore+1, n-1);

    for( i = 0; i < n; i++)     //Stampo l'array ordinato
        printf("%d ", A[i]);

    return 0;
}


int legge(int **a, int *len) {

    scanf("%d", len);
    if(*len <= 0)
        return 1;

    *a = (int *) malloc(*len * sizeof(int));
    if(*a == NULL)
        return 1;

    for(int i = 0; i < *len; i++)
        scanf("%d", (*a)+i);

    return 0;
}

void swap (int *a, int *b){
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

int pari_dispari(int a[], int sx, int dx) {

    int i = sx - 1;
    for(int j = sx; j <= dx; j++){
        if(abs(a[j]) % 2 == 0){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    return i;
}

int distribuzione(int a[], int sx, int px, int dx) {

    swap(&a[dx], &a[px]);

    int key = a[dx];
    int i = sx - 1;
    for(int j = sx; j < dx; j++){
        if(a[j] <= key){
            i++;
            swap(&a[i], &a[j]);
        }
    }
    swap(&a[i+1], &a[dx]);
    return i+1;
}

void quicksort( int a[], int sx, int dx ) {

    int perno;  //Elemento in posizione [pivot]
    int pivot;  //Indice

    if(sx < dx) {
        pivot = sx + rand() % (dx - sx + 1);   //La posizione del pivot viene scelta a caso

        perno = distribuzione(a, sx, pivot, dx); //Separa gli elementi minori di a[pivot] da quelli maggiori o uguali

        quicksort(a, sx, perno-1);
        quicksort(a, perno+1, dx);
    }
}


