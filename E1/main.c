#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//definisco i prototipi degli automi

void automa0(char *v);
void automa1(char *v);
void automa2 (char *v);
int automa_abDD(int stato, char carattere);
//dichiaro i contatori globalmente per poterli utilizzare in ogni punto del programma

int i = 0;
int j = 0;
int k = 0;

int main()
{
    char vet[50];     //dichiaro l' array che dovrà contenere la mia stringa
    void (*f[3])(char vet[]) = {automa0, automa1, automa2};      //dichiaro l' array di puntatori a funzione
    puts("Stringa:");
    scanf("%[^\n]", vet);     // prendo in input la stringa
    for (i = 0; i < 3; i++){
        (*f[i])(vet);     //chiamo 3 volte l'array di puntatori a funzione per muovermi nei 3 automi
    }
    printf("stringa appartenente al linguaggio\n");
    if (j == 2){
        printf("sottostringa abDD presente\n");
    }
    else{
        printf("nessuna sottostringa abDD\n");
    }
    return 0;
}

void automa0(char *vet)
{
    if (*vet >= 'A' && *vet <= 'Z'){        //controllo che il primo carattere sia compreso tra A e Z
        for (k = 1; k < 4 ; k++) {
            if (*(vet+k) < 'A' || *(vet+k) > 'Z'){       //controllo i 3 caratteri successivi e se ne trovo uno che non va bene fermo tutto
                break;
            }
        }
        if (*(vet + k) == 'a' && *(vet + k +1) == 'b'){     //controllo che le 2 occorrenze subito consecutive siano a e b
            k++;
            return;
            }
        else {
            puts("stringa non appartenente al linguaggio");     //altrimenti esco perchè la stringa non può appartenere al linguaggio
            exit(EXIT_SUCCESS);
        }
    }
    else {
        puts("stringa non appartenente al linguaggio");
        exit(EXIT_SUCCESS);
    }
}

void automa1(char *vet)
{
    if (*(vet + k) == 'b' && *(vet + k + 1) != 'b') {       //controllo se i valori che seguono b sono b o altri caratteri
        j++;
        ++k;
    }
    else{
        while (*(vet + k) == 'b') {
            ++k;
        }
    }
}
//funzione di ctype.h che mi restituisce 1 se trova un carattere 0 altrimenti (isalpha)
void automa2 (char *vet)
{
    if (isalpha(*(vet + k)) && *(vet + k) == 'D' && *(vet + k + 1) == 'D') {
        j++;                                                                    //controllo se trovo la sottostringa abDD
    }
    for (i = 0; i < 3; ++i) {
        if (isalpha(*(vet + k)) && *(vet + k) != 'd') {             //controllo se le occorrenze successive ad aba
            ++k;
        } else if (*(vet + k) == 'd') {
            puts("stringa non appartenente al linguaggio");
            exit(EXIT_SUCCESS);

        }
    }if (isalpha(*(vet + k))){
        puts("stringa non appartenente al linguaggio");
        exit(EXIT_SUCCESS);
    }

}
