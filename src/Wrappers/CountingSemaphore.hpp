/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** CountingSemaphore
*/

#ifndef COUNTINGSEMAPHORE_HPP
#define COUNTINGSEMAPHORE_HPP

#include <atomic>
#include <semaphore>

class CountingSemaphore {
private:
    std::counting_semaphore<> _semaphore;
    std::atomic<uint32_t> _counter;

public:
    CountingSemaphore(const int initialCount) : _semaphore(initialCount), _counter(initialCount) {}

    void acquire();
    void release();
    [[nodiscard]] uint32_t getValue() const { return _counter; }
};

#endif // COUNTINGSEMAPHORE_HPP
