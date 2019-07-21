#include <stdio.h>

int main()
{
    int c, i, max;
    int ndigit[100];
    max = 0;

    for(i = 0; i < 100; ++i)
        ndigit[i] =0;

    while((c = getchar()) != EOF)
        ++ndigit[c - '0'];

    for(i = 0; i < 101; ++i)
        max = max + ndigit[i];

    for(i = 0; i < 100; ++i)
        if(ndigit[i] != 0)
            printf("Czestotliwosc danego znaku %c: %d/%d\n", i + '0', ndigit[i], max);
}
