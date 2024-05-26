/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Common
*/

#ifndef TESTS_COMMON_HPP_
    #define TESTS_COMMON_HPP_

    #include "../src/Order.hpp"

namespace Plazza {
    constexpr bool operator==(Pizza const &lhs, Pizza const &rhs) noexcept
    {
        return lhs.type == rhs.type && lhs.size == rhs.size;
    }

    constexpr bool operator==(Order const &lhs, Order const &rhs) noexcept
    {
        return lhs.type == rhs.type && lhs.size == rhs.size && lhs.quantity == rhs.quantity;
    }
}

#endif /* !TESTS_COMMON_HPP_ */
