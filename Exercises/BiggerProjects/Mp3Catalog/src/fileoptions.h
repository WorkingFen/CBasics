#ifndef FILEOPTIONS_H
#define FILEOPTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitoptions.h"
#include "textoptions.h"

struct filemp3* utworz_liste_z_pliku(int ID, char* author, char* title, char* album, int minutes, int seconds, int bits, float fsize){     ///Sprawdzone
    printf("Utworzenie listy");
    struct filemp3* wsk = (struct filemp3*)malloc(sizeof(struct filemp3));
    if(wsk == NULL)
    {
        printf("Nieudana proba utworzenia pierwszego elementu listy!\n");
        return NULL;
    }

    wsk->ID = ID;
    strncpy(wsk->author, author, 21);
    strncpy(wsk->title, title, 21);
    strncpy(wsk->album, album, 21);
    wsk->minutes = minutes;
    wsk->seconds = seconds;
    wsk->bitrate.bits = bits;
    wsk->fsize = fsize;
    wsk->next = NULL;
    wsk->prev = NULL;

    pierwszy = ostatni = wsk;
    return wsk;
}

struct filemp3* dodaj_do_pliku(int ID, char* author, char* title, char* album, int minutes, int seconds, int bits, float fsize){   ///Sprawdzone
    if(pierwszy == NULL)
        return (utworz_liste_z_pliku(ID, author, title, album, minutes, seconds, bits, fsize));

    struct filemp3* wsk = (struct filemp3*)malloc(sizeof(struct filemp3));
    if(wsk == NULL){
        printf("Nieudana proba utworzenia nowego elementu listy!\n");
        return NULL;
    }

    wsk->ID = ID;
    strncpy(wsk->author, author, 21);
    strncpy(wsk->title, title, 21);
    strncpy(wsk->album, album, 21);
    wsk->minutes = minutes;
    wsk->seconds = seconds;
    wsk->bitrate.bits = bits;
    wsk->fsize = fsize;
    wsk->next = NULL;
    wsk->prev = ostatni;

    ostatni->next = wsk;
    ostatni = wsk;

    return wsk;
}

void zapisz_bit(FILE* plik_bitu){   ///Sprawdzone
    struct bit* wsk = pierwszybit;
    if(wsk == NULL)
    	return;
	else{
	    while(wsk != NULL){
	        fprintf(plik_bitu, "%x ", wsk->bits);
	        wsk = wsk->next;
	    }
	}
    return;
    fclose(plik_bitu);
}

void zapisz_do_pliku(FILE* plik){      ///Sprawdzone
    struct filemp3* wsk = pierwszy;
    if(wsk == NULL)
    	return;
	else{
	    while(wsk != NULL){
	        fprintf(plik, "%d %s %s %s %d %d %d %f\n", wsk->ID, wsk->author, wsk->title, wsk->album, wsk->minutes, wsk->seconds, wsk->bitrate.bits, wsk->fsize);
	        wsk = wsk->next;
	    }

	}
    return;
    fclose(plik);
}

void odczytaj_bit(FILE* plik_bitu){     ///Sprawdzone
    wyczysc_bit();
    int bits;

    while(!feof(plik_bitu)){
        fscanf(plik_bitu, "%x ", &bits);
        dodaj_bit(bits);
	}
    return;
    fclose(plik_bitu);
}

void odczyt_z_pliku(FILE* plik){    ///Sprawdzone
    wyczysc_baze();
    int bits;
    int ID;
    int minutes, seconds;
    char* author = (char*)malloc(21*sizeof(char));
    char* title = (char*)malloc(21*sizeof(char));
    char* album = (char*)malloc(21*sizeof(char));
    float fsize;

    while(!feof(plik)){
        fscanf(plik, "%d %s %s %s %d %d %d %f\n", &ID, author, title, album, &minutes, &seconds, &bits, &fsize);
        dodaj_do_pliku(ID, author, title, album, minutes, seconds, bits, fsize);
    }
    return;
    fclose(plik);
}

#endif // FILEOPTIONS_H
