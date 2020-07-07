#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int N;

typedef struct v{
    int n_archi;
    int* archi;
}vertex;

vertex* read_input();
void rec_check_path(vertex* grafo, int start, int* colors);
int check_path(vertex* grafo, int start_v);


int main () {

    vertex* grafo = read_input();

    srand(time(NULL));
    int v_start = 0 + rand()%N;

    printf("%d\n", check_path(grafo, v_start));

    free(grafo);
    return 0;
}

vertex* read_input(){

    scanf("%d", &N);
    vertex* grafo = malloc(N * sizeof(vertex));

    for(int i = 0; i < N; i++){
        scanf("%d", &grafo[i].n_archi);
        grafo[i].archi = (int*)malloc(grafo[i].n_archi * sizeof(int));
        for (int j = 0; j < grafo[i].n_archi; ++j)
            scanf("%d", &grafo[i].archi[j]);

    }
    return grafo;
}

int check_path(vertex* grafo, int start_v){

    int* colors = (int*)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i)
        colors[i] = 0;

    colors[start_v] = 1;
    rec_check_path(grafo, start_v, colors);
    

    for(int i = 0; i < N; i++){
        if(!colors[i]){
            free(colors);
            return 0;
        }
    }
    free(colors);
    return 1;
}

void rec_check_path(vertex* grafo, int start, int* colors){

    int vertice_adiacente;

    for(int i = 0; i < grafo[start].n_archi; i++){
        vertice_adiacente = grafo[start].archi[i];
        if(!colors[vertice_adiacente]) {
            colors[vertice_adiacente] = 1;
            rec_check_path(grafo, vertice_adiacente, colors);
        }
    }
}