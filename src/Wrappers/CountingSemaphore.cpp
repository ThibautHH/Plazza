/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** CountingSemaphore
*/

#include "CountingSemaphore.hpp"

void CountingSemaphore::acquire()
{
    _semaphore.acquire();
    --_counter;
}

void CountingSemaphore::release()
{
    _semaphore.release();
    ++_counter;
}

void CountingSemaphore::wait()
{
    _semaphore.acquire();
    _semaphore.release();
}
