#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct per il prodotto.
struct prodotto
{
	int cod;
	char nome[50];
	int prezzo;
	int numero;
	struct prodotto *prossimo;
};
typedef struct prodotto Prodotto;
typedef Prodotto *ProdottoPnt; // puntatore alla struttura

// Le dichiaro come variabili globali per poterle poi stampare in uscita.
int soglia = 10;
int tot = 0;

// Variabile usata per stampare al contrario la lista
int prodotti_in_mem = 0;

void inserisci_prodotto(ProdottoPnt *prodottoIni, int prezzo ,int numero , int cod, char* nome); //funzione utilizzata per inserire i prodotto ed ordinarli in base al loro codice
void stampa_menu();       // stampa del menu
int prendi_cod();        // funzione utilizzata per la richiesta del codice prodotto
void stampa_dettagli_prod(ProdottoPnt prodotto);     // funzione per la stampa dei dettagli del prodotto
Prodotto** cod_per_prodotto(ProdottoPnt *prodottoIni, int cod);  //risalgo al prodotto dal codice e faccio i vari controlli
void varia_numero_prod(ProdottoPnt *prodottoIni);
void cancella_prod(ProdottoPnt *prodottoIni);
void copia_inFile(ProdottoPnt *prodottoIni);  // utilizzata  per stampare una data lista sul file
void aggiungi_prod(ProdottoPnt *prodottoIni);
void varia_prezzo_prod(ProdottoPnt *prodottoIni);
void cerca_prod(ProdottoPnt *prodottoIni);
Prodotto** prod_sottosoglia(ProdottoPnt *prodottoIni);
void stampa_sottosoglia(ProdottoPnt *prodottoIni);
void esci(ProdottoPnt *prodottoIni);

int main(int argc, char const *argv[])
{
    Prodotto *prodottoIni = NULL;
	FILE *input; //dichiaro un tipo file per il file.csv che andrò a leggere
	if ((input = fopen("elencoProdotti.csv", "r")) == NULL)
	{
		printf("Impossibile trovare il file elencoProdotti.csv\n");
		return 0;
	}
	//setto il seed a 10
	char vet[100];
    srand(10);
	while (fgets(vet, sizeof vet, input) != NULL) // mi prendo quello che c'è in input_file, con dimensione di d, e lo vado ad immagazzinare nel buffer puntato da d
	{
		// Mi prendo tutti i prodotti
		int cod = 0;
		int prezzo = 0;
		char* nome = malloc(sizeof vet);
		int numero = rand() % 100000; // prendo un valore randomico che va da a 0 a 100.000

		if (sscanf(vet, "%d;%[^;];%d", &cod, nome, &prezzo) < 3){
			printf("Errore, il file elencoProdotti.csv è formattato male!\n");
			return 0;
		}
		inserisci_prodotto(&prodottoIni, prezzo, numero, cod, nome);
		free(nome);
	}
	fclose(input);
    //array di puntatori a funzione per il menu testuale.
	void (*f[7])() = {varia_numero_prod, varia_prezzo_prod, aggiungi_prod, cancella_prod, cerca_prod, stampa_sottosoglia, esci};
	int sce;
	while(sce != 7)
    {
		// Faccio apparire il menu fino a quando l'utente non esce
		stampa_menu();
		sce = 0;
		while(scanf("\n%d", &sce) != 1 || sce > 7 || sce < 1){
			stampa_menu();
			getchar();
		}
		f[sce-1](&prodottoIni);
	}

	return 0;
}

void inserisci_prodotto(ProdottoPnt *prodottoIni, int prezzo, int numero, int cod, char* nome)
{
	// Inserisco il prodotto nella lista
	ProdottoPnt prod_nuovo = malloc(sizeof(Prodotto));
	if (prod_nuovo != NULL)
    { //se il nuovo prodotto è diverso da null vado a copiare i valore nella struct
        prod_nuovo->numero = numero;
		prod_nuovo->prezzo = prezzo;
		prod_nuovo->cod = cod;
		strcpy(prod_nuovo->nome, nome);
		prod_nuovo->prossimo = NULL;


		ProdottoPnt prodotto_corr = *prodottoIni; //do al prodotto corrente l indirizzo del prodotto iniziale
		ProdottoPnt prodotto_prec = NULL;
		//effettuo l'ordinamento in base al codice del prodotto
		while (prodotto_corr != NULL && prodotto_corr->cod < prod_nuovo->cod)
        {
			prodotto_prec=prodotto_corr;
			prodotto_corr=prodotto_corr->prossimo;
		}
		if (prodotto_prec == NULL)
        {
			prod_nuovo->prossimo = *prodottoIni;
			*prodottoIni=prod_nuovo;
		}
		else
		{
			prodotto_prec->prossimo = prod_nuovo;
			prod_nuovo->prossimo = prodotto_corr;
		}
		prodotti_in_mem+=1;

	}
	else
    {
		printf("Memoria esaurita!\n");
		exit(1);
	}
}

