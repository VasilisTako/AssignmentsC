 #include <stdio.h>
 #include <stdlib.h>
 #include <math.h>
 #include <stddef.h>

 int controllo(int nElementi);
 void ordinamento(int matOcc[][100],int rigcol);


 int main()
 {
    int temp;//variabile temporanea per scorrere il file la prima volta
    int nElementi=0; //numero elementi nella matrice
    float rigcol; // numero di righe e colonne NxN
    int i,j,k,l=0;//contatori
    int M;//numero di occorrenze da ricercare
    char nomefile[20];//nome del file da aprire
    int matOcc[100][100];//matrice utilizzata per inserire al suo interno valori occorrenze

        puts("Inserisci il nome del file");
        scanf("%s",nomefile);

        FILE *MatQuadrata;//dichiaro un puntatore di tipo file
        if((MatQuadrata=fopen(nomefile,"r"))==NULL)//apro il file
        {
            puts("Impossibile aprire il file.");
            exit(1);
        }
        else
        {
            while(!feof(MatQuadrata))//scorro il file fino a quando non arrivo alla fine
            {
                fscanf(MatQuadrata,"%d\n",&temp);
                nElementi++;//incremento il numero di elementi ad ogni ciclo
            }
        }

    rigcol=sqrt(nElementi);//faccio la radice quadrata del numero di elementi per verificare se è effetivamente quadrata
    if(rigcol != (int)rigcol){//controllo che la radice sia un numero intero
        exit(0);
    }
    else{
        puts("La matrice presa dal file e' quadrata.\n");
    }
    int **matrice=(int**)malloc(nElementi*sizeof(int*));//dichiaro una matrice dinamica

    for(i=0;i<nElementi;i++){
        matrice[i]=(int*)malloc(sizeof(int)*nElementi);//alloco alla matrice int*n elementi
    }
    rewind(MatQuadrata);//torno all'inizio del file
    while(!feof(MatQuadrata))//fino a quando non arrivo all' eof
    {
        for(i=0;i<rigcol;i++)
        {
            for(j=0;j<rigcol;j++)
            {
                fscanf(MatQuadrata,"%d",&matrice[i][j]);//inserisco all' interno della matrice creata i valori della matrice del file
            }
        }
    }


    //stampa
    for(i=0;i<rigcol;i++){
        for(j=0;j<rigcol;j++){
            printf("%d  ",matrice[i][j]);
        }
        puts("");
    }
    printf("Inserisci il numero di occorrenze dei valori da ricercare:\n");
    M=controllo(nElementi);//prendo il valore minimo delle occorrenze contigue
    k=0;//Faccio partire k da 0

    //calcolo occorrenze verticali
    for(i=0; i<rigcol; i++){
        static int cont=1;
        for(j=0; j<rigcol; j++){
            static int x,y,z=0;
            if(j<rigcol-1){
                if(matrice[i][j]==matrice[i][j+1]){
                    if(cont==1){
                        y=i;//colonne
                        x=j;//righe
                        z=matrice[i][j];//valore
                    }
                    cont++;
                }
             if(cont>=M && (((matrice[i][j]!=matrice[i][j+1])) || (matrice[i][j]==matrice[i][j+1] && (j+1==rigcol-1)))){
                matOcc[k][0]=cont; //numero di occorrenze
                matOcc[k][1]=z; //numero che viene ripetuto
                matOcc[k][2]=x; //numero di righe
                matOcc[k][3]=y; //colonne
                matOcc[k][4]=1;; //vale 1 quando l' occorrenza è in verticale, 0 quando è in orizzontale
                k++;
                cont=1;
             }
             if(matrice[i][j]!=matrice[i][j+1]){
                cont=1;
             }
            }
        }
    }

    //calcolo occorrenze orizzontali
    for(j=0; j<rigcol; j++){
        static int cont=1;
        for(i=0; i<rigcol; i++){
            static int x,y,z=0;
            if(i<rigcol-1){
                    if(matrice[i][j]==matrice[i+1][j]){
                        if(cont==1){
                            y=i;
                            x=j;
                            z=matrice[i][j];
                        }
                        cont++;
                    }
                if(cont>=M && (((matrice[i][j]!=matrice[i+1][j])) || ((matrice[i][j]==matrice[i+1][j]) && (i+1== rigcol-1)))){
                    matOcc[k][0]=cont; //numero di occorrenze
                    matOcc[k][1]=z; //numero ripetuto
                    matOcc[k][2]=x; //righe
                    matOcc[k][3]=y; //colonne
                    matOcc[k][4]=0; //vale 0 se l'occorrenza è in orizzontale,1 se in verticale
                    k++;
                    cont=1;
                }
                if(matrice[i][j]!=matrice[i+1][j]){
                    cont=1;
                }
            }
        }
    }


    ordinamento(matOcc,rigcol);

    while((matOcc[l][0])>=M){

        if((matOcc[l][4])==0){
                    printf("Ci sono %d occorrenze consecutive di %d in colonna %d a partire dalla riga %d\n\n",matOcc[l][0],matOcc[l][1],matOcc[l][2],matOcc[l][3]);
        }
        else if((matOcc[l][4])==1){
                    printf("Ci sono %d occorrenze consecutive di %d in riga %d a partire dalla colonna %d\n\n",matOcc[l][0],matOcc[l][1],matOcc[l][2],matOcc[l][3]);
        }
        l++;
    }

    fclose(MatQuadrata);
    return 0;
 }


void ordinamento(int matOcc[][100],int rigcol)
    {
        int n1=0; // contatore 1
        int n2=0; // contatore 2
        int temp=0; // variabile di supporto

        for(n1=0;n1<(rigcol*rigcol);n1++){
            for(n2=0;n2<(rigcol*rigcol)-n1-1;n2++){
                if(matOcc[n2][0]<matOcc[n2+1][0]){

                    temp=matOcc[n2][0];
                    matOcc[n2][0]=matOcc[n2+1][0];   // scambio il numero di occorrenze
                    matOcc[n2+1][0]=temp;

                    temp=matOcc[n2][1];
                    matOcc[n2][1]=matOcc[n2+1][1];  // scambio il valore che occorre
                    matOcc[n2+1][1]=temp;

                    temp=matOcc[n2][2];
                    matOcc[n2][2]=matOcc[n2+1][2];  // scambio il numero di righe
                    matOcc[n2+1][2]=temp;

                    temp=matOcc[n2][3];
                    matOcc[n2][3]=matOcc[n2+1][3];  // scambio il numero di colonne
                    matOcc[n2+1][3]=temp;

                    temp=matOcc[n2][4];
                    matOcc[n2][4]=matOcc[n2+1][4];  // scambio il fatto che sia orizzontale o verticale l'occorrenza.
                    matOcc[n2+1][4]=temp;

                }
            }
        }

    }
 int controllo(int nElementi)
 {
     int n;
     while(scanf("%d",&n)<1 || n<1 || n>=sqrt(nElementi) ){
        puts("Errore. Reinserire il valore\n");
        scanf("%*[^\n]%*c");
     }
     printf("\n\n");
     return n;
 }
