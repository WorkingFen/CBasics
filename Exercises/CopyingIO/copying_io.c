#include <stdio.h>

int main()
{
    int c, s;

    s = 0;
    while ((c = getchar()) != EOF) {
        if(c == ' ')
            ++s;
        if(s > 1) {
            while((c = getchar()) == ' ')
                c = NULL;
            s = 0;
        }
        if(c != ' ')
            s = 0;
        putchar(c);
    }
}
