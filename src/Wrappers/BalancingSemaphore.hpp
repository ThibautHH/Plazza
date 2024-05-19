/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** BalancingSemaphore
*/

#ifndef BALANCINGSEMAPHORE_HPP
#define BALANCINGSEMAPHORE_HPP

#include <atomic>
#include <functional>
#include <semaphore>
#include <utility>

class BalancingSemaphore {
private:
    std::pair<std::counting_semaphore<>, std::counting_semaphore<>> _semaphore;
    std::atomic<uint32_t> _counter;

public:
    BalancingSemaphore(const int initialCount) : _semaphore(initialCount, 0), _counter(initialCount) {}

    void acquire()
    {
        _semaphore.first.acquire();
        _semaphore.second.release();
        --_counter;
    }

    void acquire(std::function<void()> const &lambda)
    {
        _semaphore.first.acquire();
        lambda();
        _semaphore.second.release();
        --_counter;
    }

    void release()
    {
        _semaphore.second.acquire();
        _semaphore.first.release();
        ++_counter;
    }

    void release(std::function<void()> const &lambda)
    {
        _semaphore.second.acquire();
        lambda();
        _semaphore.first.release();
        ++_counter;
    }

    [[nodiscard]] uint32_t getValue() const { return _counter; }
};

#endif // BALANCINGSEMAPHORE_HPP
