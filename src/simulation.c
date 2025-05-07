/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Simulation
*/

#include <stdio.h>
#include <stdlib.h>

#include "panoramix.h"

static void initialize_semaphores(panoramix_t *pano)
{
    sem_init(&pano->pot.sem_pot, 0, pano->pot.size);
    sem_init(&pano->druid.sem_druid, 0, 0);
}

static void cleanup_semaphores(panoramix_t *pano)
{
    sem_destroy(&pano->pot.sem_pot);
    sem_destroy(&pano->druid.sem_druid);
}

static int create_druid_thread(panoramix_t *pano, pthread_t *druid_thread)
{
    if (pthread_create(druid_thread, NULL, druid_thread_func, (void *)pano) !=
        0) {
        perror("pthread_create (druid)");
        return 84;
    }
    return 0;
}

static thread_data_t *create_thread_data(panoramix_t *pano, size_t id)
{
    thread_data_t *data = malloc(sizeof(thread_data_t));

    if (!data) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    data->pano = pano;
    data->id = id;
    return data;
}

static void create_villager_threads(
    panoramix_t *pano, pthread_t *villager_threads)
{
    thread_data_t *data = NULL;

    for (size_t i = 0; i < pano->villager_count; i++) {
        data = create_thread_data(pano, i);
        if (pthread_create(
                &villager_threads[i], NULL, villager_thread_func, data) != 0) {
            perror("pthread_create (villager)");
            exit(EXIT_FAILURE);
        }
    }
}

static void join_villager_threads(
    panoramix_t *pano, pthread_t *villager_threads)
{
    for (size_t i = 0; i < pano->villager_count; i++) {
        pthread_join(villager_threads[i], NULL);
    }
}

int start_simulation(panoramix_t *pano)
{
    pthread_t druid_thread;
    pthread_t *villager_threads =
        malloc(sizeof(pthread_t) * pano->villager_count);

    if (!villager_threads) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    initialize_semaphores(pano);
    if (create_druid_thread(pano, &druid_thread) != 0) {
        free(villager_threads);
        return 84;
    }
    create_villager_threads(pano, villager_threads);
    join_villager_threads(pano, villager_threads);
    free(villager_threads);
    sem_post(&pano->druid.sem_druid);
    pthread_join(druid_thread, NULL);
    cleanup_semaphores(pano);
    return 0;
}
