/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Pizza tests
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include "Common.hpp"

using namespace Plazza;

Test(Pizza, extractBasic)
{
    Pizza p{};
    std::istringstream iss("1:1");
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Regina, S})));
}

Test(Pizza, extractOtherType)
{
    Pizza p{};
    std::istringstream iss("2:1");
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Margarita, S})));
}

Test(Pizza, extractOtherSize)
{
    Pizza p{};
    std::istringstream iss("1:8");
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Regina, XL})));
}

Test(Pizza, extractOtherTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("2:4");
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Margarita, L})));
}

Test(Pizza, extractPadding)
{
    Pizza p{};
    std::istringstream iss(" \n\v1:1\v");
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(zero(iss.eof()));
    cr_expect(eq(type(Pizza), p, (Pizza{Regina, S})));
}

Test(Pizza, extractInvalidType)
{
    Pizza p{};
    std::istringstream iss("3:1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractInvalidSize)
{
    Pizza p{};
    std::istringstream iss("1:5");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractInvalidTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("3:5");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractZeroType)
{
    Pizza p{};
    std::istringstream iss("0:1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractZeroSize)
{
    Pizza p{};
    std::istringstream iss("1:0");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractZeroTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("0:0");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractZero)
{
    Pizza p{};
    std::istringstream iss("0");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNegativeType)
{
    Pizza p{};
    std::istringstream iss("-1:1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNegativeSize)
{
    Pizza p{};
    std::istringstream iss("1:-1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNegativeTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("-1:-1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNegative)
{
    Pizza p{};
    std::istringstream iss("-1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNullType)
{
    Pizza p{};
    std::istringstream iss(":1");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNullSize)
{
    Pizza p{};
    std::istringstream iss("1:");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNullTypeAndSize)
{
    Pizza p{};
    std::istringstream iss(":");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractNull)
{
    Pizza p{};
    std::istringstream iss("");
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractAlpha)
{
    Pizza p{};
    std::istringstream iss("Margarita:S");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Margarita, S})));
}

Test(Pizza, extractAlphaOtherType)
{
    Pizza p{};
    std::istringstream iss("Regina:S");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Regina, S})));
}

Test(Pizza, extractAlphaOtherSize)
{
    Pizza p{};
    std::istringstream iss("Margarita:XL");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Margarita, XL})));
}

Test(Pizza, extractAlphaOtherTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("Regina:L");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(not(zero(iss.eof())));
    cr_expect(eq(type(Pizza), p, (Pizza{Regina, L})));
}

Test(Pizza, extractAlphaPadding)
{
    Pizza p{};
    std::istringstream iss(" \n\vMargarita:S\v");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(zero(iss.fail()));
    cr_expect(zero(iss.eof()));
    cr_expect(eq(type(Pizza), p, (Pizza{Margarita, S})));
}

Test(Pizza, extractAlphaInvalidType)
{
    Pizza p{};
    std::istringstream iss("Lol:S");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractAlphaInvalidSize)
{
    Pizza p{};
    std::istringstream iss("Margarita:XXS");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}

Test(Pizza, extractAlphaInvalidTypeAndSize)
{
    Pizza p{};
    std::istringstream iss("Lol:XXS");
    iss >> PizzaTypeTraits::alpha >> PizzaSizeTraits::alpha;
    utils::extract(iss, p);
    cr_expect(not(zero(iss.fail())));
}
