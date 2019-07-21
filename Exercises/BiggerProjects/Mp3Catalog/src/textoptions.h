#ifndef TEXTOPTIONS_H
#define TEXTOPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitoptions.h"

struct filemp3{
    int ID;
    char author[21];
    char title[21];
    char album[21];
    int minutes;
    int seconds;
    struct bit bitrate;
    float fsize;
    struct filemp3* next;
    struct filemp3* prev;
};

struct filemp3* pierwszy = NULL;
struct filemp3* ostatni = NULL;

struct filemp3* utworz_liste(char* author, char* title, char* album, int minutes, int seconds, struct bit* bitrate, float fsize, int bits){     ///Sprawdzone
    printf("Utworzenie listy");
    struct filemp3* wsk = (struct filemp3*)malloc(sizeof(struct filemp3));
    if(wsk == NULL)
    {
        printf("Nieudana proba utworzenia pierwszego elementu listy!\n");
        return NULL;
    }

    struct bit* poprzednibit = NULL;

    bitrate = szukaj_bit(bits, &poprzednibit);

    wsk->ID = 0;
    strncpy(wsk->author, author, 21);
    strncpy(wsk->title, title, 21);
    strncpy(wsk->album, album, 21);
    wsk->minutes = minutes;
    wsk->seconds = seconds;
    wsk->bitrate.bits = bitrate->bits;
    wsk->fsize = fsize;
    wsk->next = NULL;
    wsk->prev = NULL;

    pierwszy = ostatni = wsk;
    return wsk;
}

struct filemp3* dodaj_do_listy(char* author, char* title, char* album, int minutes, int seconds, struct bit* bitrate, float fsize, int bits){   ///Sprawdzone
    if(pierwszy == NULL)
        return (utworz_liste(author, title, album, minutes, seconds, bitrate, fsize, bits));

    printf("Dodanie elementu listy\n");

    struct bit* poprzednibit = NULL;

    struct filemp3* wsk = (struct filemp3*)malloc(sizeof(struct filemp3));
    if(wsk == NULL){
        printf("Nieudana proba utworzenia nowego elementu listy!\n");
        return NULL;
    }

    bitrate = szukaj_bit(bits, &poprzednibit);

    wsk->ID = (ostatni->ID)+1;
    strncpy(wsk->author, author, 21);
    strncpy(wsk->title, title, 21);
    strncpy(wsk->album, album, 21);
    wsk->minutes = minutes;
    wsk->seconds = seconds;
    wsk->bitrate.bits = bitrate->bits;
    wsk->fsize = fsize;
    wsk->next = NULL;
    wsk->prev = ostatni;

    ostatni->next = wsk;
    ostatni = wsk;

    return wsk;
}

struct filemp3* szukaj_ID(int ID){  ///Sprawdzone
    struct filemp3* wsk = pierwszy;
    int znaleziony = 0;

    while(wsk != NULL){
        if(wsk->ID == ID){
            znaleziony = 1;
            break;
        }
        else{
            wsk = wsk->next;
        }
    }

    if(znaleziony){
        return (struct filemp3*)1;
    }
    else
        return 0;
}

struct filemp3* przeszukaj_liste(int ID, struct filemp3** poprzedni){  ///Sprawdzone
    struct filemp3* wsk = pierwszy;
    struct filemp3* tmp = NULL;
    int znaleziony = 0;

    printf("...Przeszukiwanie listy\n");

    while(wsk != NULL){
        if(wsk->ID == ID){
            znaleziony = 1;
            break;
        }
        else{
            tmp = wsk;
            wsk = wsk->next;
        }
    }

    if(znaleziony){
        if(poprzedni)
            *poprzedni = tmp;
        return wsk;
    }
    else
        return NULL;
}

int skasuj_wartosc_z_listy(int ID){   ///Sprawdzone
    struct filemp3* poprzedni = NULL;
    struct filemp3* do_skasowania = NULL;

    printf("...Kasowanie wartosci z listy elementow\n");

    do_skasowania = przeszukaj_liste(ID, &poprzedni);

	if(do_skasowania == NULL)
        return -1;
    else{
        if(poprzedni != NULL){
            poprzedni->next = do_skasowania->next;
            do_skasowania->prev=do_skasowania->next->prev;
        }

        if(do_skasowania == ostatni)
            ostatni = poprzedni;
        else if(do_skasowania == pierwszy){
            pierwszy = do_skasowania->next;
            do_skasowania->prev=NULL;
        }
    }

    free(do_skasowania);
    do_skasowania = NULL;

    return 0;
}

