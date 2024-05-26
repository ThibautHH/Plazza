/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** Reception
*/

#ifndef PLAZZA_RECEPTION_HPP_
    #define PLAZZA_RECEPTION_HPP_

    #include <chrono>
    #include <list>
    #include <optional>

    #include "Order.hpp"
    #include "KitchenProcess.hpp"

namespace Plazza {
    class Reception {
        public:
            Reception(double speed, std::uint16_t cookCount, std::optional<std::chrono::milliseconds> restock_delay = std::nullopt);

            void addOrder(Order order);

        private:
            const double _speed;
            const std::uint16_t _cookCount;
            const std::optional<std::chrono::milliseconds> _restock_delay;

            std::list<KitchenProcess> _kitchens;

            KitchenProcess &addKitchen();
    };
}

#endif /* !PLAZZA_RECEPTION_HPP_ */
