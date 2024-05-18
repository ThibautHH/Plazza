/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Kitchen
*/

#include "Kitchen.hpp"

Kitchen::Kitchen(const uint16_t maxCooks, const uint16_t cookingTime, const uint32_t reloadTime) :
    _maxCooks(maxCooks), _cookingTime(cookingTime), _reloadTime(reloadTime)
{
    for (uint16_t i = 0; i < _maxCooks; i++)
        _cooks.emplace_back(i, _cookingTime);
}

Kitchen::~Kitchen()
{
    for (auto &thread : _threads)
        thread.join();
}

bool Kitchen::orderPizza(Pizza pizza)
{
    if (_nbCooks < _maxCooks) {
        _threads.emplace_back([this, pizza](Cook &cook) { cook.cook(pizza, _mutex); }, std::ref(_cooks[_nbCooks++]));
        return true;
    }
    return false;
}
