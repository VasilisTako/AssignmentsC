#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int controllo_val();
int controllo_sce();
void comando1();
void comando2();
void comando3();

int const M = 100;  //tetto massimo per il numero da indovinare
int val_iniziale;  //valore da indovinare

int main()
{
    int scelta;  //valore utilizzato per muoversi nell' array di puntatori a funzione.

    void(*f[3])() = {comando1,comando2,comando3};  //dichiaro l'array di puntatori a funzione

        printf("1 - gioco con due giocatori\n");
        printf("2 - gioco con tre giocatori\n");
        printf("3 - esci\n");
        printf("Scelta: ");
        scelta = controllo_sce();
        f[scelta-1]();

    main();


    return 0;
}

void comando1(){            //selezione a un giocatore
    int tentativi,numero_inserito;
    int i = 0;
    tentativi = (int)log2(M);
    printf("Numero segreto: ");
    val_iniziale = controllo_val();
    printf("Indovina il numero!\n");
    for(i = 0;i < tentativi+1;i++){
            printf("Tentativo numero %d: ",i+1);
            numero_inserito = controllo_val();
            if(numero_inserito > val_iniziale)
                printf("Troppo alto\n");
            else if(numero_inserito < val_iniziale)
                printf("Troppo basso\n");
            else if(numero_inserito == val_iniziale){
                printf("Hai vinto!\n");
                break;
            }
            if(i == tentativi)
                printf("Ha vinto il banco!\n");
    }
}

void comando2(){        //selezione a due giocatori
    int tentativi,numero_inserito;
    int i=0;
    tentativi = (int)log2(M);
    printf("Numero segreto: ");
    val_iniziale= controllo_val();
    printf("Indovina il numero!\n");
    for(i=0;i < tentativi+1; i++){
        printf("Tentativo numero %d: ",i+1);
        numero_inserito = controllo_val();
        if(numero_inserito > val_iniziale)
            printf("Troppo alto\n");
        else if(numero_inserito < val_iniziale)
            printf("Troppo basso\n");
        else if(numero_inserito == val_iniziale){
            if(i % 2 == 0){
                printf("Ha vinto il giocatore n. 1\n");
                break;
            }
            else{
                printf("Ha vinto il giocatore n. 2\n");
                break;
            }
        }
        if(i == tentativi)
            printf("Ha vinto il banco!\n");
    }


}

void comando3(){
    exit(0);
}

int controllo_val(){
    int n;
    while(scanf("%d",&n) < 1 || n < 0 || n > 100){
        printf("Errore. Inserire un numero fra 0 e M.\n");
        getchar();
    }
    return n;
}

int controllo_sce(){
    int n;
    while(scanf("%d",&n)<1 || n<0 || n>3){
        printf("Errore. Opzione non consentita. ");
        getchar();
        printf("Scelta: ");
    }
    return n;
}
