/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Druid Header
*/

#ifndef DRUID_H_
    #define DRUID_H_

    #include <pthread.h>
    #include <semaphore.h>
    #include <stdbool.h>
    #include <stddef.h>

    #include "pot.h"

typedef struct druid_s {
    size_t refills_left;
    pthread_mutex_t mutex_print;
    sem_t sem_druid;
} druid_t;

typedef struct pot_s pot_t;

void druid_ready(void);
bool druid_is_empty(druid_t *druid);
bool druid_refill(druid_t *druid, pot_t *pot);

void *druid_thread_func(void *arg);

#endif /* !DRUID_H_ */
