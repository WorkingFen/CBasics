#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int slate[49][2];
int PC_bars[49][2];
int User_bars[49][2];
int Deck[36][2];
int Table[50][2];
int Slate=49;
int User=7;
int PC=7;
int DECK=35;

///Sprawdzone
void pauza(){       //Pauza
    puts("");
    puts("Wcisnij ENTER");
    if(getchar());
}

///Sprawdzone
void dane(){        //Dane autora
    puts("\\*Program stworzony na potrzeby projektu laboratoryjnego*\\");
    puts("\\*Jest typowa gra w Domino*\\");
    puts("\\*Autorem jest Piotr Zawadka z grupy I2*\\");
}

///Sprawdzone
void slates(){       //Tworzenie tablicy kamieni
    int i,j,k;

    for(j=0,k=0,i=0;j<49;j++){
        if(!(j%7)&&j!=0)k++;
        slate[j][i]=k;
    }
    for(j=0,k=0,i=1;j<49;j++,k++){
        if(k==7)k=0;
        slate[j][i]=k;
    }
}

///Sprawdzone
void put(char way, int j){   //Wybor pierwszego kamienia

    if(way=='L'){
        User--;
        Table[0][0]=User_bars[j][0];
        User_bars[j][0]=User_bars[6][0];
        Table[0][1]=User_bars[j][1];
        User_bars[j][1]=User_bars[6][1];
        printf("[%d|%d]\n", Table[0][0],Table[0][1]);
    }
    else if(way=='P'){
        User--;
        Table[0][0]=User_bars[j][1];
        User_bars[j][1]=User_bars[6][1];
        Table[0][1]=User_bars[j][0];
        User_bars[j][0]=User_bars[6][0];
        printf("[%d|%d]\n", Table[0][0],Table[0][1]);
    }
    else if(way=='0'){
        PC--;
        Table[0][0]=PC_bars[j][0];
        PC_bars[j][0]=PC_bars[6][0];
        Table[0][1]=PC_bars[j][1];
        PC_bars[j][1]=PC_bars[6][1];
        printf("[%d|%d]\n", Table[0][0],Table[0][1]);
    }
    else if(way=='1'){
        PC--;
        Table[0][0]=PC_bars[j][1];
        PC_bars[j][1]=PC_bars[6][1];
        Table[0][1]=PC_bars[j][0];
        PC_bars[j][0]=PC_bars[6][0];
        printf("[%d|%d]\n", Table[0][0],Table[0][1]);
    }
}

///Sprawdzone
int putmoreUser(int j, int i){   //Wybor kolejnych kamieni przez User
    int k;

    if(User_bars[j][0]==Table[i-1][1]){
        User--;
        Table[i][0]=User_bars[j][0];
        User_bars[j][0]=User_bars[User][0];
        Table[i][1]=User_bars[j][1];
        User_bars[j][1]=User_bars[User][1];
        for(k=0;k<i;k++)
            printf("[%d|%d]", Table[k][0],Table[k][1]);
        printf("[%d|%d]\n\n", Table[k][0],Table[k][1]);
        return 0;
    }
    else{
        User--;
        Table[i][0]=User_bars[j][1];
        User_bars[j][1]=User_bars[User][1];
        Table[i][1]=User_bars[j][0];
        User_bars[j][0]=User_bars[User][0];
        for(k=0;k<i;k++)
            printf("[%d|%d]", Table[k][0],Table[k][1]);
        printf("[%d|%d]\n\n", Table[k][0],Table[k][1]);
        return 0;
    }
}

///Sprawdzone
int putmorePC(int j, int i){   //Wybor kolejnych kamieni przez PC
    int k;

    if(PC_bars[j][0]==Table[i-1][1]){
        printf("\033[H\033[2J");
        puts("Tura komputera");
        PC--;
        Table[i][0]=PC_bars[j][0];
        PC_bars[j][0]=PC_bars[PC][0];
        Table[i][1]=PC_bars[j][1];
        PC_bars[j][1]=PC_bars[PC][1];
        for(k=0;k<i;k++)
            printf("[%d|%d]", Table[k][0],Table[k][1]);
        printf("[%d|%d]\n\n", Table[k][0],Table[k][1]);
        return 0;
    }
    else{
        printf("\033[H\033[2J");
        puts("Tura komputera");
        PC--;
        Table[i][0]=PC_bars[j][1];
        PC_bars[j][1]=PC_bars[PC][1];
        Table[i][1]=PC_bars[j][0];
        PC_bars[j][0]=PC_bars[PC][0];
        for(k=0;k<i;k++)
            printf("[%d|%d]", Table[k][0],Table[k][1]);
        printf("[%d|%d]\n\n", Table[k][0],Table[k][1]);
        return 0;
    }
}

