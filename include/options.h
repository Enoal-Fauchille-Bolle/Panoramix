/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Options Header
*/

#ifndef OPTIONS_H_
    #define OPTIONS_H_

    #include <stddef.h>
    #include <stdbool.h>

typedef struct options_s {
    unsigned int villagers;
    size_t pot_size;
    unsigned int max_fights;
    unsigned int max_refills;
    bool help;
    bool args_error;
    bool value_error;
} options_t;

options_t get_options(int ac, char **av);

#endif /* !OPTIONS_H_ */
