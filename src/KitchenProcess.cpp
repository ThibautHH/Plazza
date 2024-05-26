/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** KitchenProcess
*/

#include <chrono>
#include <istream>
#include <mutex>
#include <optional>
#include <poll.h>
#include <syncstream>

#include "KitchenProcess.hpp"

using namespace std::chrono_literals;

using namespace Plazza;

/**
*  Unused in the end
*/
const Notification::handlers_t Notification::handlers = {
    {"closing", [](std::istringstream &&iss, Notification &n) noexcept {
        if (!iss.eof())
            return false;
        std::construct_at(std::addressof(n), std::nullopt);
        return true;
    }},
    {"order", [](std::istringstream &&iss, Notification &n) noexcept {
        bool orderHandled = false;
        utils::extract(iss, orderHandled);
        if (iss.fail() || !(iss >> std::ws).eof())
            return false;
        std::construct_at(std::addressof(n), orderHandled);
        return true;
    }},
    {"pizza", [](std::istringstream &&iss, Notification &n) noexcept {
        Pizza pizza{};
        utils::extract(iss, pizza);
        if (iss.fail() || !(iss >> std::ws).eof())
            return false;
        std::construct_at(std::addressof(n), pizza);
        return true;
    }}
};

std::uint16_t KitchenProcess::nextId = 0;

KitchenProcess::KitchenProcess(double speed, std::uint16_t cookCount, std::optional<std::chrono::milliseconds> restockDelay)
    : _cookCount(cookCount), /*_orderHandled(false), _cooking(false), */_closed(false),
    _pizzaCount(0)
{
    std::osyncstream(std::cout) << "Kitchen #" << _id << " opened" << std::endl;
    // Start subprocess
    this->start(startKitchen, speed, cookCount, restockDelay);
    // Start notification thread
    this->_notificationThread = std::jthread(notificationThread, std::ref(*this));
}

KitchenProcess::~KitchenProcess()
{
    // If the kitchen is closed, the notification thread is already stopped
    if (this->hasClosed())
        return;
    this->_notificationThread.request_stop();
    // Close the ipc on this side
    this->ipc([](subprocess::buffer &buf){ buf = subprocess::buffer(); });
    // That triggers a POLLHUP on the kitchen side, which closes the kitchen
}

void KitchenProcess::startKitchen(std::iostream &&ipc, int fd, double mult, std::uint16_t, std::optional<std::chrono::milliseconds>)
{
    std::atomic<std::chrono::steady_clock::time_point> timeout =
        std::chrono::steady_clock::now() + std::chrono::seconds(static_cast<long>(5.0 / mult));
    std::jthread kitchenThread([&ipc, fd, mult, &timeout](std::stop_token st){
        while (!st.stop_requested()) {
            struct pollfd pfd = {fd, POLLIN, 0};
            if (int ret = poll(&pfd, 1, 0); ret < 0)
                throw std::runtime_error(std::string("poll: ") + strerror(errno));
            else if (ret == 0) // No data available
                continue;
            else if (pfd.revents & POLLHUP) {
                std::osyncstream(std::cout) << "Kitchen: Closing automatically" << std::endl;
                // Don't wait for the timeout
                timeout = std::chrono::steady_clock::now();
                break;
            }
            const auto pizza = utils::extract<Pizza>(ipc);
            if (pizza.has_value()) {
                std::osyncstream(std::cout) << "Kitchen: Reading pizza" << std::endl;
                // Increment the timeout
                timeout = std::chrono::steady_clock::now() + std::chrono::seconds(static_cast<long>(5.0 / mult));
                // Send back the pizza when it's cooked
                ipc << *pizza << std::flush;
            }
        }
    });
    // Yield until the timeout is reached
    while (std::chrono::steady_clock::now() < timeout.load())
        std::this_thread::yield();
    // Request stop on the kitchen thread
    kitchenThread.request_stop();
    // std::jthread joins on destruction
}

bool KitchenProcess::order(Pizza pizza)
{
    // If there are already twice as many pizzas as cooks, the kitchen is full
    if (this->_pizzaCount == this->_cookCount * 2) {
        std::osyncstream(std::cout) << "Kitchen #" << this->_id << " is full" << std::endl;
        return false;
    }
    // Just send everything, let the kitchen handle the buffering
    this->_pizzaCount++;
    std::osyncstream(std::cout) << "Kitchen #" << this->_id << " was ordered a \""
        << pizza.type << "\" pizza in size " << pizza.size << std::endl;
    this->ipc([pizza](std::ostream &ipc){ ipc << pizza << std::flush; });
    return true;
}

/**
*  Unused in the end
*/
void KitchenProcess::handleNotification(Notification n)
{
    std::osyncstream(std::cout) << "Kitchen #" << this->_id << " received a notification: " << n << std::endl;
    if (n.isClosing()) {
        this->_closed = true;
        return;
    }
    if (n.isPizza().has_value())
    {
        this->_pizzaCount--;
        std::osyncstream(std::cout) <<PizzaTypeTraits::pushalpha << PizzaSizeTraits::pushalpha
            << PizzaTypeTraits::alpha << PizzaSizeTraits::alpha
            << "Kitchen #" << this->_id << " finished cooking a \""
            << n.isPizza().value().type << "\" pizza in size " << n.isPizza().value().size << std::endl
            << PizzaTypeTraits::popalpha << PizzaSizeTraits::popalpha;
    }
}

void KitchenProcess::notificationThread(std::stop_token st, KitchenProcess &kitchen)
{
    while (!(st.stop_requested() || kitchen.hasClosed())) {
        // Couldn't find how to handle wrongly killed kitchens (e.g. from htop)
        //if (auto status = kitchen.try_wait(); status.has_value()
        //    && (status->is_terminated()
        //        || (status->was_stopped() && !kitchen.wait().was_continued())))
        //    return;
        // Notification n;
        if (const auto status = kitchen.ipc([/*&n, */&kitchen](std::istream &ipc, int fd) -> std::optional<bool> {
                struct pollfd pfd = {fd, POLLIN, 0};
                if (int ret = poll(&pfd, 1, 0); ret < 0)
                    throw std::runtime_error(std::string("poll: ") + strerror(errno));
                else if (ret == 0) // No data available
                    return std::nullopt;
                else if (pfd.revents & POLLHUP) {
                    // Kitchen timeout gives a POLLHUP
                    // their ipc is closed on KitchenProcess::start return
                    std::osyncstream(std::cout) << "Kitchen #" << kitchen._id << " closed" << std::endl;
                    kitchen._closed = true;
                    return false;
                }
                // utils::extract(ipc, n);
                const auto pizza = utils::extract<Pizza>(ipc);
                if (pizza.has_value()) {
                    kitchen._pizzaCount--;
                    std::osyncstream(std::cout) <<PizzaTypeTraits::pushalpha << PizzaSizeTraits::pushalpha
                        << PizzaTypeTraits::alpha << PizzaSizeTraits::alpha
                        << "Kitchen #" << kitchen._id << " finished cooking a \""
                        << pizza->type << "\" pizza in size " << pizza->size << std::endl
                        << PizzaTypeTraits::popalpha << PizzaSizeTraits::popalpha;
                }
                return true;
            }); !status.has_value())
            continue;
        else if (!status.value())
            break;
        // kitchen.handleNotification(n);
    }
    // Reap the subprocess, no zombies pls
    kitchen.wait();
}
