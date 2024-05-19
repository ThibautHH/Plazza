/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Cook
*/

#include "Cook.hpp"

void Cook::cook(const Pizza pizza, const std::vector<std::shared_ptr<BalancingSemaphore>> &ingredients,
                std::mutex &mutex)
{
    mutex.lock();
    _pizza     = pizza;
    _isCooking = true;

    const auto duration = std::chrono::milliseconds(_cookingTime * pizzaRecipe.at(_pizza.type).first * 1000);
    _endCookingTime     = std::chrono::system_clock::now() + duration;
    mutex.unlock();

    for (uint16_t i = 0; i < 9; i++)
        for (uint16_t j = 0; j < pizzaRecipe.at(_pizza.type).first; j++)
            if (const auto ingredient = static_cast<Ingredient>(1 << i);
                pizzaRecipe.at(_pizza.type).second & ingredient)
                ingredients[i]->acquire();
    for (uint16_t i = 0; i < _pizza.number; i++)
        std::this_thread::sleep_for(duration);

    mutex.lock();
    _isCooking = false;

    std::cout << "Cook " << _id << " finished cooking a " << pizzaName.at(_pizza.type) << " "
              << pizzaSize.at(_pizza.size) << " x" << _pizza.number << std::endl;
    mutex.unlock();
}

std::ostream &operator<<(std::ostream &os, const Cook &cook)
{

    if (const auto diff = std::chrono::duration_cast<std::chrono::milliseconds>(cook.getEndCookingTime() -
                                                                                std::chrono::system_clock::now())
                              .count();
        cook.isCooking() && diff > 0)
        os << "Cook " << cook.getId() + 1 << " is cooking a " << pizzaName.at(cook.getPizza().type) << " "
           << pizzaSize.at(cook.getPizza().size) << " x" << cook.getPizza().number << " end in " << diff << "ms";

    else
        os << "Cook " << cook.getId() << " is waiting for a pizza";
    return os;
}