void stampa_menu()
{
	printf("Scegliere un'opzione (1 - variazione della quantità di un prodotto; 2 - variazione del prezzo di un prodotto; 3 - inserimento di un nuovo prodotto; 4 - eliminazione di un prodotto; 5 - Ricerca di un prodotto; 6 - Stampa prodotti sotto la soglia; 7 - Esci):\n");
}

int prendi_cod()
{
	// controllo sul codice prodotto
	int cod;
	printf("Inserire il codice del prodotto:\n");
	while (scanf("\n%d", &cod) < 1)
    {
		printf("Inserire il codice del prodotto\n");
		getchar();
	}
	return cod;
}

void stampa_dettagli_prod(ProdottoPnt prodotto)
{
	printf("%10d%50s%10d%10d\n", prodotto->cod, prodotto->nome, prodotto->prezzo, prodotto->numero);
}

Prodotto** cod_per_prodotto(ProdottoPnt *prodottoIni, int cod)
{ //ritorno un array di puntatori ai prodotti. (passo quello corrente e quello precedente che mi serve ad eliminare i prodotti.)
    ProdottoPnt prodotto_corr = *prodottoIni;
	ProdottoPnt prodotto_prec = NULL;
	while (prodotto_corr != NULL && prodotto_corr->cod != cod)
    {
		prodotto_prec = prodotto_corr;
		prodotto_corr = prodotto_corr->prossimo;
	}
	ProdottoPnt *val_return = malloc(sizeof(Prodotto) * 2);
	val_return[0] = prodotto_corr;
	val_return[1] = prodotto_prec;
	return val_return;
}

void varia_numero_prod(ProdottoPnt *prodottoIni)
{
	//in questa funzione vado a modificare il numero dei prodotti
	int cod = prendi_cod();
	Prodotto **prodotto = cod_per_prodotto(prodottoIni, cod);
	if (prodotto[0] == NULL)
    {
		printf("Non esiste nessun prodotto con questo codice\n");
		return;
	}
	int numero;
	printf("Inserisci la nuova quantita:\n");
	while(scanf("\n%d", &numero) < 1)
	{
		printf("Quantita non valida, inseriscine un'altra\n");
		getchar();
	}
	prodotto[0]->numero=numero;
	stampa_dettagli_prod(prodotto[0]);
	free(prodotto);

}

void cancella_prod(ProdottoPnt *prodottoIni)
{   //uso questa funzione per cancellare un prodotto gia presente nella lista
	int cod = prendi_cod();

	Prodotto **prodotto = cod_per_prodotto(prodottoIni, cod);
	if (prodotto[0] == NULL)
    {
		printf("Non esiste un prodotto associato a questo codice.\n");
		return;
	}
	prodotto[1]->prossimo = prodotto[0]->prossimo;
	stampa_dettagli_prod(prodotto[0]);
	free(prodotto[0]);
	free(prodotto);
	prodotti_in_mem -=1;
    copia_inFile(prodottoIni);
}

void copia_inFile(ProdottoPnt *prodottoIni)
{
	// Salvo la lista attuale sul file
	FILE *input = fopen("elencoProdotti.csv", "w");
	ProdottoPnt prodotto_corr = *prodottoIni;
	while (prodotto_corr != NULL)
    {
		fprintf(input, "%d;%s;%d\n", prodotto_corr->cod, prodotto_corr->nome, prodotto_corr->prezzo);
		prodotto_corr = prodotto_corr->prossimo;
	}
	fclose(input);
}

