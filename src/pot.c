/*
** EPITECH PROJECT, 2025
** Panoramix
** File description:
** Pot
*/

#include "pot.h"

/**
 * @brief Fill the pot with potions.
 *
 * This function fills the pot with the maximum number of potions it can hold.
 * It sets the number of potions left in the pot to its size.
 *
 * @param pot The pot to fill.
 */
void fill_pot(pot_t *pot)
{
    pot->potions_left = pot->size;
}

/**
 * @brief Check if the pot is empty.
 *
 * This function checks if the pot is empty by comparing the number of
 * potions left in the pot to zero.
 *
 * @param pot The pot to check.
 * @return true if the pot is empty, false otherwise.
 */
bool pot_is_empty(pot_t *pot)
{
    return pot->potions_left == 0;
}

/**
 * @brief Use a potion from the pot.
 *
 * This function decrements the number of potions left in the pot by one.
 * It assumes that the pot is not empty before calling this function.
 * If the pot is empty, it refills the pot using the druid.
 *
 * @param pot The pot to use a potion from.
 * @param druid The druid to refill the pot if it's empty.
 * @return true if a potion was used, false otherwise.
 */
bool pot_use(pot_t *pot, druid_t *druid)
{
    if (pot->potions_left > 0) {
        pot->potions_left--;
        return true;
    } else {
        druid_refill(druid, pot);
        if (pot->potions_left > 0) {
            pot->potions_left--;
            return true;
        }
        return false;
    }
    return false;
}
