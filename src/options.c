/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Options
*/

#include "options.h"

#include <stdio.h>
#include <stdlib.h>

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
