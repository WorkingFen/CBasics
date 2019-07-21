#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <time.h>
#include <signal.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>

#define LIMIT 9
#define PRODUCERS 2

//gcc semaphores.c -o program -lpthread -std=c99

typedef struct {
    int tab[9];
}que;

typedef struct {
    que tal;
    int waiting_prod;
    int waiting_even;
    int waiting_odd;
    int count;
    sem_t consume_even;
    sem_t consume_odd;
    sem_t mutex;
    sem_t producer;
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

    sem_init(&commune->consume_even, 1, 0);
    sem_init(&commune->consume_odd, 1, 0);
    sem_init(&commune->producer, 1, 1);
    sem_init(&commune->mutex, 1, 1);

    commune->count=0;
    commune->waiting_even=0;
    commune->waiting_odd=0;
    commune->waiting_prod=0;

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
	sem_wait(&commune->mutex);

        if(size() < 3 || !check()%2){
            commune->waiting_even++;
            sem_post(&commune->mutex);
            sem_wait(&commune->consume_even);
            commune->waiting_even--;
        }
        printf("Even consumer got: %d\n", check());\
        del();
        if(size() >= 3) {
            if(!(check()%2) && commune->waiting_even) {
                sem_post(&commune->consume_even);
            }
            else if(commune->waiting_odd){
                sem_post(&commune->consume_odd);
            }
        }
        else if(size() < LIMIT && commune->waiting_prod)
            sem_post(&commune->producer);
        else
            sem_post(&commune->mutex);
        sleep(rand()%2501)+500;
    }
    return 0;
}

int consumer_odd() {
    srand(time(NULL)+1);
    while(1) {
	sem_wait(&commune->mutex);

        if(size() < 3 || check()%2){
            commune->waiting_odd++;
            sem_post(&commune->mutex);
            sem_wait(&commune->consume_odd);
            commune->waiting_odd--;
        }
        printf("Odd consumer got: %d\n", check());
        del();
        if(size() >= 3) {
            if(!(check()%2) && commune->waiting_even) {
                sem_post(&commune->consume_even);
            }
            else if(commune->waiting_odd){
                sem_post(&commune->consume_odd);
            }
        }
        else if(size() < LIMIT && commune->waiting_prod)
            sem_post(&commune->producer);
        else
            sem_post(&commune->mutex);
        sleep(rand()%2501)+500;
    }
    return 0;
}

int producers(int index) {
    srand(time(NULL)+2+index);
    while(1) {
        sem_wait(&commune->mutex);

        if(size() >= LIMIT){
            commune->waiting_prod++;
            sem_post(&commune->mutex);
            sem_wait(&commune->producer);
            commune->waiting_prod--;
        }

        int x = rand();
        insert(x);
        printf("%d. producer inserted: %d\n", index+1, check());

        if(size() >= 3) {
            if(!(check()%2) && commune->waiting_even) {
                sem_post(&commune->consume_even);
            }
            else if(commune->waiting_odd){
                sem_post(&commune->consume_odd);
            }
        }
        else if(size() < LIMIT && commune->waiting_prod)
            sem_post(&commune->producer);
        else
            sem_post(&commune->mutex);
        sleep(rand()%2501)+500;
    }
    return 0;
}
