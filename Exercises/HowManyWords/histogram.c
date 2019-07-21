#include <stdio.h>

int main()
{
    int c, nc, i, j, max, a, b;
    int ndigit[30];
    nc = 0;

    for(i = 0; i < 30; ++i)
        ndigit[i] = 0;

    while((c = getchar()) != EOF) {
        ++nc;
        if(c == ' ' || c == '\t' || c == '\n') {
            ++ndigit[nc];
            nc = 0;
        }
    }
    i = 1;
    for(j = 2; j < 30; ++j) {
        if(ndigit[i] < ndigit[j])
            i = j;
        max = ndigit[i];
    }

    printf("Ilosc wyrazow:   ");

    for(i = 2; i < 30; ++i)
        if(ndigit[i] != 0)
            printf("%2d ", ndigit[i]);

    printf("\n");

    b = max;
    for(i = 0; i < max; ++i) {
        printf("\t        ");
        for(a = 2; a < 30; ++a)
            if(ndigit[a] != 0 && ndigit[a] >= b)
                printf("  |");
            else if(ndigit[a] != 0 && ndigit[a] < b)
                printf("   ");
        --b;
        printf("\n");
    }

    printf("Slowa dlugosci: ");

    for(i = 1; i < 30; ++i)
        if(ndigit[i] != 0)
            printf("%3d", i);
}
