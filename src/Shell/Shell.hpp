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

        [[nodiscard]] constexpr PizzaType getType() const noexcept;
        [[nodiscard]] constexpr PizzaSize getSize() const noexcept;
        [[nodiscard]] constexpr int getQuantity() const noexcept;
    private:
        const PizzaType _type;
        const PizzaSize _size;
        const int _quantity;
};

class Shell {
    public:
        Shell();
        ~Shell();
        void run();
        static Order parseOrder(const std::string &input);
    private:
        static PizzaType parsePizzaType(const std::string& type);
        static PizzaSize parsePizzaSize(const std::string& size);
        static int parseAmount(const std::string& amountStr);
        bool _status = true;
};