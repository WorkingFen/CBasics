#include <stdio.h>
#include <stdlib.h>

int main(){
    int n,i;
    float x,a,s;

    puts("Wpisz stopien n i liczbe x: ");
    if(scanf("%d %f", &n,&x)!=2){
        puts("Blad danych");
        return 1;
    }
    for(i=n,s=0.0;i>=0;i--){
        s*=x;
        printf("Wpisz liczbe a[%d]:", i);
        while(scanf("%f", &a)!=1){
            puts("Blad");
            while(getchar()!='\n');
            puts("Wpisz jeszcze raz");
			scanf("%f",&a);
        }
        s+=a;
    }
    printf("Wynik tego wielomianu to: %f", s);
    return 0;
}

