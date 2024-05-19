/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** BalancingSemaphore
*/

#include "BalancingSemaphore.hpp"

void BalancingSemaphore::acquire()
{
    _semaphore.first.acquire();
    _semaphore.second.release();
    --_counter;
}

void BalancingSemaphore::acquire(std::function<void()> const &lambda)
{
    _semaphore.first.acquire();
    lambda();
    _semaphore.second.release();
    --_counter;
}

void BalancingSemaphore::release()
{
    _semaphore.second.acquire();
    _semaphore.first.release();
    ++_counter;
}

void BalancingSemaphore::release(std::function<void()> const &lambda)
{
    _semaphore.second.acquire();
    lambda();
    _semaphore.first.release();
    ++_counter;
}
