/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Main File
*/

#include <stdio.h>

#include "options.h"

int main(int ac, char **av)
{
    options_t options = get_options(ac, av);

    if (options.help || options.args_error || options.value_error) {
        printf(
            "USAGE: ./panoramix <nb_villagers> <pot_size> <nb_fights> "
            "<nb_refills>\n");
        if (options.value_error)
            printf("Values must be >0.\n");
        if (options.args_error || options.value_error)
            return 84;
        return 0;
    }
    return 0;
}
