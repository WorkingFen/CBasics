#include <stdio.h>

int main()
{
    printf("Drukowanie tabeli przeliczeniowej stopni Fahrenheita na stopnie Celsjusza\n");
    /*Dla wartoœci F = 0, 20, ..., 300*/
    float F,C; /*Stopnie Farenheita, Celsjusza*/
    int o_ile, lower, upper; /*O ile stopni przejœcie, minimalna wartoœæ stopni, maksymalna wartoœæ stopni*/

    lower = 0;
    upper = 300;
    o_ile = 20;

    F = lower;
    while(F <= upper) {
        C = (5.0/9.0)*(F-32.0);
        printf("%3.0f\t%6.1f\n", F, C);
        F = F + o_ile;
    }
}
