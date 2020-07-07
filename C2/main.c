#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// Dichiaro due struct contententi i dati per la frequenza delle lunghezze e delle parole

struct freqLunghezza
{
    int frequenza;  //numero di volte che trovo una data lunghezza
	int lunghezza;  //definita dalla lunghezza delle parole
	struct freqLunghezza *prossima; //puntatore al prossimo elemento della lista
};

struct freqParola
{
    int frequenza;  //numero di volte che trovo una data parola
	char parola [50];
	struct freqParola *prossima;
};

typedef struct freqLunghezza frequenza_lunghe;
typedef frequenza_lunghe *frequenza_lunghe_pnt;

typedef struct freqParola frequenza_parola;
typedef frequenza_parola *frequenza_parola_pnt;



void lunghezza(char* stringa, frequenza_lunghe_pnt *lunghezza_iniziale, int *tot); //funzione per la lunghezza e la frequenza di tali lunghezze
_Bool comparazione(frequenza_parola_pnt *parola1, frequenza_parola_pnt *parola2);
void modifica(char* stringa);   //funzione che modifica il testo rimuovendo punteggiatura e maiuscole
_Bool ordinamento(char* stringa1, char* stringa2);
void parola(char* stringa, frequenza_parola_pnt *parola_iniziale); //funzione parole e frequenza parole
void stampa(frequenza_parola_pnt struct_parolaPnt, frequenza_lunghe_pnt struct_lunghezzaPnt, float tot);


int main(int argc, char const *argv[])
{

	char nomeFile[10];
	FILE *fileInput;
    int tot=0; // numero totale valori trovati
    char carattere[50]; // vettore usato per scorrere le parole

	frequenza_parola *parola_iniziale = NULL;
	frequenza_lunghe *lunghezza_iniziale = NULL;

    puts("Inserisci il nome del file da aprire:");
    scanf("%s",nomeFile);
	if ((fileInput = fopen(nomeFile, "r")) == NULL)
	{
		printf("Impossibile aprire il file\n");
		return 0;
	}
	while ((fscanf(fileInput, "%s" ,carattere) ) ==1 )
	{
		modifica(carattere);
		parola(carattere, &parola_iniziale);
		lunghezza(carattere, &lunghezza_iniziale, &tot);
	}
	stampa(parola_iniziale, lunghezza_iniziale, (float)tot);
	fclose(fileInput);

	return 0;
}

void modifica(char* stringa){
	// Levo tutti i caratteri maiuscoli o "speciali"
	int i;
	for (i = 0; i < strlen(stringa); ++i)
	{
		if (stringa[i] < 65 || (stringa[i] > 90 && stringa[i]<97) || stringa[i] > 122 )
		{
			memmove(&stringa[i], &stringa[i+1], strlen(stringa)-i);
			stringa[strlen(stringa)] = '\0';
			i -=1;
		}
		else if(65 <= stringa[i] && stringa[i] <= 90){
			stringa[i] = stringa[i]+32;
		}
	}
}

void lunghezza(char* stringa, frequenza_lunghe_pnt *lunghezza_iniziale, int *tot){

	frequenza_lunghe_pnt nuova_lunghezza = malloc(sizeof(frequenza_lunghe));

	if (nuova_lunghezza != NULL){

		nuova_lunghezza->lunghezza = strlen(stringa);
		nuova_lunghezza->prossima = NULL;

		frequenza_lunghe_pnt lunghezza_corrente = *lunghezza_iniziale;
		frequenza_lunghe_pnt lunghezza_precedente = NULL;

		while (lunghezza_corrente != NULL && nuova_lunghezza->lunghezza > lunghezza_corrente->lunghezza){ //itero per inserire i dati all' interno della lista
			lunghezza_precedente = lunghezza_corrente;
			lunghezza_corrente = lunghezza_corrente->prossima;
		}
		if (lunghezza_precedente == NULL && (lunghezza_corrente == NULL || nuova_lunghezza->lunghezza != lunghezza_corrente->lunghezza)){   // controllo le due lunghezze a inizio lista
			nuova_lunghezza->frequenza = 1;
			nuova_lunghezza->prossima = *lunghezza_iniziale;
			*lunghezza_iniziale = nuova_lunghezza;
		}
		else if(lunghezza_corrente != NULL && nuova_lunghezza->lunghezza == lunghezza_corrente->lunghezza){   // se le due lunghezze sono uguali aumento la frequenza
			lunghezza_corrente->frequenza +=1;
		}
		else{                    //altrimenti reimposto la frequenza a 1 e riparto
			nuova_lunghezza->frequenza=1;
			lunghezza_precedente->prossima = nuova_lunghezza;
			nuova_lunghezza->prossima = lunghezza_corrente;
		}
		*tot = *tot + 1;  //aumento il contatore degli elementi trovati
	}

}

