/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Notification
*/

#include <criterion/criterion.h>
#include <criterion/new/assert.h>
#include <optional>

#include "Common.hpp"

#include "../src/KitchenProcess.hpp"

using namespace Plazza;

Test(Notification, writeClosing)
{
    std::ostringstream oss;
    oss << Notification(std::nullopt);
    cr_expect(eq(type(std::string_view), oss.str(), "closing\n"));
}

Test(Notification, writeOrderHandled)
{
    std::ostringstream oss;
    oss << Notification(true);
    cr_expect(eq(type(std::string_view), oss.str(), "order:1\n"));
    oss.str("");
    oss << Notification(false);
    cr_expect(eq(type(std::string_view), oss.str(), "order:0\n"));
}

Test(Notification, writePizzaCooked)
{
    std::ostringstream oss;
    oss << Notification(Pizza{Regina, S});
    cr_expect(eq(type(std::string_view), oss.str(), "pizza:1:1\n"));
    oss.str("");
    oss << Notification(Pizza{Margarita, L});
    cr_expect(eq(type(std::string_view), oss.str(), "pizza:2:4\n"));
}

Test(Notification, readEmpty)
{
    std::istringstream iss("\n");
    Notification n;
    iss >> n;
    cr_expect(iss.fail());
    iss.str(" \t \v  \f \n");
    iss >> n;
    cr_expect(iss.fail());
}

Test(Notification, readInvalid)
{
    std::istringstream iss(" \tinvalid \v \f\n");
    Notification n;
    iss >> n;
    cr_expect(iss.fail());
    iss.str(" \v \finvalid:1 \t\n");
    iss >> n;
    cr_expect(iss.fail());
    iss.str(" \tinvalid:1:1 \v \f\n");
    iss >> n;
    cr_expect(iss.fail());
}

Test(Notification, readClosing)
{
    std::istringstream iss(" \f closing \t\n");
    Notification n;
    iss >> n;
    cr_expect(not(iss.fail()));
    cr_expect(n.isClosing());
    cr_expect(not(n.isOrderHandled().has_value()));
    cr_expect(not(n.isPizza().has_value()));
    iss.str("\fclosing:\v \n");
    iss >> n;
    cr_expect(iss.fail());
    iss.str(" closing:1  \t\n");
    iss >> n;
    cr_expect(iss.fail());
}

Test(Notification, readOrderHandled)
{
    std::istringstream iss("  \f order:1\t\n");
    Notification n;
    iss >> n;
    cr_expect(not(iss.fail()));
    cr_expect(not(n.isClosing()));
    cr_expect(n.isOrderHandled().value());
    cr_expect(not(n.isPizza().has_value()));
    iss.str(" \torder:0\v \n");
    iss >> n;
    cr_expect(not(iss.fail()));
    cr_expect(not(n.isClosing()));
    cr_expect(not(n.isOrderHandled().value()));
    cr_expect(not(n.isPizza().has_value()));
    iss.str("order:1:\f \n");
    iss >> n;
    cr_expect(iss.fail());
    iss.str("order:1:1\n");
    iss >> n;
    cr_expect(iss.fail());
}

Test(Notification, readPizzaCooked)
{
    std::istringstream iss(" \f pizza:1:1 \v\n");
    Notification n;
    iss >> n;
    cr_expect(not(iss.fail()));
    cr_expect(not(n.isClosing()));
    cr_expect(not(n.isOrderHandled().has_value()));
    cr_expect(eq(type(Pizza), n.isPizza().value(), (Pizza{Regina, S})));
    iss.str("  pizza:2:4\t \n");
    iss >> n;
    cr_expect(not(iss.fail()));
    cr_expect(not(n.isClosing()));
    cr_expect(not(n.isOrderHandled().has_value()));
    cr_expect(eq(type(Pizza), n.isPizza().value(), (Pizza{Margarita, L})));
    iss.str("pizza:1:1:\f \n");
    iss >> n;
    cr_expect(iss.fail());
    iss.str("pizza:1:1:1\n");
    iss >> n;
    cr_expect(iss.fail());
}
