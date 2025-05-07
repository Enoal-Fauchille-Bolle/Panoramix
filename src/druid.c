/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Druid
*/

#include "druid.h"

#include <stdio.h>

#include "panoramix.h"
#include "pot.h"

/**
 * @brief Initialize the druid.
 *
 * This function initializes the druid with the maximum number of refills
 * it can make.
 *
 * @param druid The druid to initialize.
 * @param max_refills The maximum number of refills the druid can make.
 */
void druid_ready(void)
{
    printf("Druid: I'm ready... but sleepy...\n");
}

/**
 * @brief Check if the druid is out of refills.
 *
 * This function checks if the druid is out of refills by comparing the number
 * of refills left to zero.
 *
 * @param druid The druid to check.
 * @return true if the druid is out of refills, false otherwise.
 */
bool druid_is_empty(druid_t *druid)
{
    return druid->refills_left == 0;
}

/**
 * @brief Refill the pot with potions.
 *
 * This function refills the pot with potions. If the druid is out of refills,
 * it goes back to sleep.
 *
 * @param druid The druid to refill the pot.
 * @param pot The pot to refill.
 * @return true if the pot was refilled, false otherwise.
 */
bool druid_refill(druid_t *druid, pot_t *pot)
{
    printf(
        "Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can only "
        "make <refills> more refills after this one.\n");
    if (druid->refills_left > 0) {
        fill_pot(pot);
        druid->refills_left--;
        return true;
    }
    if (druid_is_empty(druid)) {
        printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
        return false;
    }
    return false;
}

static void druid_wakeup_message(panoramix_t *pano)
{
    pthread_mutex_lock(&pano->mutex_print);
    printf(
        "Druid: Ah! Yes, yes, I'm awake! Working on it! Beware I can "
        "only make %zu more refills after this one.\n",
        pano->druid.refills_left - 1);
    pthread_mutex_unlock(&pano->mutex_print);
}

static void druid_empty_message(panoramix_t *pano)
{
    pthread_mutex_lock(&pano->mutex_print);
    printf("Druid: I'm out of viscum. I'm going back to... zZz\n");
    pthread_mutex_unlock(&pano->mutex_print);
}

static void refill_pot_and_notify(panoramix_t *pano)
{
    druid_wakeup_message(pano);
    fill_pot(&pano->pot);
    pano->druid.refills_left--;
    for (size_t i = 0; i < pano->pot.size; i++) {
        sem_post(&pano->pot.sem_pot);
    }
    if (pano->druid.refills_left == 0) {
        druid_empty_message(pano);
    }
}

static void handle_empty_pot(panoramix_t *pano)
{
    pthread_mutex_lock(&pano->pot.mutex_pot);
    if (pot_is_empty(&pano->pot)) {
        refill_pot_and_notify(pano);
    }
    pthread_mutex_unlock(&pano->pot.mutex_pot);
}

void *druid_thread_func(void *arg)
{
    panoramix_t *pano = (panoramix_t *)arg;

    druid_ready();
    while (pano->druid.refills_left > 0) {
        sem_wait(&pano->druid.sem_druid);
        handle_empty_pot(pano);
    }
    return NULL;
}
