#include <stdio.h>
#include <string.h>
#define LAST '~'
#define FIRST '!'
#define FIRSTKEY 21
#define SECONDKEY 37
#define SPACE LAST-FIRST+1

int main(){

    FILE*data=fopen("coded.txt", "r");
    FILE*decode=fopen("decoded.txt", "w");

    char tab[128];
    int key=FIRSTKEY;
    int no, foo;

    while((foo = getc(data))!= EOF){                        /*<---- Does program ends after this word? If not, continue*/
        ungetc(foo, data);
        fscanf(data, "%s", &tab);                           /*<---- Get the word*/
        for(no=0;no<strlen(tab);no++){                      /*<---- Decode every char*/
            if(key>SPACE)                                   /*<---- If the key was too big*/
                key%=SPACE;

            tab[no]-=key;                                   /*<---- Subtract key from char*/

            if(tab[no]<FIRST)                               /*<---- If created char is lesser than the FIRST*/
                tab[no]+=SPACE;

            if(tab[no]<0)                                   /*<---- If char > 128, then it changes its value to -128*/
                tab[no]+=128+FIRST+1;

            key+=SECONDKEY;                                 /*<---- Add SECONDKEY to key*/
        }
        fprintf(decode, "%s ", &tab);                       /*<---- Print created word*/
        memset(tab, 0, 128);
    }

    if(fclose(data)!=0 || fclose(decode)!=0)
        fprintf(stderr, "An error occurred while closing files.\n");
    return 0;
}
