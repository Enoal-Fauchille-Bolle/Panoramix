/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Options
*/

#include "options.h"

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Setup the options structure.
 *
 * This function sets up the options structure with the provided command line
 * arguments.
 *
 * @param options The options structure to set up.
 * @param av The command line arguments.
 * @return true if the setup was successful, false otherwise.
 */
static bool setup_options(options_t *options, char **av)
{
    int villagers = atoi(av[1]);
    int pot_size = atoi(av[2]);
    int max_fights = atoi(av[3]);
    int max_refills = atoi(av[4]);

    if (villagers <= 0 || pot_size <= 0 || max_fights <= 0 ||
        max_refills <= 0) {
        options->value_error = true;
        return false;
    }
    options->villagers = (unsigned int)villagers;
    options->pot_size = (size_t)pot_size;
    options->max_fights = (unsigned int)max_fights;
    options->max_refills = (unsigned int)max_refills;
    return true;
}

/**
 * @brief Get the options from command line arguments.
 *
 * This function parses the command line arguments and sets up the options
 * structure.
 *
 * @param ac The number of command line arguments.
 * @param av The command line arguments.
 * @return The options structure.
 */
options_t get_options(int ac, char **av)
{
    options_t options = {0, 0, 0, 0, false, false, false};

    if (ac == 2 && av[1][0] == '-' && av[1][1] == 'h') {
        options.help = true;
        return options;
    }
    if (ac != 5) {
        options.args_error = true;
        options.help = true;
        return options;
    }
    setup_options(&options, av);
    return options;
}

/**
 * @brief Handle the options and print usage information if needed.
 *
 * This function checks the options structure and prints usage information if
 * there are errors or if help is requested.
 *
 * @param options The options structure to handle.
 * @return 0 on success, 84 on error.
 */
int handle_options(options_t *options)
{
    if (options->help || options->args_error || options->value_error) {
        printf(
            "USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights>"
            "<nb_refills>\n");
        if (options->value_error)
            printf("Values must be >0.\n");
        if (options->args_error || options->value_error)
            return 84;
        return 0;
    }
    return -1;
}
