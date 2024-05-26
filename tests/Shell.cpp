/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell tests
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>

#include <ranges>

#include "Common.hpp"

#include "../src/Shell.hpp"

using namespace Plazza;

Test(Shell, empty)
{
    bool exited = false;
    const auto result = Shell::parseOrders("", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, whitespace)
{
    bool exited = false;
    const auto result = Shell::parseOrders("\n   \f \t\t\v", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, emptyCommands)
{
    bool exited = false;
    const auto result = Shell::parseOrders("\n ;  \f; \t;\t\v;;;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exit)
{
    bool exited = false;
    const auto result = Shell::parseOrders("exit", exited);
    cr_expect(not(zero(exited)));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exitWithWhitespace)
{
    bool exited = false;
    const auto result = Shell::parseOrders("exit\n   \f \t\t\v", exited);
    cr_expect(not(zero(exited)));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exitWithEmptyCommands)
{
    bool exited = false;
    const auto result = Shell::parseOrders("\vexit\n ;  \f; \t;\t;;;", exited);
    cr_expect(not(zero(exited)));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exitInvalidArguments)
{
    bool exited = false;
    const auto result = Shell::parseOrders("exit fze", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exitInvalidArgumentsWithWhitespace)
{
    bool exited = false;
    const auto result = Shell::parseOrders(" \texit  \n fze\n   \f\t\v", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, exitInvalidArgumentsWithEmptyCommands)
{
    bool exited = false;
    const auto result = Shell::parseOrders(" ;\texit  \n fze\n   \f\t\v; ;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, invalidCommand)
{
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1 x1", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, invalidCommandWithWhitespace)
{
    bool exited = false;
    const auto result = Shell::parseOrders("\f \tMargarita S x1 x1\n   \t\v", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, invalidCommandWithEmptyCommands)
{
    bool exited = false;
    const auto result = Shell::parseOrders("\f \tMargarita S x1 x1\n   \t\v; ; ;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, invalidCommandWithExit)
{
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1 x1; exit", exited);
    cr_expect(not(zero(exited)));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::empty<Order>))));
}

Test(Shell, validAndInvalidCommands)
{
    const Order orders[] = {
        {Margarita, S, 1}, {Americana, S, 1}
    };
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1; Regina S x1 x1; Americana S x1;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::all(orders)))));
}

Test(Shell, validAndInvalidCommandsWithExit)
{
    const Order orders[] = {
        {Margarita, S, 1}, {Americana, S, 1}
    };
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1; Regina S x1 x1; Americana S x1; exit", exited);
    cr_expect(not(zero(exited)));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::all(orders)))));
}

Test(Shell, single)
{
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::single(Order{Margarita, S, 1})))));
}

Test(Shell, singleAndEmptyCommands)
{
    bool exited = false;
    const auto result = Shell::parseOrders("; Margarita S x1; ;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::single(Order{Margarita, S, 1})))));
}

Test(Shell, multiple)
{
    const Order orders[] = {
        {Margarita, S, 1}, {Regina, M, 2}, {Americana, L, 3}
    };
    bool exited = false;
    const auto result = Shell::parseOrders("Margarita S x1; Regina M x2; Americana L x3", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::all(orders)))));
}

Test(Shell, multipleAndEmptyCommands)
{
    const Order orders[] = {
        {Margarita, S, 1}, {Regina, M, 2}, {Americana, L, 3}
    };
    bool exited = false;
    const auto result = Shell::parseOrders("; Margarita S x1; ; Regina M x2; ; Americana L x3; ;", exited);
    cr_expect(zero(exited));
    cr_expect(not(zero(std::ranges::equal(std::views::all(result), std::views::all(orders)))));
}
