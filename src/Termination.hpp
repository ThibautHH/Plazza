/*
** EPITECH PROJECT, 2024
** The Plazza
** File description:
** Termination
*/

#ifndef TERMINATION_HPP_
#define TERMINATION_HPP_

#include <exception>

/**
 * @brief Class responsible for handling termination of the program
 */
class Termination {
private:
    static constexpr char ProgramName[] = "The Plazza";
    static const std::terminate_handler DefaultTerminateHandler;
    static void terminate();
};

#endif /* !TERMINATION_HPP_ */
