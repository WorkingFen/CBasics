#include <stdio.h>

int main()
{
    int c;

    while((c = getchar()) != EOF) {
        if(c == '\t') {
            c = NULL;
            printf("\\");
            printf("t");
        }
        if(c == '\b') {
            c = NULL;
            printf("\\");
            printf("b");
        }
        if(c == '\\') {
            c = NULL;
            printf("\\");
            printf("\\");
        }
        putchar(c);
    }
}