void aggiungi_prod(ProdottoPnt *prodottoIni)
{   //uso questa funzione per aggiungere un nuovo prodotto alla lista
	int cod = prendi_cod();
	if (cod_per_prodotto(prodottoIni, cod)[0] != NULL)
    {
		printf("Esiste già un prodotto con questo codice!\n");
		return;
	}
	char nome[50];
	printf("Inserisci il nome:\n");
	while(scanf("\n%[^\n]", nome) < 1)
	{
		printf("Nome errato. Reinserire.\n");
		getchar();
	}
	int prezzo;
	printf("Inserisci il nuovo prezzo:\n");
	while(scanf("\n%d", &prezzo) < 1)
	{
		printf("Prezzo errato. Reinserire.\n");
		getchar();
	}
	int numero;
	printf("Inserisci la quantita:\n");
	while(scanf("\n%d", &numero) < 1)
	{
		printf("Quantità errata. Reinserire.\n");
		getchar();
	}
	inserisci_prodotto(prodottoIni, prezzo, numero, cod, nome);
	copia_inFile(prodottoIni);
	printf("%10d%50s%10d%10d\n", cod, nome, prezzo, numero);
}

void varia_prezzo_prod(ProdottoPnt *prodottoIni)
{
	// in questa funzione vado a modificare il prezzo dei prodotti
	int cod = prendi_cod();
	Prodotto **prodotto = cod_per_prodotto(prodottoIni, cod);
	if (prodotto[0] == NULL)
    {
		printf("Non esiste nessun prodotto con questo codice\n");
		return;
	}
	int prezzo;
	printf("Inserisci il nuovo prezzo:\n");
	while(scanf("\n%d", &prezzo) < 1)
    {
		printf("Prezzo non valido, inseriscine un altro\n");
		getchar();
	}
	prodotto[0]->prezzo=prezzo;
	stampa_dettagli_prod(prodotto[0]);
	free(prodotto);
	copia_inFile(prodottoIni);
}

void cerca_prod(ProdottoPnt *prodotto_iniziale)
{   //uso questa funzione per cercare un prodotto attraverso il suo codice
	int cod = prendi_cod();
	Prodotto **prodotto = cod_per_prodotto(prodotto_iniziale, cod);
	if (prodotto[0] == NULL)
    {
		printf("Non esiste un prodotto associato a questo codice.\n");
		return;
	}
	stampa_dettagli_prod(prodotto[0]);
	free(prodotto);
}

Prodotto** prod_sottosoglia(ProdottoPnt *prodottoIni)
{
	int i = 0;
	ProdottoPnt prodotto_corr = *prodottoIni;
	ProdottoPnt *val_return = malloc(sizeof(Prodotto) * prodotti_in_mem);
	memset(val_return, 0, sizeof(val_return)*prodotti_in_mem);
	tot = 0;
	while(prodotto_corr != NULL)
    {
		if (prodotto_corr->numero < soglia){
			val_return[i] = prodotto_corr;
			i += 1;
		}
		tot += 1;
		prodotto_corr = prodotto_corr->prossimo;
	}
	return val_return;
}

void stampa_sottosoglia(ProdottoPnt *prodottoIni)
{    //stampo i prodotti con numero sotto la soglia
    int i;
	printf("Inserisci la soglia:\n");
	while (scanf("\n%d", &soglia) < 1)
    {
		printf("Soglia errata. Reinserire.\n");
		getchar();
	}
	Prodotto **prodotto = prod_sottosoglia(prodottoIni);
	for (i = prodotti_in_mem; i >= 0; --i)
	{
		if (prodotto[i] != NULL) {
			stampa_dettagli_prod(prodotto[i]);
		}
	}
	free(prodotto);
}

void esci(ProdottoPnt *prodottoIni)
{
    int i;
	Prodotto **prodotto = prod_sottosoglia(prodottoIni);
	FILE *soglia = fopen("daOrdinare.bin", "w");
	int sotto_soglia = 0;
	fprintf(soglia, "%20s%50s%20s\n", "Codice", "Nome", "Da Ordinare" );
	for (i = prodotti_in_mem; i >= 0; --i)
	{
		if (prodotto[i] != NULL) {
			fprintf(soglia, "%20d%50s%20d\n", prodotto[i]->cod, prodotto[i]->nome, soglia-prodotto[i]->numero+1);
			sotto_soglia +=1;
		}
	}
    printf("Numero totale di prodotti disponibili in magazzino: %d\n", prodotti_in_mem);
	printf("Numero totale di prodotti sotto la soglia: %d\n", sotto_soglia);
	free(prodotto);
	fclose(soglia);
	FILE *numTotale = fopen("numeroTotale.txt", "w");
	fprintf(numTotale, "Numero totale di prodotti: %d\nNumero di prodotti sotto la soglia: %d\n", tot, sotto_soglia);
	fclose(numTotale);
	printf("Ciao!\n");
	exit(0);
}
