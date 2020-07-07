#include<stdio.h>
#include<stdlib.h>
#define DIM 32
int controllo();
int controllosce();
void comando1();
void comando2();
void comando3();
void comando4();
void comando5();
void binario();
void complemento1();
void complemento2();
int vet[DIM];//vettore binario
int n;//n= numero intero


int main(){
	int s,c;// s= scelta, c=rappresentazione in binario
	printf("Inserisci un numero intero: ");
    void (*f[5])()={comando1,comando2,comando3,comando4,comando5};//dichiaro un array di puntatori a funzioni

	n=controllo();//effettuo il controllo su n

	while(s!=5){//Finche la scelta non è 5(opzione di uscita) continuo a ciclare.

		printf("Scegli un'opzione:\n");
		printf("\t1) Inserisci un nuovo numero.\n");
		printf("\t2) Stampa rappresentazione in complemento a due.\n");
		printf("\t3) Calcola opposto.\n");
		printf("\t4) Stampa rappresentazione in complemento a due dell'opposto.\n");
		printf("\t5) Esci.\n");
		printf("Scelta:  ");
		s=controllosce();//controllo la scelta
	    f[s-1]();//chiamata dell' array di puntatori
	}

	return 0;
}

//eseguo il primo comando
void comando1(){
        printf("Inserisci un numero intero: ");
        n=controllo();//effettuo il controllo su n
}

//eseguo il secondo comando
void comando2(){
        size_t j;//contatore per il ciclo for

		if(n>0){//se n è maggiore di zero il complemento a 2 è il binario di quel numero
			binario();//chiamo la funzione che calcola il binario
		}
		else{//se n è minore di zero il complemento a 2 si trova applicando le tre funzioni binario,complemento1 e complemento2
			binario();//chiamo la funzione che calcola il binario
			complemento1();//chiamo la funzione che calcola l opposto
			complemento2();//chiamo la funzione che aggiunge 1 al numero binario
		}
		printf("La rappresentazione di %d in complemento a due (MSB) è:",n);
        for(j=0;j<DIM;j++){//stampo il vettore
            if(j%4==0){
                printf(" ");
            }
            printf("%d",vet[j]);
        }
        printf(" ");
        printf("\n");
        printf("\n");


}//svolgo il comando 3
void comando3(){
		printf("L'opposto di %d è %d\n",n,(n-2*n));//stampo l'opposto dell'n inserito

}
void comando4(){
        size_t j;//contatore per il ciclo for

        if(n>0){//se n è maggiore di 0 per calcolare il complemento dell' opposto di n devo usare binario,complemento1 e complemento2
        	binario();//chiamo la funzione che calcola il binario
        	complemento1();//chiamo la funzione che calcola l opposto
        	complemento2();//chiamo la funzione che aggiunge 1 al numero binario
        }
        else{
        	binario();//chiamo la funzione che calcola il binario
        }


        printf("La rappresentazione dell'opposto di %d in complemento a due (MSB) è:",n);
        for(j=0;j<DIM;j++){

            if(j%4 == 0){
                printf(" ");
            }
            printf("%d",vet[j]);//stampo il vettore
        }
        printf(" ");
        printf("\n");
        printf("\n");
}
void comando5(){
	printf("Bye\n");//messaggio di uscita
}
//calcolo il complemento a uno
void complemento1(){
	size_t i;
	for(i=0;i<DIM;i++){
		if(vet[i]==1){//se il valore con indice i è uguale ad 1 lo sostituisco con 0
			vet[i]=0;
		}
		else if (vet[i]==0){//se il valore con indice i è uguale a 0 lo sostituisco con 1
			vet[i]=1;
		}
	}

}
//calcolo il complemento a 2
void complemento2(){
	size_t i,j;

	for(i=DIM-1;i>=0;i--){
		if(vet[i]==0){//se il valore con indice i è uguale a 0 ci sostituisco 1 e mi fermo
			vet[i]=1;
			break;
		}
		else if(vet[i]==1){//se il valore con indice i è uguale ad 1 ci sostuisco 0
			vet[i]=0;
		}
	}
}
//trasformo il numero da decimale a binario
void binario()
{
	size_t i=0;		//Inizializza indice
	int m=n;
	while(i<DIM)	// Fino all'untimo elemento
	{
		if((m%2)==0)	// Se il bit meno significativo e' 0
		{
			vet[DIM-1-i]=0;	// metto 0 nell'elemento del vettore
		} else {
			vet[DIM-1-i]=1;	// se no, metto 1
		}
		m=m/2;		// Elimino ilbit meno significativo per passare al prossimo
		++i;		// conto i bit elaborati
	}
}
//controllo N
int controllo(){

	int n;
	while(scanf("%d",&n)<1 ){//svolgo il controllo
		printf("Errore. Inserisci un numero intero.\n");
		scanf("%*[^\n]%*c");//effettuo la pulizia del buffer
	}
return n;
}
//controllo per la scelta
int controllosce(){

	int n;
	while(scanf("%d",&n)<1 || n<0 || n>5){//svolgo il controllo
		printf("Errore. Inserisci un numero intero.\n");
		scanf("%*[^\n]%*c");//effetto la pulizia del buffer
	}
return n;
}
