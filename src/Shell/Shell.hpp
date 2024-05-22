/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#pragma once

#include "../Pizza.hpp"

class Order {
    public:
        Order(PizzaType type, PizzaSize size, int quantity) : _type(type), _size(size), _quantity(quantity) {}
        ~Order() = default;

        [[nodiscard]] PizzaType getType() const { return _type; }
        [[nodiscard]] PizzaSize getSize() const { return _size; }
        [[nodiscard]] int getQuantity() const { return _quantity; }
    private:
        PizzaType _type;
        PizzaSize _size;
        int _quantity;
};

class Shell {
    public:
        Shell();
        ~Shell();
        void run();
        static Order parseOrder(const std::string &input);
    private:
        bool _status = true;
};