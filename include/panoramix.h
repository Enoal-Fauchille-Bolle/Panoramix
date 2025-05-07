/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Panoramix Header
*/

#ifndef PANORAMIX_H_
    #define PANORAMIX_H_

    #include <pthread.h>
    #include <stddef.h>

    #include "druid.h"
    #include "pot.h"
    #include "villager.h"

typedef struct panoramix_s {
    villager_t *villagers;
    size_t villager_count;
    druid_t druid;
    pot_t pot;
    pthread_mutex_t mutex_print;
} panoramix_t;

typedef struct {
    panoramix_t *pano;
    unsigned int id;
} thread_data_t;

int start_simulation(panoramix_t *pano);

#endif /* !PANORAMIX_H_ */
