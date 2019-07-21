#include <stdio.h>

int main()
{
    int c, i, nc, a;
    int ndigit[30];
    for(i = 0; i < 30; ++i)
        ndigit[i] = 0;
    nc = 0;
    while((c = getchar()) != EOF) {
        ++nc;
        if(c == '\n' || c == '\t' || c == ' ') {
            ++ndigit[nc];
            nc = 0;
        }
    }
    for(i = 0; i < 30; ++i) {
        if(ndigit[i] != 0) {
            printf("Slow o dlugosci %d jest: %d ", i-1, ndigit[i]);
            for(a = 0; a < ndigit[i]; ++a)
                printf("_");
            printf("\n");
        }
    }
}
