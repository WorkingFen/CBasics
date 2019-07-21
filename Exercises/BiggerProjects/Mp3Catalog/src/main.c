#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "textoptions.h"
#include "bitoptions.h"
#include "sort.h"
#include "fileoptions.h"

void dane(){        //Dane autora ///Sprawdzone
    puts("|||||\tProgram stworzony na potrzeby projektu laboratoryjnego");
    puts("|||||\tProgram ten tworzy baze danych dalej zwana Katalogiem MP3");
    puts("|||||\tAutorem jest Piotr Zawadka z grupy I2");
}

void Info(){        //Informacja   ///Sprawdzone
    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
    puts("\\*1. Dodaj liste z pliku*\\");
    puts("\\*2. Zapisz liste w pliku*\\");
    puts("\\*3. Dodaj element do listy*\\");
    puts("\\*4. Skasuj element z listy*\\");
    puts("\\*5. Edytuj element z listy*\\");
    puts("\\*6. Posortuj liste*\\");
    puts("\\*7. Zaprezentuj katalog MP3*\\");
    puts("\\*8. Wyczysc cala baze*\\");
    puts("\\*9. Dzialania na bitrate*\\");
    puts("\\*0. Zakoncz program*\\");
    puts("");
}

void Infobit(){     //Informacja o bitrate  ///Sprawdzone
    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
    puts("\\*1. Dodaj bitrate do puli*\\");
    puts("\\*2. Skasuj bitrate z puli*\\");
    puts("\\*3. Edytuj bitrate z puli*\\");
    puts("\\*4. Wydrukuj bitrate*\\");
    puts("\\*5-0. Wroc do menu*\\");
    puts("");
}

void Infosortuj(){     //Informacja o sortowaniu  ///Sprawdzone
    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
    puts("\\*1. Sortuj za pomoca ID*\\");
    puts("\\*2. Sortuj za pomoca autora*\\");
    puts("\\*3. Sortuj za pomoca tytulu*\\");
    puts("\\*4. Sortuj za pomoca albumu*\\");
    puts("\\*5. Sortuj za pomoca czasu*\\");
    puts("\\*6. Sortuj za pomoca bitrate'u*\\");
    puts("\\*7. Sortuj za pomoca wielkosci pliku*\\");
    puts("\\*8-0. Nie sortuj*\\");
    puts("");
}

void bity(){        //Poczatkowa lista bitrate   ///Sprawdzone
    dodaj_bit(32);
    dodaj_bit(96);
    dodaj_bit(128);
    dodaj_bit(256);
    dodaj_bit(320);
}

