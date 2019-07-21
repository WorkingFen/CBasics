#include <stdio.h>
#include <string.h>

int main() {

    FILE*liczby=fopen("liczby.txt", "r");
    FILE*wynikplik=fopen("wyniki.txt", "w");

    char tab[8];
    char tablica[1];
    int wynik,i,n;
    int naj=0;
    int najwi=0;
    int suma=0;

    for(i=0;i<1000;i++) {
        wynik=0;
        fscanf(liczby, "%s", &tab);
        for(n=1;n<7;n++) {
            wynik *= tab[0]-'0';
            wynik += tab[n]-'0';
        }
        if(tab[0]-'0'==4 && wynik>naj) {
            naj=wynik;
        }
        if(wynik>najwi){
            najwi=wynik;
        }
        suma += wynik;
        fprintf(wynikplik, "%i\n", wynik);
    }
    printf("%i\n", naj);
    printf("%i\n", najwi);
    printf("%i", suma);
    return 0;
}
