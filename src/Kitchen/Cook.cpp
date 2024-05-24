/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Cook
*/

#include "Cook.hpp"

#include <iostream>

using namespace Plazza::Kitchen;

void Cook::cook(const Pizza pizza, const std::vector<std::shared_ptr<BalancingSemaphore>> &ingredients,
                std::mutex &mutex, std::ostream &os)
{
    mutex.lock();
    _isBusy = true;
    _pizza  = pizza;
    mutex.unlock();

    for (uint16_t i = 0; i < NB_INGREDIENTS; i++)
        for (uint16_t j = 0; j < pizzaRecipe.at(_pizza.type).first; j++)
            if (const auto ingredient = static_cast<Ingredient>(1 << i);
                pizzaRecipe.at(_pizza.type).second & ingredient)
                ingredients[i]->acquire();

    mutex.lock();
    const auto duration = std::chrono::milliseconds(
        static_cast<int>(_cookingTime * static_cast<float>(pizzaRecipe.at(_pizza.type).first) * 1000));
    _endCookingTime = std::chrono::system_clock::now() + duration;
    mutex.unlock();

    std::this_thread::sleep_for(duration);

    mutex.lock();
    os << _pizza << std::endl;
    _isBusy = false;
    mutex.unlock();
}

std::ostream &operator<<(std::ostream &os, const Cook &cook)
{

    if (const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(cook.getEndCookingTime() -
                                                                                std::chrono::system_clock::now())
                              .count();
        cook.isBusy() && diff > 0)
        os << "Cook " << cook.getId() << " is cooking a " << Plazza::pizzaName.at(cook.getPizza().type) << " "
           << Plazza::pizzaSize.at(cook.getPizza().size) << " end in " << diff << "ms";
    else
        os << "Cook " << cook.getId() << " is waiting for a pizza";

    return os;
}