///Sprawdzone
void randomize(){   //Losowanie kamieni
    int i;
    int temp;
    srand(time(NULL));
    for(i=0;i<7;i++){       //Dla User
        temp=(rand()%Slate);
        Slate--;
        User_bars[i][0]=slate[temp][0];
        slate[temp][0]=slate[Slate][0];
        User_bars[i][1]=slate[temp][1];
        slate[temp][1]=slate[Slate][1];
        //printf("[%d|%d]", User_bars[i][0],User_bars[i][1]); ///Test
    }
    //puts("");   ///Taktyczny Enter
    for(i=0;i<7;i++){       //Dla PC
        temp=rand()%Slate;
        Slate--;
        PC_bars[i][0]=slate[temp][0];
        slate[temp][0]=slate[Slate][0];
        PC_bars[i][1]=slate[temp][1];
        slate[temp][1]=slate[Slate][1];
        //printf("[%d|%d]", PC_bars[i][0],PC_bars[i][1]); ///Test
    }
    //puts("");   ///Taktyczny Enter
    for(i=0;i<35;i++){      //Reszta kamieni
        temp=rand()%Slate;
        Slate--;
        Deck[i][0]=slate[temp][0];
        slate[temp][0]=slate[Slate][0];
        Deck[i][1]=slate[temp][1];
        slate[temp][1]=slate[Slate][1];
        //printf("[%d|%d]", Deck[i][0],Deck[i][1]);   ///Test
    }
    //puts("");   ///Taktyczny Enter
}

///Sprawdzone
int who(){        //Kto rozpoczyna: 0 komputer, 1 uzytkownik
    srand(time(NULL));
    int num =(rand()%2);
    return num;
}

///Sprawdzone
int start(int Fin){      //Rozpoczecie gry

    int i,j;
    char way;
    int stone;

    int Start=who();
    Fin=Start;

    if(!Start){     //Gdy PC rozpoczyna
        puts("Rozpoczyna komputer");
        srand(time(NULL));
        way=(rand()%2)+'0';
        stone=(rand()%7);
        put(way,stone);
    }
    else if(Start){     //Gdy User rozpoczyna
        puts("Ty rozpoczynasz");
        for(j=0;j<7;j++){
            for(i=0;i<2;i++){
                if(!i) printf("%d. [%d|", j,User_bars[j][i]);
                if(i) printf("%d]\t", User_bars[j][i]);
            }
        }
        printf("\n");
        puts("Ktorym z kamieni chcesz rozpoczac? Wpisz liczbe:");
        scanf("%d", &stone);
        puts("Ktorym krancem chcesz rozpoczac? Prawym 'P' czy lewym 'L'?");
        scanf("%s", &way);
        if(getchar()=='\n');
        while(way!='P'&&way!='L'){
            puts("ERROR: Wprowadz wartosc P (PRAWO) lub L (LEWO)");
            while(getchar()!='\n');
            scanf("%s", &way);
        }
        put(way,stone);
    }
    return Fin;
}

///Sprawdzone
int extraPC(int a){   //Losowanie dodatkowego kamienia PC

    DECK--;
    PC_bars[PC][0]=Deck[DECK][0];
    PC_bars[PC][1]=Deck[DECK][1];


    if(PC_bars[PC][0]==Table[a-1][1]){
        putmorePC(PC,a);
        PC++;
        return 0;
    }
    else if(PC_bars[PC][1]==Table[a-1][1]){
        putmorePC(PC,a);
        PC++;
        return 0;
    }
    else{
        if(DECK<0) return 1;
        PC++;
        extraPC(a);
    }
    return 0;
}

