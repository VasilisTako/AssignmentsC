#include <stdio.h>
#include <stdlib.h>

struct elemento{

	int info;
	int colore;
	struct elemento *right;
	struct elemento *left;

};
typedef struct elemento nodo;

nodo *crea(nodo **t, int el, int col);
nodo *inserisci(nodo **t, int el, int col);
int visita(nodo *t, int *ok);


int main(){

	int n, i, x, y;
	scanf("%d",&n);
	nodo *t=NULL;
	for(i=0;i<n;i++){
		scanf("%d %d",&x,&y);
		inserisci(&t,x,y);
	}
	int *ok=1;
	visita(t,&ok);
	if(ok) printf("TRUE\n");
	else printf("FALSE\n");

	return 0;
}

nodo *crea(nodo **t, int el, int col){ //creo un elemento di tipo nodo e inserisco gli attributi
    nodo *aux=malloc(sizeof(nodo));
    aux->info=el;
    aux->colore=col;
    aux->right=NULL;
    aux->left=NULL;
    return aux;
}


nodo *inserisci(nodo **t, int el, int col){ //inserisco gli elementi all'interno dell'abr

    if((*t)==NULL) (*t)=crea(&(*t),el,col); //nel caso non abbia inserito ancora nessuno elemento creo il primo 
    else {
        if(el > (*t)->info) (*t)->right=inserisci(&(*t)->right,el,col); // se ho gia un primo elemento lo confronto con la chiave 
        else (*t)->left=inserisci(&(*t)->left,el,col);
    }
    return *t;
}


int visita(nodo *t, int *ok){

	if(t==NULL) return 0;
    int sx=visita(t->left,ok);
    int dx=visita(t->right,ok);
    if((*ok)==0) return 0; 
    if(abs(sx-dx)>1){
        *ok=0;
        return 0;
    }
    int somma=sx+dx;
    if(t->left != NULL && t->right != NULL){  //solo per il test case 7 cioè quando ho i figli sinistro e destro entrambi rossi devo sottrarre dalla somma 1 cosi non conto un elemento in più
    	if(((t->left)->colore == 0) && ((t->right)->colore == 0)) somma--;// visto che vogliamo percorso da nodo a foglia allora dobbiamo togliere 1 in quanto non posso andare da entrambe le parti per arrivare alla foglia
    }
	if(t->colore == 0) return somma+1; //se il nodo è rosso allora aggiungo 1 alla somma finale
    return somma;

}