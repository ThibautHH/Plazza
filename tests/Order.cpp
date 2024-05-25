/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Order tests
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <sstream>

#include "../src/Order.hpp"

using namespace Plazza;

constexpr bool operator==(Order const &lhs, Order const &rhs) noexcept
{
    return lhs.type == rhs.type && lhs.size == rhs.size && lhs.quantity == rhs.quantity;
}

Test(Order, extractBasic)
{
    Order o{};
    std::istringstream iss("Margarita S x1");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Order), o, (Order{Margarita, S, 1})));
}

Test(Order, extractOtherType)
{
    Order o{};
    std::istringstream iss("Regina S x1");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Order), o, (Order{Regina, S, 1})));
}

Test(Order, extractOtherSize)
{
    Order o{};
    std::istringstream iss("Margarita L x1");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Order), o, (Order{Margarita, L, 1})));
}

Test(Order, extractOtherQuantity)
{
    Order o{};
    std::istringstream iss("Margarita S x24");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Order), o, (Order{Margarita, S, 24})));
}

Test(Order, extractPadding)
{
    Order o{};
    std::istringstream iss(" \n\vMargarita \f\tS           x1\v");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    cr_expect(zero(iss.eof()));
    cr_expect(eq(type(Order), o, (Order{Margarita, S, 1})));
}

Test(Order, extractInvalidType)
{
    Order o{};
    std::istringstream iss("Lol S x1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractInvalidSize)
{
    Order o{};
    std::istringstream iss("Margarita XS x1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNullQuantity)
{
    Order o{};
    std::istringstream iss("Margarita S x0");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNegativeQuantity)
{
    Order o{};
    std::istringstream iss("Margarita S x-1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractInvalidQuantity)
{
    Order o{};
    std::string rest;
    std::istringstream iss("Margarita S x1.5");
    utils::extract(iss, o);
    cr_expect(zero(iss.fail()));
    iss >> rest;
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(std::string_view), rest, ".5"));
}

Test(Order, extractInvalidFormat)
{
    Order o{};
    std::istringstream iss("Margarita S 1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNoQuantity)
{
    Order o{};
    std::istringstream iss("Margarita S x");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNoSize)
{
    Order o{};
    std::istringstream iss("Margarita x1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNoType)
{
    Order o{};
    std::istringstream iss("S x1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNoTypeAndSize)
{
    Order o{};
    std::istringstream iss("x1");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}

Test(Order, extractNull)
{
    Order o{};
    std::istringstream iss("");
    utils::extract(iss, o);
    cr_expect(not(zero(iss.fail())));
}
