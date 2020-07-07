#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* archi;
    int n_archi;
}vertex;

typedef struct {
    int* elements;
    int size;
    int head;
    int tail;
}queue;

vertex* read_input (int *N);
void init_q(queue* q, int N);
void enqueue(queue* q, int src);
int dequeue(queue* q);
void deinit_q(queue* q);
int min_path(vertex* grafo, int N, int v_start, int v_end);

int main () {

    int N;
    vertex* grafo = read_input(&N);

    int v_start, v_end, n_path;
    scanf("%d", &n_path);
    for (int i = 0; i < n_path; ++i) {
        scanf("%d %d", &v_start, &v_end);
        printf("%d\n", min_path(grafo, N, v_start, v_end));
    }

    free(grafo);
    return 0;
}

vertex* read_input (int *N){

    scanf("%d", N);

    vertex* grafo = (vertex*)malloc((*N) * sizeof(vertex));
    for (int i = 0; i < *N; ++i) {
        scanf("%d", &grafo[i].n_archi);
        grafo[i].archi = (int*)malloc(grafo[i].n_archi * sizeof(int));
        for (int j = 0; j < grafo[i].n_archi; ++j)
            scanf("%d", &grafo[i].archi[j]);
    }
    return grafo;
}

int min_path(vertex* grafo, int N, int v_start, int v_end){

    if(v_start == v_end)
        return 0;

    int* distance = (int*)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++)
        distance[i] = -1;
    distance[v_start] = 0;

    queue q;
    init_q(&q, N);
    enqueue(&q, v_start);

    int src, dest;
    while (q.head != q.tail){
        src = dequeue(&q);
        for(int i = 0; i < grafo[src].n_archi; i++){
            dest = grafo[src].archi[i];
            if(distance[dest] == -1){
                distance[dest] = distance[src] + 1;
                if(dest == v_end){
                    int result = distance[dest];
                    deinit_q(&q);
                    free(distance);
                    return result;
                }
                enqueue(&q, dest);
            }
        }
    }
    deinit_q(&q);
    free(distance);
    return -1;
}

void init_q(queue* q, int N){
    q->size = N;
    q->head = 0;
    q->tail = 0;
    q->elements = (int*)malloc(N * sizeof(int));
}

void enqueue(queue* q, int src){
    q->tail++;
    q->elements[q->tail] = src;
}

int dequeue(queue* q){
    q->head++;
    return q->elements[q->head];
}

void deinit_q(queue* q){
    free(q->elements);
    q->size = q->head = q->tail = 0;
}