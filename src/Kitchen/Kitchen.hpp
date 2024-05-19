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

#include "../Wrappers/BalancingSemaphore.hpp"
#include "Cook.hpp"

class Kitchen {
private:
    const uint16_t _maxCooks;
    const float _cookingTime;
    const uint32_t _reloadTime;

    uint16_t _nbCooks = 0;

    std::vector<Cook> _cooks;
    std::vector<std::thread> _threadsCooks;

    std::shared_ptr<std::atomic<bool>> _isRunning = std::make_shared<std::atomic<bool>>(true);

    std::vector<std::shared_ptr<BalancingSemaphore>> _ingredients;
    std::vector<std::thread> _threadsIngredients;

    std::mutex _mutex;

public:
    Kitchen(uint16_t maxCooks, uint16_t cookingTime, uint32_t reloadTime);
    ~Kitchen();

    bool orderPizza(Pizza pizza);

    friend std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen)
    {
        for (uint16_t i = 0; i < static_cast<uint16_t>(kitchen._cooks.size()); i++)
            os << kitchen._cooks[i] << "\n";
        os << "Ingredient\n";
        for (uint16_t i = 0; i < 9; i++) {
            os << '\t' << ingredientName.at(static_cast<Ingredient>(1 << i)) << ": "
               << kitchen._ingredients[i]->getValue();
            if (i != 8)
                os << "\n";
        }

        return os;
    }
};

#endif // KITCHEN_HPP
