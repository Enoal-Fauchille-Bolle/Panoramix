/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Villager
*/

#include "villager.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "panoramix.h"
#include "pot.h"

void villager_ready(villager_t *villager)
{
    printf("Villager %u: Going into battle!\n", villager->id);
}

bool villager_drink(villager_t *villager, druid_t *druid, pot_t *pot)
{
    printf("Villager %u: I need a drink... I see %lu servings left.\n",
        villager->id, pot->potions_left);
    if (villager->drank) {
        printf("Villager %u: I already drank the potion!\n", villager->id);
        return false;
    }
    if (!pot_use(pot, druid)) {
        printf("Villager %u: The pot is empty!\n", villager->id);
        return false;
    }
    villager->drank = true;
    if (pot->potions_left == 0) {
        printf("Villager %u: Hey Pano wake up! We need more potion.\n",
            villager->id);
        sem_post(&druid->sem_druid);
    }
    return true;
}

void villager_fight(villager_t *villager)
{
    if (villager->fights_left > 0) {
        villager->fights_left--;
        villager->drank = false;
        printf("Villager %u: Take that roman scum! Only %u left.\n",
            villager->id, villager->fights_left);
    }
    if (villager->fights_left == 0) {
        printf("Villager %u: I'm going to sleep now.\n", villager->id);
    }
}

void *villager_thread_func(void *arg)
{
    thread_data_t *data = (thread_data_t *)arg;
    panoramix_t *pano = data->pano;
    unsigned int id = data->id;
    villager_t *villager = NULL;

    free(data);
    villager = &pano->villagers[id];
    villager_ready(villager);
    while (villager->fights_left > 0) {
        sem_wait(&pano->pot.sem_pot);
        pthread_mutex_lock(&pano->pot.mutex_pot);
        pthread_mutex_lock(&pano->mutex_print);
        if (villager_drink(villager, &pano->druid, &pano->pot)) {
            villager_fight(villager);
        }
        pthread_mutex_unlock(&pano->mutex_print);
        pthread_mutex_unlock(&pano->pot.mutex_pot);
        usleep(100000);
    }
    return NULL;
}
