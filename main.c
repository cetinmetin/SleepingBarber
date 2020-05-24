#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t musteri, berber;
int musteriSayisi = 0;
const int beklemeSalonuKapasitesi = 5;

void *Musteri(void *arg) {
    int i;
    for (i = 0; i < 11; i++) {

        sleep(3);
        musteriSayisi++;
        printf("Yeni musteri geldi, musteri bekleme salonuna gitti\n");
        printf("Salondaki musteri sayisi : %d\n",musteriSayisi);

        while(musteriSayisi > beklemeSalonuKapasitesi ){
            printf("Bekleme salonu dolu, gelen musteri geri dondu..\n");
            musteriSayisi--;
        }

        sem_post(&musteri);
    }
 }

void *Berber(void *arg) {
    int i;
    for (i = 0; i < 12; i++) {

        while(musteriSayisi == 0){
            printf("Musteri yok, berber uyuyor.\n");
            sem_wait(&musteri);
            printf("Musteri geldi ve berberi uyandirdi, tiras basladi.\n");
        }
        sleep(6);
        musteriSayisi--;
        printf("Tiras bitti\n");
        printf("Salonda kalan musteri sayisi: %d\n", musteriSayisi);
        sem_wait(&musteri);
    }
}

int main(void) {

    pthread_t tid0,tid1;
    sem_init(&musteri, 0, 0);
    sem_init(&berber, 0, 0);

    pthread_create(&tid0, NULL, Berber, NULL);
    pthread_create(&tid1, NULL, Musteri, NULL);
    pthread_join(tid0, NULL);
    pthread_join(tid1, NULL);

    sem_destroy(&berber);
    sem_destroy(&musteri);

    return 0;
}
