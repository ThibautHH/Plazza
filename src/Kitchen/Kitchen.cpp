/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

#include <csignal>

Kitchen::Kitchen(const uint16_t maxCooks, const uint16_t cookingTime, const uint32_t reloadTime) :
    _maxCooks(maxCooks), _cookingTime(cookingTime), _reloadTime(reloadTime)
{
    for (uint16_t i = 0; i < _maxCooks; i++)
        _cooks.emplace_back(i + 1, _cookingTime);

    for (uint16_t i = 0; i < 9; i++)
        _ingredients.emplace_back(std::make_shared<BalancingSemaphore>(5));

    for (uint16_t i = 0; i < 9; i++)
        _threadsIngredients.emplace_back(
            [this, i]()
            {
                while (*_isRunning)
                    _ingredients[i]->release([] { std::this_thread::sleep_for(std::chrono::milliseconds(1000)); });
            });
}

Kitchen::~Kitchen()
{
    for (auto &thread : _threadsCooks)
        thread.join();
    *_isRunning = false;
    for (const auto &ingredient : _ingredients)
        ingredient->acquire();
    for (auto &thread : _threadsIngredients)
        thread.join();
}

bool Kitchen::orderPizza(Pizza pizza)
{
    if (_nbCooks < _maxCooks) {
        _threadsCooks.emplace_back([this, pizza](Cook &cook) { cook.cook(pizza, _ingredients, _mutex); },
                                   std::ref(_cooks[_nbCooks++]));
        return true;
    }
    return false;
}
