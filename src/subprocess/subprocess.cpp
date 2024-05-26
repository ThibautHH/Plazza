/*
** EPITECH PROJECT, 2024
** Plazza
** File description:
** subprocess
*/

#include <ext/stdio_filebuf.h>
#include <istream>
#include <memory>
#include <sys/socket.h>
#include <sys/wait.h>

#include "subprocess.hpp"

subprocess::subprocess::buffer subprocess::subprocess::make_ipc()
{
    int fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0)
        throw std::runtime_error(std::string("socketpair: ") + strerror(errno));

    _buf = buffer(fds[0], std::ios::out | std::ios::in | std::ios::binary);
    _ipc.rdbuf(std::addressof(_buf));
    return {fds[1], std::ios::out | std::ios::in | std::ios::binary};
}

subprocess::status subprocess::subprocess::wait() const
{
    if (!_pid.has_value())
        throw std::runtime_error("Subprocess not started");
    if (_pid == 0)
        throw std::runtime_error("Cannot wait for child process from child process");
    int s, ret = waitpid(*_pid, std::addressof(s), WCONTINUED | WUNTRACED);
    if (ret < 0)
        throw std::runtime_error(std::string("waitpid: ") + strerror(errno));
    return s;
}

std::optional<subprocess::status> subprocess::subprocess::try_wait() const
{
    if (!_pid.has_value())
        throw std::runtime_error("Subprocess not started");
    if (_pid == 0)
        throw std::runtime_error("Cannot wait for child process from child process");
    int s, ret = waitpid(*_pid, std::addressof(s), WNOHANG | WCONTINUED | WUNTRACED);
    if (ret < 0)
        throw std::runtime_error(std::string("waitpid: ") + strerror(errno));
    else if (ret == 0)
        return std::nullopt;
    return s;
}