///Sprawdzone
int extraUser(int a){  //Losowanie dodatkowego kamienia User

    DECK--;
    User_bars[User][0]=Deck[DECK][0];
    User_bars[User][1]=Deck[DECK][1];

    if(User_bars[User][0]==Table[a-1][1]){
        putmoreUser(User,a);
        User++;
        return 0;
    }
    else if(User_bars[User][1]==Table[a-1][1]){
        putmoreUser(User,a);
        User++;
        return 0;
    }
    else{
        if(DECK<0) return 1;
        User++;
        extraUser(a);
    }
    return 0;
}

///Sprawdzone
int game(int First){     //Glowna czesc gry

    static int a=1;
    int i,j;
    int stone;
    int ok=0;

    if((First==0)&&(a%2==0)){     //Wybieranie kamieni przez PC
        for(j=0;j<PC;j++){
            if(PC_bars[j][0]==Table[a-1][1]){
                putmorePC(j,a);
                ok=1;
                break;
            }
            else if(PC_bars[j][1]==Table[a-1][1]){
                putmorePC(j,a);
                ok=1;
                break;
            }
        }
        if(!ok) extraPC(a);
    }
    else if((First==1)&&(a%2==1)){      //Wybieranie kamieni przez PC
        for(j=0;j<PC;j++){
            if(PC_bars[j][0]==Table[a-1][1]){
                putmorePC(j,a);
                ok=1;
                break;
            }
            else if(PC_bars[j][1]==Table[a-1][1]){
                putmorePC(j,a);
                ok=1;
                break;
            }
        }
        if(!ok) extraPC(a);
    }
    else if((First==0)&&(a%2==1)){     //Wybieranie kamieni przez User
        puts("Twoja tura");
        for(j=0;j<User;j++){
            for(i=0;i<2;i++){
                if(!i) printf("%d. [%d|", j,User_bars[j][i]);
                if(i) printf("%d]\t", User_bars[j][i]);
            }
        }
        printf("\n");
        puts("Ktory z kamieni chcesz polozyc? Wpisz liczbe:");
        puts("Jezeli nie posiadasz, to wpisz 99");
        scanf("%d", &stone);
        if(stone==99){
            extraUser(a);
            a++;
            return 0;
        }
        while((User_bars[stone][0]!=Table[a-1][1])&&(User_bars[stone][1]!=Table[a-1][1])){
            puts("ERROR: Wybierz inny kamien!");
            while(getchar()!='\n');
            scanf("%d", &stone);
        }
        putmoreUser(stone,a);
    }
    else if((First==1)&&(a%2==0)){     //Wybieranie kamieni przez User
        puts("Twoja tura");
        for(j=0;j<User;j++){
            for(i=0;i<2;i++){
                if(!i) printf("%d. [%d|", j,User_bars[j][i]);
                if(i) printf("%d]\t", User_bars[j][i]);
            }
        }
        printf("\n");
        puts("Ktory z kamieni chcesz polozyc? Wpisz liczbe:");
        puts("Jezeli nie posiadasz, to wpisz 99");
        scanf("%d", &stone);
        if(stone==99){
            extraUser(a);
            a++;
            return 0;
        }
        while((User_bars[stone][0]!=Table[a-1][1])&&(User_bars[stone][1]!=Table[a-1][1])){
            puts("ERROR: Wybierz inny kamien!");
            while(getchar()!='\n');
            scanf("%d", &stone);
        }
        putmoreUser(stone,a);
    }
    a++;
    return 0;
}

int main(){
    ///Ekran startowy
    dane();
    pauza();

    slates();
    randomize();
    printf("\033[H\033[2J");

    int Start=0;
    Start=start(Start);
    pauza();

    do{
        game(Start);
    }while(User!=0 && PC!=0 && DECK>=0);

    printf("\033[H\033[2J");

    if(DECK<0){
        if(User>PC) puts("Przegrales!!!");
        if(User<PC) puts("Wygrales!!!");
        if(User==PC) puts("Remis!!!");
    }
    if(!PC) puts("Przegrales!!!");
    if(!User) puts("Wygrales!!!");

    pauza();

    ///Czyszczenie konsoli
    /*printf("\033[H\033[2J");    //Linux
    system("cls");              //Windows
    */

    return 0;
}
