#include <stdio.h>
#include <string.h>
#include <math.h>

int na_osemkowy (int liczba) {
    int i;
    int p=1;
    int wynik = 0;
    for (i=0; liczba!=0; i++) {
        wynik = wynik + p*(liczba%8);
        liczba = liczba/8;
        p*=10;
    }
    return wynik;
}
int main () {
    printf("%d\n", na_osemkowy(69));
    return 0;
}
