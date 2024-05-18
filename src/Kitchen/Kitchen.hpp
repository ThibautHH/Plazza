/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <cstdint>
#include <thread>
#include <vector>

#include "Cook.hpp"

class Kitchen {
private:
    const uint16_t _maxCooks;
    const float _cookingTime;
    const uint32_t _reloadTime;

    uint16_t _nbCooks = 0;

    std::vector<Cook> _cooks;
    std::vector<std::thread> _threads;

    std::mutex _mutex;

public:
    Kitchen(uint16_t maxCooks, uint16_t cookingTime, uint32_t reloadTime);
    ~Kitchen();

    bool orderPizza(Pizza pizza);

    friend std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen)
    {
        for (uint16_t i = 0; i < static_cast<uint16_t>(kitchen._cooks.size()); i++) {
            os << kitchen._cooks[i];
            if (i + 1 < static_cast<uint16_t>(kitchen._cooks.size()))
                os << std::endl;
        }

        return os;
    }
};

#endif // KITCHEN_HPP
