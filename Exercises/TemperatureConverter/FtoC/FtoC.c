#include <stdio.h>

int main()
{
    printf("Drukowanie tabeli przeliczeniowej stopni Fahrenheita na stopnie Celsjusza\n");
    /*Dla warto�ci F = 0, 20, ..., 300*/
    float F,C; /*Stopnie Farenheita, Celsjusza*/
    int o_ile, lower, upper; /*O ile stopni przej�cie, minimalna warto�� stopni, maksymalna warto�� stopni*/

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
