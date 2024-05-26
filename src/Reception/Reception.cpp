/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include "../Kitchen/Kitchen.hpp"

Reception::Reception(const uint16_t maxCooks, const uint16_t cookingTime, const uint32_t reloadTime) :
    _maxCooks(maxCooks), _cookingTime(cookingTime), _reloadTime(reloadTime)
{
    if (maxCooks == 0)
        throw std::invalid_argument("Max cooks must be greater than 0");

    _shellThread = std::thread([this]
    {
        _shell.run([this](const Order order)
        {
            const Pizza pizza{order.getType(), order.getSize()};

            for (uint16_t i = 0; i < static_cast<uint16_t>(order.getQuantity()); i++) {
                bool isOrderSent = false;
                for (auto &kitchen : _kitchens)
                    if (kitchen.orderPizza(pizza)) {
                        isOrderSent = true;
                        break;
                    }
                if (!isOrderSent) {
                    _kitchens.emplace_back(_maxCooks, _cookingTime, _reloadTime);
                    _kitchens.back().orderPizza(pizza);
                }
            }
        });
    });
}

void Reception::run()
{
    while (_shell.isOpen());
}


Reception::~Reception()
{
    _shellThread.join();
}
