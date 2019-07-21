#include <stdio.h>
#include <stdlib.h>

int silnia(int n) {
    if(n==1 || n==0)
        return 1;
    return n*silnia(n-1);
}

void perm(int n, int tab[6]) {
    int tmp;

    if(n%silnia(6)==599) {
        tmp = tab[0];
        tab[0] = tab[3];
        tab[3] = tmp;
    }
    else if(n%silnia(6)==479) {
        tmp = tab[0];
        tab[0] = tab[5];
        tab[5] = tmp;
    }
    else if(n%silnia(6)==359) {
        tmp = tab[0];
        tab[0] = tab[4];
        tab[4] = tmp;
    }
    else if(n%silnia(5)==119) {
        tmp = tab[0];
        tab[0] = tab[1];
        tab[1] = tmp;
    }
    else if(n%silnia(4)==23) {
        tmp = tab[1];
        tab[1] = tab[2];
        tab[2] = tmp;
    }
    else if(n%silnia(4)==17) {
        tmp = tab[2];
        tab[2] = tab[5];
        tab[5] = tmp;
    }
    else if(n%silnia(3)==5) {
        tmp = tab[2];
        tab[2] = tab[3];
        tab[3] = tmp;
    }
    else if(n%silnia(2)==1) {
        tmp = tab[3];
        tab[3] = tab[4];
        tab[4] = tmp;
    }
    else if(n%silnia(2)==0) {
        tmp = tab[4];
        tab[4] = tab[5];
        tab[5] = tmp;
    }
}

int main() {
    //FILE*f =fopen("wyniki.txt", "w");
    int tabM1[6] = {30, 73, 79, 84, 26, 7};
    int tabM2[6] = {22, 76, 40, 38, 96, 44};
    int winner[6];

    int i, j, resultM1, resultM2;
    int smallest = 99999;

    for(j=0; j<silnia(6); j++) {
        resultM1 = 0;
        resultM2 = 0;

        for(i=0; i<6; i++) {
            resultM1 += tabM1[i];
            if(i==0)
                resultM2 = tabM2[i] + resultM1;
            else if(resultM1 > resultM2)
                resultM2 = resultM1 + tabM2[i];
            else
                resultM2 += tabM2[i];
        }
        if(smallest>resultM2) {
            smallest = resultM2;
            for(i=0; i<6; i++)
                winner[i] = tabM1[i];
        }
        //fprintf(f, "%d %d %d %d %d %d: ", tabM1[0], tabM1[1], tabM1[2], tabM1[3], tabM1[4], tabM1[5]);
        //fprintf(f, "%d\n", resultM2);
        perm(j, tabM1);
        perm(j, tabM2);
    }
    //fclose(f);

    printf("%d %d %d %d %d %d: ", winner[0], winner[1], winner[2], winner[3], winner[4], winner[5]);
    printf("%d\n", smallest);

    return 0;
}
