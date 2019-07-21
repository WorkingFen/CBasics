#include <stdio.h>
#include <string.h>

int szescian(int q) {
    int j;
    for(j=1;j<=100;j++) {
            if (j*j*j == q)
                return q;
        }
        return 0;
}

int main()
{
    int i,j;
    int n;
    int tablica[1000];
    int ok;
    int ciag = 0;
    int najwieksza = 0;
    int sze = 0;

    FILE*quest=fopen("ciagi.txt", "r");
    FILE*wrong=fopen("bledne.txt", "r");
    FILE*ans=fopen("wyniki.txt", "w");
    FILE*ans2=fopen("wyniki2.txt", "w");
    FILE*ans3=fopen("wyniki3.txt", "w");

    for(i=0;i<1000;i++) {
        fscanf (quest, "%d", &n);
        for(j=0;j<n;j++)
            fscanf(quest, "%d", &tablica[j]);

        ok = 1;

        for(j=2;j<n;j++)
            if (tablica[j]-tablica[j-1] != tablica[1]-tablica[0])
                ok=0;

        if(ok) {
            ciag++;
            if (tablica[1]-tablica[0] > najwieksza)
                najwieksza = tablica[1]-tablica[0];
        }

        sze = 0;

        for(j=n;j>=0;j--)
           if (szescian(tablica[j]))
                if (tablica[j]>sze)
                    sze = tablica[j];

         if(sze) {
            fprintf(ans2, "Najwiekszy szescian: %d\n", sze);
            printf ("Najwiekszy szescian: %d\n", sze);
        }
    }
    fclose(quest);

    for(i=0;i<20;i++) {
        fscanf (wrong, "%d", &n);
        fscanf (wrong, "%d", &tablica[0]);
        fscanf (wrong, "%d", &tablica[1]);
        for(j=2;j<n;j++)
            fscanf(wrong, "%d", &tablica[j]);

        for(j=2;j<n;){
            if(tablica[j]-tablica[j-1]==tablica[j-1]-tablica[j-2]){
                if(tablica[j+1]-tablica[j]==tablica[j]-tablica[j-1]){
                    if(tablica[j+2]-tablica[j+1]!=tablica[j+1]-tablica[j]){
                        printf("Zla liczba ciagu to: %d\n", tablica[j+2]);
                        fprintf(ans3, "Zla liczba ciagu to: %d\n", tablica[j+2]);
                        break;
                    }
                    else {
                        j++;
                    }
                }
                else {
                    printf("Zla liczba ciagu to: %d\n", tablica[j+1]);
                    fprintf(ans3, "Zla liczba ciagu to: %d\n", tablica[j+1]);
                    break;
                }
            }
            else if(tablica[j+1]-tablica[j]==tablica[j]-tablica[j-1]){
                printf("Zla liczba ciagu to: %d\n", tablica[j-2]);
                fprintf(ans3, "Zla liczba ciagu to: %d\n", tablica[j-2]);
                break;
            }
            else if(tablica[j+2]-tablica[j+1]==tablica[j+1]-tablica[j]){
                printf("Zla liczba ciagu to: %d\n", tablica[j-1]);
                fprintf(ans3, "Zla liczba ciagu to: %d\n", tablica[j-1]);
                break;
            }
            else {
                printf("Zla liczba ciagu to: %d\n", tablica[j]);
                fprintf(ans3, "Zla liczba ciagu to: %d\n", tablica[j]);
                break;
            }
        }
    }
    printf("Liczba ciagow: %d\n", ciag);
    printf("Najwieksza roznica: %d\n", najwieksza);
    fprintf(ans, "Liczba ciagow: %d\n", ciag);
    fprintf(ans, "Najwieksza roznica: %d\n", najwieksza);


    return 0;
}