_Bool ordinamento(char* stringa1, char* stringa2){
	// Calcolo l'ordine alfabetico di due parole
	int parola_lung_min ;
	int valore_return;
    int i;

    if(strlen(stringa1) < strlen(stringa2))
        parola_lung_min = strlen(stringa1);
    else
        parola_lung_min = strlen(stringa2);

	for (i = 0; i < parola_lung_min; ++i)
	{
		if (stringa1[i] < stringa2[i])
		{
			return 1;
		}
		else if (stringa2[i]<stringa1[i]){
			return 0;
		}
	}
    if(strlen(stringa1)<strlen(stringa2))
        valore_return = 1;
    else
        valore_return = 0;

	return valore_return;

}

void parola(char* stringa, frequenza_parola_pnt *parola_iniziale){
	// Frequenza parole in ordine alfabetico

	frequenza_parola_pnt nuova_parola = malloc(sizeof(frequenza_parola));

	if(nuova_parola != NULL){

		strcpy(nuova_parola->parola, stringa);
		nuova_parola->prossima = NULL;

		frequenza_parola_pnt parola_corrente = *parola_iniziale;
		frequenza_parola_pnt parola_precedente = NULL;

		while (parola_corrente != NULL && strcmp(parola_corrente->parola, stringa) != 0 && !ordinamento(nuova_parola->parola, parola_corrente->parola))
		{
			parola_precedente = parola_corrente;
			parola_corrente=parola_corrente->prossima;
		}

		if (parola_precedente==NULL && (parola_corrente == NULL || strcmp(parola_corrente->parola, stringa) != 0))  //controllo se le due parole non sono uguali a inizio lista
		{
			nuova_parola->frequenza = 1;
			nuova_parola->prossima = *parola_iniziale;
			*parola_iniziale = nuova_parola;
		}

		else if (parola_corrente != NULL && strcmp(parola_corrente->parola, stringa)==0){  //controllo se le due parole sono uguali e aumento la frequenza
			parola_corrente->frequenza += 1;
		}

		else {
			nuova_parola->frequenza = 1;
			parola_precedente->prossima = nuova_parola;
			nuova_parola->prossima = parola_corrente;
		}



	}
	else{
		printf("Memoria Esaurita!\n");
	}

}


void stampa(frequenza_parola_pnt lista_parolaPnt, frequenza_lunghe_pnt lista_lunghePnt, float tot){
	//Stampo tutto
	int i;
	printf("%10s%18s\n", "Lunghezza", "Frequenza (%)");
	while (lista_lunghePnt != NULL){
		float percentuale = ((float)lista_lunghePnt->frequenza/tot)*100;
		printf("%10d%15.2f %%\n", lista_lunghePnt->lunghezza, percentuale);
		lista_lunghePnt = lista_lunghePnt->prossima;
	}
	while (lista_parolaPnt != NULL){
		printf("%10s ", lista_parolaPnt->parola);
		for (i = 0; i < lista_parolaPnt->frequenza; ++i)
		{
			printf("*");
		}
		printf("\n");
		lista_parolaPnt = lista_parolaPnt->prossima;
	}
}
