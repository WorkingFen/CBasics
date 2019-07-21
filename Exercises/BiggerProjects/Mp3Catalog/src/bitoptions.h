#ifndef BITOPTIONS_H
#define BITOPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void pauza(){       //Pauza   ///Sprawdzone
    puts("");
    puts("Wcisnij ENTER");
    if(getchar());
}


struct bit{
    int bits;
    struct bit* next;
};

struct bit* pierwszybit = NULL;
struct bit* ostatnibit = NULL;

struct bit* utworz_bit(int bits){   ///Sprawdzone
    struct bit* wsk = (struct bit*)malloc(sizeof(struct bit));
    if(wsk == NULL)
    {
        printf("Nieudana proba utworzenia pierwszego elementu listy!\n");
        return NULL;
    }

    wsk->bits = bits;
    wsk->next = NULL;

    pierwszybit = ostatnibit = wsk;
    return wsk;
}

struct bit* dodaj_bit(int bits){   ///Sprawdzone
    if(pierwszybit == NULL)
        return (utworz_bit(bits));

    struct bit* wsk = (struct bit*)malloc(sizeof(struct bit));
    if(wsk == NULL){
        printf("Nieudana proba utworzenia nowego elementu listy!\n");
        return NULL;
    }
    wsk->bits = bits;
    wsk->next = NULL;

    ostatnibit->next = wsk;
    ostatnibit = wsk;

    return wsk;
}

struct bit* szukaj_bit(int bits, struct bit** poprzednibit){  ///Sprawdzone
    struct bit* wsk = pierwszybit;
    struct bit* tmp = NULL;
    int znaleziony = 0;

    while(wsk != NULL){
        if(wsk->bits == bits){
            znaleziony = 1;
            break;
        }
        else{
            tmp = wsk;
            wsk = wsk->next;
        }
    }

    if(znaleziony){
        if(poprzednibit)
            *poprzednibit = tmp;
        return wsk;
    }
    else
        return NULL;
}

struct bit* szukaj_bitu(int bits){  ///Sprawdzone
    struct bit* wsk = pierwszybit;
    int znaleziony = 0;

    while(wsk != NULL){
        if(wsk->bits == bits){
            znaleziony = 1;
            break;
        }
        else{
            wsk = wsk->next;
        }
    }

    if(znaleziony){
        return (struct bit*)1;
    }
    else
        return 0;
}

int skasuj_bit(int bits){  ///Sprawdzone
    struct bit* poprzednibit = NULL;
    struct bit* do_skasowania = NULL;

    printf("...Kasowanie wartosci z listy bitrate\n");

    do_skasowania = szukaj_bit(bits, &poprzednibit);

	if(do_skasowania == NULL)
        return -1;
    else{
        if(poprzednibit != NULL)
            poprzednibit->next = do_skasowania->next;

        if(do_skasowania == ostatnibit)
            ostatnibit = poprzednibit;
        else if(do_skasowania == pierwszybit)
            pierwszybit = do_skasowania->next;
    }

    free(do_skasowania);
    do_skasowania = NULL;

    return 0;
}

int edytuj_bit(int bits){  ///Sprawdzone
    struct bit* do_edycji = NULL;
    struct bit* brak = NULL;
    int bit2;

    printf("...Edytowanie wartosci z listy bitrate\n");

    do_edycji = szukaj_bit(bits, &brak);

	if(do_edycji == NULL)
        return -1;
    else{
        puts("Wpisz wartosc bitrate po edycji");
        scanf("%d",&bit2);
        if(szukaj_bitu(bit2)){
            puts("Istnieje juz taki bitrate");
            if(getchar());
            pauza();
        }
        else
            do_edycji->bits = bit2;
    }

    return 0;
}

int wyczysc_bit(){     /// Sprawdzone
    struct bit* do_skasowania = NULL;
    int koniec=0;

    printf("...Kasowanie wartosci z listy elementow\n");

    while(!koniec){
        if(pierwszybit==NULL)
            return -1;

        do_skasowania = pierwszybit->next;

        if(do_skasowania == NULL)
            do_skasowania=pierwszybit;

        if(pierwszybit != NULL)
            pierwszybit->next = do_skasowania->next;

        if(do_skasowania == pierwszybit){
            koniec=1;
        }

        free(do_skasowania);
        do_skasowania = NULL;

    }
    free(pierwszybit);
    pierwszybit=NULL;
    return 0;
}

void wydrukuj_bit(){   ///Sprawdzone
    struct bit* wsk = pierwszybit;
    if(wsk == NULL)
    	printf("Lista jest pusta!\n");
	else{
	    printf("\n ------- Wydruk listy / Poczatek ------- \n");
	    printf("Bitrate\t\n");
	    while(wsk != NULL){
	        printf("%3d kbit/s\n",wsk->bits);
	        wsk = wsk->next;
	    }
	    printf("------- Wydruk listy / Koniec --------- \n");
	}
    return;
}

#endif // BITOPTIONS_H
