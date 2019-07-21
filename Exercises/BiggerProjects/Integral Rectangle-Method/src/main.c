#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265359
#define F1 funkcja(z+i*dx,a,b)
#define F2 funkcja(z+(i+1)*dx,a,b)

void dane(){
    puts("\\*Program stworzony na potrzeby projektu laboratoryjnego*\\");
    puts("\\*Sluzy do wyliczenia calki z funkcji a*sin(bx) o zadanej dokladnosci*\\");
    puts("\\*za pomoca metody prostokatow z niedomiarem*\\");
    puts("\\*Autorem jest Piotr Zawadka z grupy I2*\\\n");
}

double funkcja(double x, double a, double b){
    return a*sin(b*x);
}

char end(char fin){
    puts("Chcesz zakonczyc program? T/N");
    scanf("%s", &fin);
    while(fin!='N'&&fin!='T'){
        puts("ERROR: Wprowadz wartosc T (TAK) lub N (NIE)");
        while(getchar()!='\n');
        scanf("%s", &fin);
    }
    return fin;
}

int main()
{
    dane();
    puts("Wcisnij ENTER");
    if(getchar());

    char Koniec='N';    //Zmienna konczenia programu

    do{
        double a,b;         //Wspolczynniki
        double z,y;         //Przedzial calkowania
        double dx;          //Przesuniecie x
        double calka=0.0;   //Wynik calkowania
        double wzor;        //Wzor potrzebny gdy f(x) rozne znakowo od f(x+dx)
        unsigned long n;    //Dokladnosc(ilosc prostokatow)
        unsigned long i;    //Licznik
        int p;              //Wspolczynnik procentow

        printf("\033[H\033[2J");    //Linux
        system("clr");              //Windows

        puts("Wpisz wspolczynnik \"a\" tej funkcji");
        while(scanf("%lf", &a)!=1){
            puts("ERROR: Wprowadz poprawne wartosci");
            while(getchar()!='\n');
        }

        if(!a){
            puts("Wynik calkowania to 0\n");
            Koniec=end(Koniec);
            continue;
        }

        while(a<-2E+160||a>2E+160){
            puts("ERROR: Liczba nie miesci sie w zakresie");
            while(getchar()!='\n');
            puts("Wpisz wspolczynnik raz jeszcze z zakresu <-2E+160,2E+160>");
            scanf("%lf", &a);
        }

        puts("Wpisz wspolczynnik \"b\" tej funkcji");
        while(scanf("%lf", &b)!=1){
            puts("ERROR: Wprowadz poprawne wartosci");
            while(getchar()!='\n');
        }

        if(!b){
            puts("Wynik calkowania to 0\n");
            Koniec=end(Koniec);
            continue;
        }

        while(b<-2E+9||b>2E+9){
            puts("ERROR: Liczba nie miesci sie w zakresie");
            while(getchar()!='\n');
            puts("Wpisz wspolczynnik raz jeszcze z zakresu <-2E+9,2E+9>");
            scanf("%lf", &b);
        }

        puts("Wpisz zakres calkowania funkcji. Podaj go za pomoca radianow w formacie: z y; gdzie z<y");
        while(scanf("%lf %lf", &z, &y)!=2){
            puts("ERROR: Wprowadz poprawne wartosci z,y");
            while(getchar()!='\n');
        }
        while(z>y){
            puts("ERROR: Wprowadz wartosci takie, ze z<y");
            while(getchar()!='\n');
            scanf("%lf %lf", &z, &y);
        }

        if(y>0){while(y-(2*PI/abs(b))>=0.0){y-=(2*PI/abs(b));}}
        else {while(y+(2*PI/abs(b))<=0.0){y+=(2*PI/abs(b));}}

        if(z>0){while(z-(2*PI/abs(b))>=0.0){z-=(2*PI/abs(b));}}
        else {while(z+(2*PI/abs(b))<=0.0){z+=(2*PI/abs(b));}}

        if(-y==z || z==y){
            puts("Wynik calkowania to 0\n");
            Koniec=end(Koniec);
            continue;
        }

        puts("Wpisz z jaka dokladnoscia chcesz policzyc te calke [liczba naturalna z zakresu <5,858993449>]\n(im wieksza liczba tym wieksza dokladnosc)");
        puts("Zalecany zakres od <100,10000000>");
        while(scanf("%ld", &n)!=1){
            puts("ERROR: Liczba ta powinna byc calkowita");
            while(getchar()!='\n');
            puts("Wpisz dokladnosc raz jeszcze");
        };
        while(n<5||n>858993449){
            puts("ERROR: Liczba nie miesci sie w zakresie");
            while(getchar()!='\n');
            puts("Wpisz dokladnosc raz jeszcze");
            scanf("%ld", &n);
        }

        printf("\nChcesz scalkowac funkcje: %E*sin(%E*x)\n\n", a, b);

        dx=(y-z)/n;         //Wyliczanie delty x

        for(i=1,p=1;i<=n;i++){          //Petla wyliczajaca calke
            if(p>10){
                puts("ERROR");
                break;
            }
            if(i>=(p*n/5)){
                printf("Wynik dla %d procent to: %E\n", p*20, calka*dx);
                p++;
            }
            if(F1>0 && F2>0){
                if(F1<F2){
                    calka+=F1;
                }
                else {
                    calka+=F2;
                }
            }
            else if(F1<0 && F2<0){
                if(F1>F2){
                    calka+=F1;
                }
                else {
                    calka+=F2;
                }
            }
            else {
                wzor=(F1*F1+F2*F2)/(2*(F1+F2));
                calka+=wzor;
            }
        }

        printf("\nWynikiem tego calkowania jest: %E\n\n", calka*dx);

        Koniec=end(Koniec);

    }while(Koniec=='N');
    return 0;
}
