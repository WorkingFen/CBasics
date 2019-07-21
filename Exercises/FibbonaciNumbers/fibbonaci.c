#include <stdio.h>
#include <string.h>


int fibbonaci1(int a, int b,FILE *fibbo) {
    int c=a+b;
    if(c>1000000000)
        return 0;
    fprintf(fibbo,"%d\n", c);
    fibbonaci1(b, c, fibbo);
}

/*int sprawdz1(int tab[], int tab2[], int i, int a) {
    if(a==44)
        return 0;
    if(tab[i]==tab2[a])
        printf("%d", tab[i]);
    else{
        a++;
        sprawdz1(tab[i], tab2[a], i, a)
    }
} */

int tablica[50];
int maxi;

int fibbonaci() {
    tablica[0] = 0;
    tablica[1] = 1;
    int i = 2;
    while (tablica[i-1] < 1000000000) {
        tablica[i] = tablica[i-2]+tablica[i-1];
        i++;
    }
    maxi = i-1;
}

int sprawdz(int liczba) {
    int i;
    for(i=0; i<maxi; i++) {
        if (tablica[i] == liczba)
            return 1;
    }
    return 0;
}


int main () {
    FILE *dane =fopen("dane.txt", "r");
    FILE *fibbo =fopen("fibbo.txt", "w");
    fibbonaci();
    fibbonaci1(0,1, fibbo);
    FILE *numbe =fopen("fibbo.txt", "r");

    int tab[44];
    int dan[201];
    int i,a,b;
    int maxf,minf,wyn;

    for(i=0;i<44;i++) {
        fscanf(numbe,"%d",&tab[i]);
    }
    for(i=0,a=0,b=0;i<200;i++){
        fscanf(dane,"%d", &dan[i]);
        if(!i){
                maxf=dan[i];
                minf=dan[i];
                wyn=b;
            }
        if (sprawdz(dan[i])){
            printf("%d\n", dan[i]);
            a++;
            b++;
            if(dan[i]>maxf)
                maxf=dan[i];
            if(dan[i]<minf)
                minf=dan[i];
        }
        else {
            if(wyn<b)
                wyn=b;
            b=0;
        }
    }
    printf("Liczb Fibbonaciego w pliku dane jest: %d\n", a);
    printf("Najwieksza liczba Fibbonaciego z pliku dane to: %d\n", maxf);
    printf("Najmniejsza liczba Fibbonaciego z pliku dane to: %d\n", minf);
    printf("Najwiekszy ciag liczb Fibbonaciego to: %d\n", wyn);

    return 0;
}
