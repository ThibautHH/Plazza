/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#ifndef PLAZZA_SHELL_HPP_
    #define PLAZZA_SHELL_HPP_

    #include "../Pizza.hpp"

namespace Plazza {
    class Order {
        public:
            Order(PizzaType type, PizzaSize size, std::uint32_t quantity)
                : _type(type), _size(size), _quantity(quantity)
            {}

            [[nodiscard]] constexpr PizzaType getType() const noexcept { return _type; }
            [[nodiscard]] constexpr PizzaSize getSize() const noexcept { return _size; }
            [[nodiscard]] constexpr std::uint32_t getQuantity() const noexcept { return _quantity; }

        private:
            const PizzaType _type;
            const PizzaSize _size;
            const std::uint32_t _quantity;
    };

    class Shell {
        public:
            void run();
            static Order parseOrder(std::string_view input);

        private:
            static PizzaType parsePizzaType(std::string_view type);
            static PizzaSize parsePizzaSize(std::string_view size);
            static std::uint32_t parseAmount(std::string_view amountStr);
            bool _status = true;
    };
}

#endif /* !PLAZZA_SHELL_HPP_ */