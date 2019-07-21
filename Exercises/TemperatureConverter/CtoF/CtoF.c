#include <stdio.h>

int main()
{
    printf("Drukowanie tabeli przeliczeniowej stopni Celsjusza na Fahrenheita\n");
    float C, F; /*Stopnie Celsjusza i Fahrenheita*/
    int o_ile, upper, lower;

    o_ile = 10;
    upper = 140;
    lower = -10;

    C = lower;
    while(C <= upper) {
        F = (9.0/5.0)*C + 32.0;
        printf("%3.0f\t%6.1f\n", C, F);
        C = C + o_ile;
    }
}
