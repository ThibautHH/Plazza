/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Program entrypoint
*/

#include "Kitchen/Kitchen.hpp"

int main(int, const char *const *)
{
    Kitchen kitchen(5, 5, 1000);
    constexpr auto pizza = Pizza{Margarita, S, 1};

    for (uint8_t i = 0; i < 10; i++) {
        kitchen.orderPizza(pizza);
    }
    sleep(5);
    std::cout << kitchen << std::endl;

    return 0;
}
