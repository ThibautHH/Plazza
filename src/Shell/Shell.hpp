/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#pragma once

#include <functional>

#include "../Pizza.hpp"

class Order
{
public:
    Order(const PizzaType type, const PizzaSize size, const int quantity) : _type(type), _size(size),
                                                                            _quantity(quantity)
    {
    }

    ~Order() = default;

    [[nodiscard]] constexpr PizzaType getType() const noexcept { return _type; }
    [[nodiscard]] constexpr PizzaSize getSize() const noexcept { return _size; }
    [[nodiscard]] constexpr int getQuantity() const noexcept { return _quantity; }

private:
    const PizzaType _type;
    const PizzaSize _size;
    const int _quantity;
};

class Shell
{
private:
    static PizzaType parsePizzaType(const std::string& type);
    static PizzaSize parsePizzaSize(const std::string& size);
    static int parseAmount(const std::string& amountStr);
    static Order parseOrder(const std::string& input);
    bool _status = true;

public:
    void run(const std::function<void(Order)>& orderCallback);
    [[nodiscard]] bool isOpen() const noexcept { return _status; }
};
