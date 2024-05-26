/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"

using namespace Plazza;

Reception::Reception(double speed, std::uint16_t cookCount, std::optional<std::chrono::milliseconds> restock_delay)
    : _speed(speed), _cookCount(cookCount), _restock_delay(restock_delay)
{
}

void Reception::addOrder(Order order)
{
    for (std::uint32_t i = 0; i < order.quantity; i++) {
        // Remove all closed kitchens
        this->_kitchens.remove_if([](const KitchenProcess &k){ return k.hasClosed(); });
        if (_kitchens.empty() // If no kitchen is open
            || !std::min_element(_kitchens.begin(), _kitchens.end())
                ->order(static_cast<Pizza &>(order))) // Or the kitchen with the least orders can't handle the order
            // Add a new kitchen and order the pizza
            this->addKitchen().order(static_cast<Pizza &>(order));
    }
}

KitchenProcess &Reception::addKitchen()
{
    _kitchens.emplace_back(_speed, _cookCount, _restock_delay);
    return _kitchens.back();
}