int wyczysc_baze(){     /// Sprawdzone
    struct filemp3* do_skasowania = NULL;
    int koniec=0;

    printf("...Kasowanie wartosci z listy elementow\n");

    while(!koniec){
        if(pierwszy==NULL)
            return -1;

        do_skasowania = pierwszy->next;

        if(do_skasowania == NULL)
            do_skasowania=pierwszy;

        if(pierwszy != NULL)
            pierwszy->next = do_skasowania->next;

        if(do_skasowania == pierwszy){
            koniec=1;
        }

        free(do_skasowania);
        do_skasowania = NULL;

    }
    free(pierwszy);
    pierwszy=NULL;
    return 0;
}

int edytuj_z_listy(int ID){    ///Sprawdzone
    struct filemp3* do_edycji = NULL;
    struct filemp3* brak = NULL;
    int x=1;
    char* author;
    char* title;
    char* album;
    int minutes, seconds, bits;
    float fsize;

    printf("...Edytowanie wartosci z listy elementow\n");

    do_edycji = przeszukaj_liste(ID, &brak);

	if(do_edycji == NULL)
        return -1;
    else{
        while(x!=0){
            puts("\\*Wpisz numer elementu, ktory chcesz zmienic*\\");
            puts("\\*1. Autora*\\");
            puts("\\*2. Tytul*\\");
            puts("\\*3. Album*\\");
            puts("\\*4. Czas*\\");
            puts("\\*5. Bitrate*\\");
            puts("\\*6. Wielkosc pliku*\\");
            puts("\\*0. Nic nie zmieniaj*\\");
            puts("");
            scanf("%d", &x);
            switch(x){
                case 1:
                    while(getchar()!='\n');
                    author = (char*)malloc(21*sizeof(char));
                    puts("Wpisz autora jaki ma widniec po edycji");
                    fgets(author, 21, stdin);
                    author[strcspn(author, "\n")] = 0;
                    strncpy(do_edycji->author, author, 21);
                break;

                case 2:
                    while(getchar()!='\n');
                    title = (char*)malloc(21*sizeof(char));
                    puts("Wpisz tytul jaki ma byc po edycji");
                    fgets(title, 21, stdin);
                    title[strcspn(title, "\n")] = 0;
                    strncpy(do_edycji->title, title, 21);
                break;

                case 3:
                    while(getchar()!='\n');
                    album = (char*)malloc(21*sizeof(char));
                    puts("Wpisz album, ktory ma byc pokazywany po edycji");
                    fgets(album, 21, stdin);
                    album[strcspn(album, "\n")] = 0;
                    strncpy(do_edycji->album, album, 21);
                break;

                case 4:
                    puts("Wpisz minuty i sekundy, dla czasu trwania piosenki");
                    scanf("%02d%02d",&minutes, &seconds);
                    do_edycji->minutes = minutes;
                    do_edycji->seconds = seconds;
                break;

                case 5:
                    puts("Wpisz wartosc bitrate z listy po edycji");
                    scanf("%3d",&bits);
                    if(!szukaj_bitu(bits)){
                        puts("Nie ma takiego bitrate'u!");
                        if(getchar());
                        pauza();
                        continue;
                    }
                    do_edycji->bitrate.bits = bits;
                break;

                case 6:
                    puts("Wpisz wartosc bitrate po edycji");
                    scanf("%6f",&fsize);
                    do_edycji->fsize = fsize;
                break;

                case 0:
                    x=0;
                break;
            }
        }

    }

    return 0;
}

void wydrukuj_liste(){    ///Sprawdzone
    struct filemp3* wsk = pierwszy;
    if(wsk == NULL)
    	printf("Lista jest pusta!\n");
	else{
	    printf("\n ------- Wydruk listy / Poczatek ------- \n");
	    printf("No. Autor\t\t  Tytul\t\t\tAlbum\t\t\tCzas\t  Bitrate\t Rozmiar\t");
	    printf("\n\t ------------------------------------------------------------------------------- \n");
	    while(wsk != NULL){
	        printf("%d   %-20s  %-20s  %-20s    %02d:%02d\t  %3d kbit/s\t %6f MB\t\n",wsk->ID, wsk->author, wsk->title, wsk->album, wsk->minutes, wsk->seconds, wsk->bitrate.bits, wsk->fsize);
	        wsk = wsk->next;
	    }
	    printf("------- Wydruk listy / Koniec --------- \n");
	}
    return;
}

#endif // TEXTOPTIONS_H
