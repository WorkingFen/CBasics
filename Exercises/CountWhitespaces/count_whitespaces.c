#include <stdio.h>

int main()
{
    int c, n, t, s;

    t = 0;
    n = 0;
    s = 0;
    while((c = getchar()) != EOF) {
        if(c == '\n')
            ++n;
        if(c == ' ')
            ++s;
        if(c == '\t')
            ++t;
    }
    printf("Ilosc enterow = %d, ilosc spacji = %d i ilosc tabulatorow = %d", n, s, t);
}
