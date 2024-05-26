/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Shell
*/

#ifndef PLAZZA_SHELL_HPP_
    #define PLAZZA_SHELL_HPP_

    #include <list>

    #include "Reception.hpp"
    #include "Pizza.hpp"

    #include "Order.hpp"

namespace Plazza {
    struct Shell {
        static std::list<Order> parseOrders(std::string commandLine, bool &exited);

        Shell(Reception &reception);

        void run();

        private:
            Reception &_reception;
    };
}

#endif /* !PLAZZA_SHELL_HPP_ */
