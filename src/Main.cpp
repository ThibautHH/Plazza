/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Program entrypoint
*/

#include "Reception/Reception.hpp"

int main(const int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./plazza [cooks] [time] [stock_time]" << std::endl;
        return 84;
    }

    try {
        Reception reception(
            std::stoi(av[1]),
            std::stoi(av[2]),
            std::stoi(av[3])
            );
        reception.run();
    } catch (const std::exception &) {
        std::cerr << "Invalid arguments." << std::endl;
        return 84;
    }

    return 0;
}
