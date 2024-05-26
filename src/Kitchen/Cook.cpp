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
    const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(
            cook.getEndCookingTime() - std::chrono::system_clock::now()
        ).count();

    os << utils::enum_traits<Plazza::PizzaSize>::alpha << utils::enum_traits<Plazza::PizzaType>::alpha
        << "Cook " << cook.getId();
    if (cook.isBusy() && diff > 0)
        os << " is cooking a \"" << cook.getPizza().type << "\" in size "
           << cook.getPizza().size << ", ready in " << diff << "ms.";
    else
        os << " is waiting for an order.";
    os << utils::enum_traits<Plazza::PizzaSize>::alpha << utils::enum_traits<Plazza::PizzaType>::alpha;
    return os;
}
