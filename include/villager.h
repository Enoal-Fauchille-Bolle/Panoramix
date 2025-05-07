/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Villager Header
*/

#ifndef VILLAGER_H_
    #define VILLAGER_H_

    #include <pthread.h>
    #include <stdbool.h>

    #include "druid.h"
    #include "pot.h"

typedef struct villager_s {
    unsigned int id;
    bool drank;
    unsigned int fights_left;
    pthread_mutex_t mutex_print;
} villager_t;

void villager_ready(villager_t *villager);
bool villager_drink(villager_t *villager, druid_t *druid, pot_t *pot);
void villager_fight(villager_t *villager);

void *villager_thread_func(void *arg);

#endif /* !VILLAGER_H_ */