int main(){
    ///Ekran startowy
    dane();
    pauza();
    printf("\033[H\033[2J");

    srand(time(NULL));

    int guard, fighter;
    int mode;
    int bits;
    int ID;
    int minutes, seconds;
    int x=1, y, koniec;
    char* author = (char*)malloc(21*sizeof(char));
    char* title = (char*)malloc(21*sizeof(char));
    char* album = (char*)malloc(21*sizeof(char));
    float fsize;

    struct bit* bitrate=(struct bit*)malloc(sizeof(struct bit));

    bity();

    while(x){
        printf("\033[H\033[2J");
        Info();
        scanf("%d",&x);
        switch(x){
            case 1:   /// Wczytywanie bazy z pliku ///Sprawdzone
                printf("\033[H\033[2J");
                puts("Wpisz z jakiego pliku chcesz odczytac bitrate (max 20 znakow wraz z rozszerzeniem)");
                char* bit_plik_ot = (char*)malloc(30*sizeof(char));
                scanf("%s", bit_plik_ot);

                puts("Wpisz z jakiego pliku chcesz odczytac dane (max 20 znakow wraz z rozszerzeniem)");
                char* otworz = (char*)malloc(30*sizeof(char));
                scanf("%s", otworz);

                FILE*plik_bitu_ot;
                FILE*odczyt;
                if ((plik_bitu_ot=fopen(bit_plik_ot, "r"))!=NULL){
                    printf("Otworzono plik z bitrate %s\n", bit_plik_ot);
                    odczytaj_bit(plik_bitu_ot);
                    wydrukuj_bit();
                }
                else
                    printf("Plik %s nie zostal otworzony \n", bit_plik_ot);

                if ((odczyt=fopen(otworz, "r"))!=NULL){
                    printf("Otworzono plik tekstowy %s\n", otworz);
                    odczyt_z_pliku(odczyt);
                    wydrukuj_liste();
                }
                else
                    printf("Plik %s nie zostal otworzony \n", otworz);

                fclose(plik_bitu_ot);
                fclose(odczyt);
                free(bit_plik_ot);
                free(otworz);
                if(getchar());
                pauza();
            break;

            case 2:    /// Zapisywanie bazy w pliku  ///Sprawdzone
                printf("\033[H\033[2J");
                puts("Wpisz do jakiego pliku chcesz zapisac bitrate (max 20 znakow wraz z rozszerzeniem)");
                char* bit_plik = (char*)malloc(30*sizeof(char));
                scanf("%s", bit_plik);

                puts("Wpisz do jakiego pliku chcesz zapisac dane (max 20 znakow wraz z rozszerzeniem)");
                char* zapisz = (char*)malloc(30*sizeof(char));
                scanf("%s", zapisz);

                FILE*plik_bitu;
                FILE*zapis;
                if ((plik_bitu=fopen(bit_plik, "w"))!=NULL){
                    printf("Utworzono plik z bitrate %s\n", bit_plik);
                    zapisz_bit(plik_bitu);
                    wydrukuj_bit();
                }
                else
                    printf("Plik %s nie zostal utworzony \n", bit_plik);

                if ((zapis=fopen(zapisz, "w"))!=NULL){
                    printf("Utworzono plik tekstowy %s\n", zapisz);
                    zapisz_do_pliku(zapis);
                    wydrukuj_liste();
                }
                else
                    printf("Plik %s nie zostal utworzony \n", zapisz);

                fclose(plik_bitu);
                fclose(zapis);
                free(bit_plik);
                free(zapisz);
                if(getchar());
                pauza();
            break;

            case 3:    /// Dodawanie elementu do bazy  ///Sprawdzone
                koniec=1;
                while(koniec){
                    printf("\033[H\033[2J");
                    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
                    puts("\\*1. Dodaj element do listy*\\");
                    puts("\\*2-0. Wroc do menu*\\");
                    puts("");
                    scanf("%d", &y);
                    switch(y){
                        case 1:
                            printf("\033[H\033[2J");
                            puts("Prosze wpisac odpowiednio wartosci dla nowego elementu bazy");
                            puts("Wpisz autora (zamiast spacji wpisz _ )");
                            if(getchar());
                            fgets(author, 21, stdin);
                            puts("Wpisz tytul (zamiast spacji wpisz _ )");
                            author[strcspn(author, "\n")] = 0;
                            fgets(title, 21, stdin);
                            puts("Wpisz album (zamiast spacji wpisz _ )");
                            title[strcspn(title, "\n")] = 0;
                            fgets(album, 21, stdin);
                            puts("Wpisz minuty i sekundy");
                            album[strcspn(album, "\n")] = 0;
                            scanf("%02d %02d", &minutes, &seconds);
                            if(seconds>=60){
                                minutes+=(seconds/60);
                                seconds=(seconds%60);
                            }
                            wydrukuj_bit();
                            puts("Wpisz bitrate");
                            scanf("%3d", &bits);
                            if(!szukaj_bitu(bits)){
                                printf("\033[H\033[2J");
                                puts("Nie ma takiego bitrate'u!");
                                if(getchar());
                                pauza();
                                continue;
                            }
                            puts("Wpisz rozmiar pliku w MB");
                            scanf("%6f", &fsize);
                            dodaj_do_listy(author, title, album, minutes, seconds, bitrate, fsize, bits);
                        break;

                        default:
                            koniec=0;
                            wydrukuj_liste();
                            if(getchar());
                            pauza();
                        break;
                    }
                }
            break;

            case 4:  /// Kasowanie elementu z bazy /// Sprawdzone
                koniec=1;
                while(koniec){
                    printf("\033[H\033[2J");
                    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
                    puts("\\*1. Skasuj element z listy*\\");
                    puts("\\*2-0. Wroc do menu*\\");
                    puts("");
                    scanf("%d", &y);
                    switch(y){
                        case 1:
                            printf("\033[H\033[2J");
                            wydrukuj_liste();
                            puts("Prosze wpisac ID elementu, ktory ma zostac skasowany");
                            scanf("%d", &ID);
                            if(!szukaj_ID(ID)){
                                printf("\033[H\033[2J");
                                puts("Nie ma takiego elementu!");
                                wydrukuj_liste();
                                if(getchar());
                                pauza();
                                continue;
                            }
                            skasuj_wartosc_z_listy(ID);
                        break;

                        default:
                            printf("\033[H\033[2J");
                            koniec=0;
                            puts("Lista po skasowaniu elementow");
                            wydrukuj_liste();
                            if(getchar());
                            pauza();
                        break;
                    }
                }
            break;

            case 5:  /// Edytowanie bazy /// Sprawdzone
                koniec=1;
                while(koniec){
                    printf("\033[H\033[2J");
                    puts("\\*Wpisz numer akcji, ktora chcesz wykonac*\\");
                    puts("\\*1. Edytuj element z listy*\\");
                    puts("\\*2-0. Wroc do menu*\\");
                    puts("");
                    scanf("%d", &y);
                    switch(y){
                        case 1:
                            printf("\033[H\033[2J");
                            wydrukuj_liste();
                            puts("Prosze wpisac ID elementu, ktory ma zostac edytowany");
                            scanf("%d", &ID);
                            if(!szukaj_ID(ID)){
                                printf("\033[H\033[2J");
                                puts("Nie ma takiego elementu!");
                                wydrukuj_liste();
                                if(getchar());
                                pauza();
                                continue;
                            }
                            edytuj_z_listy(ID);
                        break;

                        default:
                            printf("\033[H\033[2J");
                            koniec=0;
                            puts("Lista po edycji elementu");
                            wydrukuj_liste();
                            if(getchar());
                            pauza();
                        break;
                    }
                }
            break;

            case 6:  /// Sortowanie bazy
                printf("\033[H\033[2J");
                Infosortuj();
                scanf("%d", &mode);
                sortuj(mode);
                wydrukuj_liste();
                if(getchar());
                pauza();
            break;

            case 7:  /// Drukowanie bazy ///Sprawdzone
                printf("\033[H\033[2J");
                wydrukuj_liste();
                if(getchar());
                pauza();
            break;

            case 8: /// Kasowanie bazy ///Sprawdzone
                printf("\033[H\033[2J");
                puts("Czy na pewno chcesz skasowac cala baze?");
                guard=rand()%10;
                printf("Wpisz podana liczbe, by wykonac to dzialanie: %d ", guard);
                scanf("%d", &fighter);
                if(guard==fighter){
                    wyczysc_baze();
                    wydrukuj_liste();
                    if(getchar());
                    pauza();
                    continue;
                }
                puts("Wartosci z listy nie zostaly skasowane");
                if(getchar());
                pauza();
            break;

            case 9: /// Dzialanie na bitrate ///Sprawdzone
                y=1;
                while(y){
                    printf("\033[H\033[2J");
                    Info();
                    Infobit();
                    scanf("%d", &y);
                    switch(y){
                        case 1:  /// Dodawanie nowego bitrate
                            printf("\033[H\033[2J");
                            puts("Prosze wpisac bitrate, ktory ma zostac dodany do puli");
                            scanf("%3d", &bits);
                            if(szukaj_bitu(bits)){
                                printf("\033[H\033[2J");
                                puts("Istnieje juz taki bitrate!");
                                wydrukuj_bit();
                                if(getchar());
                                pauza();
                                continue;
                            }
                            dodaj_bit(bits);
                            wydrukuj_bit();
                            if(getchar());
                            pauza();
                        break;

                        case 2:   /// Kasowanie bitrate
                            printf("\033[H\033[2J");
                            wydrukuj_bit();
                            puts("Prosze wpisac bitrate, ktory ma zostac skasowany z puli");
                            scanf("%3d", &bits);
                            if(!szukaj_bitu(bits)){
                                printf("\033[H\033[2J");
                                puts("Nie ma takiego bitrate'u!");
                                wydrukuj_bit();
                                if(getchar());
                                pauza();
                                continue;
                            }
                            skasuj_bit(bits);
                            printf("\033[H\033[2J");
                            puts("Lista po skasowaniu elementu");
                            wydrukuj_bit();
                            if(getchar());
                            pauza();
                        break;

                        case 3:   /// Edytowanie bitrate
                            printf("\033[H\033[2J");
                            wydrukuj_bit();
                            puts("Prosze wpisac bitrate, ktory ma zostac edytowany");
                            scanf("%3d", &bits);
                            if(!szukaj_bitu(bits)){
                                printf("\033[H\033[2J");
                                puts("Nie ma takiego bitrate'u!");
                                wydrukuj_bit();
                                if(getchar());
                                pauza();
                                continue;
                            }
                            edytuj_bit(bits);
                            printf("\033[H\033[2J");
                            puts("Lista po edycji elementu");
                            wydrukuj_bit();
                            if(getchar());
                            pauza();
                        break;

                        case 4:   /// Prezentacja listy bitrate
                            printf("\033[H\033[2J");
                            wydrukuj_bit();
                            if(getchar());
                            pauza();
                        break;

                        default:
                            y=0;
                        break;
                    }
                }
            break;

            default:
                free(author);
                free(title);
                free(album);
                free(bitrate);
                wyczysc_baze();
                x=0;
            break;
        }
    }

    ///Czyszczenie konsoli
    /*printf("\033[H\033[2J");    //Linux
    system("cls");              //Windows
    */

    return 0;
}
