#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include "monitor.h"

#define LIMIT 9
#define PRODUCERS 2

//gcc semaphores.c -o program -pthread -std=c99

typedef struct {
    int tab[9];
}que;

typedef struct {
    que tal;
    int count;
    Condition consume_even;
    Condition consume_odd;
    Monitor mutex;
    Condition producer;
}all;

int tail=0, head=-1;
all* commune;

int check();
void del();
void insert(int);
int size();

int consumer_even();
int consumer_odd();
int producers(int);

int main(int argc, char** argv) {

    pid_t even;
    pid_t odd;
    pid_t producersPID[PRODUCERS];

    commune = mmap(NULL, sizeof(all), PROT_READ | PROT_WRITE, MAP_SHARED, 0, 0);

    commune->count=0;

    for(int i = 0; i < PRODUCERS; i++)
        if(!(producersPID[i] = fork()))
            return producers(i);

    if(!(even = fork()))
        return consumer_even();

    if(!(odd = fork()))
        return consumer_odd();

    getchar();

    //kill(even, SIGTERM);
    //kill(odd, SIGTERM);
    //for(int i = 0; i < PRODUCERS; i++) kill(producersPID[i], SIGTERM);

    return 0;
}

int check() { return commune->tal.tab[head]; }

void del() {
    if(head==-1) {
        printf("Queue is EMPTY\n");
        return;
    }
    if(head==tail)
        head=-1;
    else
        head=(head+1)%9;
    commune->count--;
}

void insert(int item) {
    if(head == (tail+1)%9) {
        printf("Queue is FULL\n");
        return;
    }
    if(head==-1)
        tail=head=0;
    else
        tail=(tail+1)%9;

    commune->tal.tab[tail]=item;
    commune->count++;
}

int size() { return commune->count; }

int consumer_even() {
    srand(time(NULL));
    while(1) {
        if(size() < 3 || !check()%2)
            mutex.wait(&commune->consume_even);

        printf("Even consumer got: %d\n", check());
        del();
        if(size() >= 3) {
            if(!(check()%2))
                mutex.signal(&commune->consume_even)
            else
                mutex.signal(&commune->consume_odd);
        }
        else if(size() < LIMIT)
            mutex.signal(&commune->producer);
        sleep(rand()%2501)+500;
    }
    return 0;
}

int consumer_odd() {
    srand(time(NULL)+1);
    while(1) {
        if(size() < 3 || check()%2)
            mutex.wait(&commune->consume_odd);

        printf("Odd consumer got: %d\n", check());
        del();
        if(size() >= 3) {
            if(!(check()%2))
                mutex.signal(&commune->consume_even);
            else
                mutex.signal(&commune->consume_odd);
        }
        else if(size() < LIMIT)
            mutex.signal(&commune->producer);
        sleep(rand()%2501)+500;
    }
    return 0;
}

int producers(int index) {
    srand(time(NULL)+2+index);
    while(1) {
        if(size() >= LIMIT)
            mutex.wait(&commune->producer);

        int x = rand();
        insert(x);
        printf("%d. producer inserted: %d\n", index+1, check());

        if(size() >= 3) {
            if(!(check()%2))
                mutex.signal(&commune->consume_even);
            else
                mutex.signal(&commune->consume_odd);
        }
        else if(size() < LIMIT)
            mutex.signal(&commune->producer);
        sleep(rand()%2501)+500;
    }
    return 0;
}
