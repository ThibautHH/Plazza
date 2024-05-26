/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** KitchenProcess
*/

#ifndef PLAZZA_KITCHENPROCESS_HPP_
    #define PLAZZA_KITCHENPROCESS_HPP_

    #include <atomic>
    #include <chrono>
    #include <condition_variable>
    #include <functional>
    #include <mutex>
    #include <optional>
    #include <sstream>
    #include <stop_token>
    #include <string>
    #include <thread>

    #include "subprocess/subprocess.hpp"

    #include "Pizza.hpp"

namespace Plazza {
    /**
     * Unused in the end
     */
    class Notification {
        public:
            typedef std::unordered_map<std::string_view, std::function<bool(std::istringstream &&, Notification &)>> handlers_t;
            static const handlers_t handlers;

            constexpr Notification() noexcept
                : _closing(false), _orderHandled(std::nullopt), _pizza(std::nullopt)
            {}
            constexpr Notification(std::nullopt_t) noexcept
                : _closing(true), _orderHandled(std::nullopt), _pizza(std::nullopt)
            {}
            constexpr Notification(bool orderHandled) noexcept
                : _closing(false), _orderHandled(orderHandled), _pizza(std::nullopt)
            {}
            constexpr Notification(Pizza pizza) noexcept
                : _closing(false), _orderHandled(std::nullopt), _pizza(pizza)
            {}

            [[nodiscard]] constexpr bool isClosing() const noexcept { return _closing; }
            [[nodiscard]] constexpr std::optional<bool> isOrderHandled() const noexcept { return _orderHandled; }
            [[nodiscard]] constexpr std::optional<Pizza> isPizza() const noexcept { return _pizza; }

        private:
            const bool _closing;
            const std::optional<bool> _orderHandled;
            const std::optional<Pizza> _pizza;
    };

    constexpr std::ostream &operator<<(std::ostream &os, Notification n) noexcept
    {
        if (n.isClosing())
            return os << "closing" << std::endl;
        if (n.isOrderHandled().has_value())
            return os << "order:" << *n.isOrderHandled() << std::endl;
        if (n.isPizza().has_value())
            return os << "pizza:"
                << PizzaTypeTraits::pushalpha << PizzaSizeTraits::pushalpha
                << PizzaTypeTraits::noalpha << PizzaSizeTraits::noalpha
                << *n.isPizza() << std::endl
                << PizzaTypeTraits::popalpha << PizzaSizeTraits::popalpha;
        return os;
    }

    inline std::istream &operator>>(std::istream &is, Notification &n) noexcept
    {
        std::string command;
        std::getline(is, command);
        std::istringstream iss(std::move(command));
        std::getline(iss >> std::ws, command, ':');
        try {
            if (!((std::istringstream(std::move(command)) >> command >> std::ws).eof()
                    && Notification::handlers.at(command)(std::move(iss), n)))
                is.setstate(std::ios_base::failbit);
        } catch (const std::out_of_range &) {
            is.setstate(std::ios_base::failbit);
        }
        return is;
    }

    class KitchenProcess : private subprocess::subprocess {
        public:
            KitchenProcess(double speed, std::uint16_t cookCount, std::optional<std::chrono::milliseconds> restockDelay);
            ~KitchenProcess();

            bool order(Pizza pizza);

            constexpr bool hasClosed() const noexcept { return _closed; }

            inline bool operator<(const KitchenProcess &other) const noexcept { return this->_pizzaCount < other._pizzaCount; }

        private:
            /**
            *  Kitchen subprocess entry point, exits 0 on return.
            */
            static void startKitchen(std::iostream &&ipc, int fd, double, std::uint16_t, std::optional<std::chrono::milliseconds>);
            /**
            *  Reception thread handling notifications from the kitchen. One thread per kitchen.
            */
            static void notificationThread(std::stop_token st, KitchenProcess &kitchen);

            static std::uint16_t nextId;

            void handleNotification(Notification n);

            const std::uint16_t _id = nextId++, _cookCount;
            bool /*_orderHandled, _cooking, */_closed;
            std::mutex _mutex;
            // std::condition_variable _cv;
            std::atomic_uint32_t _pizzaCount;
            std::jthread _notificationThread;
    };
}

#endif /* !PLAZZA_KITCHENPROCESS_HPP_ */
