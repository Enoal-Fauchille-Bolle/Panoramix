/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Main File
*/

#include <stdio.h>
#include <stdlib.h>

#include "options.h"
#include "panoramix.h"

static void setup_panoramix_villager(
    villager_t *villager, unsigned int id, unsigned int fights_left)
{
    villager->id = id;
    villager->drank = false;
    villager->fights_left = fights_left;
    villager->mutex_print = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;
}

/**
 * @brief Setup the Panoramix structure.
 *
 * This function allocates memory for the Panoramix structure and initializes
 * its members based on the provided options.
 *
 * @param options The options to use for initialization.
 * @return A pointer to the initialized Panoramix structure, or NULL on
 * failure.
 */
panoramix_t *setup_panoramix(options_t *options)
{
    panoramix_t *panoramix = malloc(sizeof(panoramix_t));

    if (!panoramix)
        return NULL;
    panoramix->villagers = malloc(sizeof(villager_t) * options->villagers);
    if (!panoramix->villagers) {
        free(panoramix);
        return NULL;
    }
    for (size_t i = 0; i < options->villagers; i++) {
        setup_panoramix_villager(
            &panoramix->villagers[i], (unsigned int)i, options->max_fights);
    }
    panoramix->villager_count = options->villagers;
    panoramix->druid.refills_left = options->max_refills;
    panoramix->pot.size = options->pot_size;
    panoramix->pot.potions_left = options->pot_size;
    return panoramix;
}

/**
 * @brief Destroy the Panoramix structure.
 *
 * This function frees the memory allocated for the Panoramix structure and its
 * villagers.
 *
 * @param panoramix The Panoramix structure to destroy.
 */
void destroy_panoramix(panoramix_t *panoramix)
{
    if (panoramix) {
        free(panoramix->villagers);
        free(panoramix);
    }
}

/**
 * @brief Debug function to print the state of the Panoramix structure.
 *
 * This function prints the state of the Panoramix structure and its villagers
 * for debugging purposes.
 *
 * @param panoramix The Panoramix structure to debug.
 * @param options The options used for initialization.
 */
void debug(panoramix_t *panoramix, options_t *options)
{
    printf("nb_villagers: %u\n", options->villagers);
    printf("pot_size: %zu\n", options->pot_size);
    printf("max_fights: %u\n", options->max_fights);
    printf("max_refills: %u\n", options->max_refills);
    printf("villager_count: %zu\n", panoramix->villager_count);
    for (size_t i = 0; i < panoramix->villager_count; i++) {
        printf("villager[%zu]:\n", i);
        printf("id: %u\n", panoramix->villagers[i].id);
        printf(
            "drank: %s\n", panoramix->villagers[i].drank ? "true" : "false");
        printf("fights_left: %u\n", panoramix->villagers[i].fights_left);
    }
    printf("druid_refills_left: %zu\n", panoramix->druid.refills_left);
    printf("pot_potions_left: %zu\n", panoramix->pot.potions_left);
    printf("pot_size: %zu\n", panoramix->pot.size);
}

/**
 * @brief Main function of the program.
 *
 * This function parses command line arguments, sets up the Panoramix
 * structure, and runs the program.
 *
 * @param ac The number of command line arguments.
 * @param av The command line arguments.
 * @return 0 on success, 84 on error.
 */
int main(int ac, char **av)
{
    options_t options = get_options(ac, av);
    int option_handler_result = handle_options(&options);
    panoramix_t *panoramix = NULL;

    if (option_handler_result != -1)
        return option_handler_result;
    panoramix = setup_panoramix(&options);
    if (start_simulation(panoramix) == 84) {
        destroy_panoramix(panoramix);
        return 84;
    }
    destroy_panoramix(panoramix);
    return 0;
}
