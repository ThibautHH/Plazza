/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <thread>

#include "../Wrappers/CountingSemaphore.hpp"
#include "Cook.hpp"

class Kitchen {
private:
    const uint16_t _maxCooks;
    const float _cookingTime;
    const uint32_t _reloadTime;

    CountingSemaphore _nbCooks{0};

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

    friend std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen);
};

#endif // KITCHEN_HPP
