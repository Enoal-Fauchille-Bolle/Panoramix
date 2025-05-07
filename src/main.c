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
