/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Pot Header
*/

#ifndef POT_H_
    #define POT_H_

    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>
    #include <stddef.h>

    #include "druid.h"

typedef struct pot_s {
    size_t size;
    size_t potions_left;
    pthread_mutex_t mutex_pot;
    sem_t sem_pot;
} pot_t;

typedef struct druid_s druid_t;

void fill_pot(pot_t *pot);
bool pot_is_empty(pot_t *pot);
bool pot_use(pot_t *pot, druid_t *druid);

#endif /* !POT_H_ */
