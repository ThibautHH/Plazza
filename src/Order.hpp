/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Order
*/

#ifndef PLAZZA_ORDER_HPP_
    #define PLAZZA_ORDER_HPP_

    #include <cstdint>
    #include <iostream>

    #include "Pizza.hpp"

namespace Plazza {
    struct Order : public Pizza {
        std::uint32_t quantity;
    };

    inline std::istream &operator>>(std::istream &is, Order &order) {
        auto type = static_cast<PizzaType>(0);
        auto size = static_cast<PizzaSize>(0);
        char x;
        std::int32_t quantity;

        is >> PizzaTypeTraits::pushalpha >> PizzaSizeTraits::pushalpha
            >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha
            >> type >> size >> x >> quantity
            >> PizzaTypeTraits::popalpha >> PizzaSizeTraits::popalpha;
        if (x != 'x' || quantity < 1) {
            is.setstate(std::ios_base::failbit);
            return is;
        }
        order.type = type;
        order.size = size;
        order.quantity = quantity;
        return is;
    }
}

#endif /* !PLAZZA_ORDER_HPP_ */
