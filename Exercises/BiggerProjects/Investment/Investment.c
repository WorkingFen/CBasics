#include <stdio.h>
#include <stdlib.h>

float lokata(int n, float procent, float premia){

    int i;
    float saldo=1500;
    float lok;

    for(i=0;i<n;i++){
        saldo+=500;
        if(i<60 && (i%6==5)){
            lok=(saldo*(procent+premia)/200);
            saldo+=(lok*81/100);
        }

        if(i>=60 && i<120 && (i%6==0)){
            lok=(saldo*(procent+premia+0.1)/200);
            saldo+=(lok*81/100);
        }

        if( i>=120 && (i%6==0)){
            lok=(saldo*(procent+premia+0.2)/200);
            saldo+=(lok*81/100);
        }
    }

    return saldo;

}

int main(){

    int n;
    float procent, premia;

    puts("Wpisz liczbe miesiecy na ile bedziesz miec lokate, jakie jest oprocentowanie i jaka jest premia");

    scanf("%d %f %f", &n, &procent, &premia);

    printf("Po %d miesiacach na koncie bede miec: %.2f", n, lokata(n, procent, premia));

    return 0;

}
