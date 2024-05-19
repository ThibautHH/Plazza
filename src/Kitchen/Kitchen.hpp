/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#ifndef KITCHEN_HPP
#define KITCHEN_HPP

#include <queue>
#include <thread>

#include "../Wrappers/CountingSemaphore.hpp"
#include "Cook.hpp"

class Kitchen {
private:
    const uint16_t _maxCooks;
    const float _cookingTime;
    const uint32_t _reloadTime;

    std::shared_ptr<std::atomic<bool>> _isRunning = std::make_shared<std::atomic<bool>>(true);
    std::mutex _mutex;

    CountingSemaphore _nbCooks{5};
    std::vector<std::pair<Cook, std::thread>> _cooks;

    std::queue<Pizza> _waitingPizzas;
    CountingSemaphore _asWaitingPizzas{0};
    std::thread _cooksManager;

    std::vector<std::shared_ptr<BalancingSemaphore>> _ingredients;
    std::vector<std::thread> _threadsIngredients;

public:
    Kitchen(uint16_t maxCooks, uint16_t cookingTime, uint32_t reloadTime);
    ~Kitchen();

    bool orderPizza(Pizza pizza);

    friend std::ostream &operator<<(std::ostream &os, const Kitchen &kitchen);
};

#endif // KITCHEN_HPP
