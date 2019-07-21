#ifndef SORT_H
#define SORT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textoptions.h"

int porownaj_CHA(char* a, char* b){
    int c=strcmp(a,b);

    if(c>0)
        return 1;
    else
        return 0;
}

int porownaj_INT(int a, int b){
    return a>b;
}

int porownaj_FLO(float a, float b){
    return a>b;
}

void zamiana(struct filemp3* wsk){
    struct filemp3* wsk_next = (struct filemp3*)malloc(sizeof(struct filemp3));
    wsk_next = wsk->next;
    struct filemp3* wsk_prev = (struct filemp3*)malloc(sizeof(struct filemp3));
    wsk_prev = wsk->prev;
    struct filemp3* wsk_nextv2 = (struct filemp3*)malloc(sizeof(struct filemp3));
    wsk_nextv2 = wsk_next->next;

    wsk_next->prev = wsk_prev;

    if(wsk_prev)
        wsk_prev->next = wsk_next;

    wsk->next = wsk_nextv2;

    if(wsk_nextv2)
        wsk_nextv2->prev = wsk;

    wsk->prev = wsk_next;
    wsk_next->next = wsk;
    wsk = wsk->prev;
}

void sortuj(int mode){
    int n = 0,i,j;
    struct filemp3 *wsk = pierwszy;

    while(wsk){
        n++;
        wsk = wsk->next;
    }

    for(i=0; i<n; i++){
        wsk = pierwszy;
        for(j=0; j<n-i-1; j++){
            switch(mode){
                case 1:
                    if(porownaj_INT(wsk->ID, wsk->next->ID)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 2:
                    if(porownaj_CHA(wsk->author, wsk->next->author)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 3:
                    if(porownaj_CHA(wsk->title, wsk->next->title)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 4:
                    if(porownaj_CHA(wsk->album, wsk->next->album)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 5:
                    if(wsk->minutes==wsk->next->minutes){
                        if(porownaj_INT(wsk->seconds, wsk->next->seconds)){
                            zamiana(wsk);
                            if(!j)
                                pierwszy = wsk;
                        }
                    }
                    else if(porownaj_INT(wsk->minutes, wsk->next->fsize)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 6:
                    if(porownaj_INT(wsk->bitrate.bits, wsk->next->bitrate.bits)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                case 7:
                    if(porownaj_FLO(wsk->fsize, wsk->next->fsize)){
                        zamiana(wsk);
                        if(!j)
                            pierwszy = wsk;
                    }
                break;

                default:
                    i=n;
                break;
            }
            wsk = wsk->next;
        }
    }
}

#endif // SORT_H
