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

std::iostream subprocess::subprocess::make_ipc()
{
    int fds[2];
    if (socketpair(AF_UNIX, SOCK_STREAM, 0, fds) < 0)
        throw std::runtime_error(std::string("socketpair: ") + strerror(errno));

    _pbuf.emplace(fds[0], std::ios::out | std::ios::in | std::ios::binary);
    _cbuf.emplace(fds[1], std::ios::out | std::ios::in | std::ios::binary);
    _parent_socket.emplace(std::addressof(*_pbuf));
    return std::iostream(std::addressof(*_cbuf));
}

subprocess::status subprocess::subprocess::wait() const
{
    int s, ret = waitpid(*_pid, std::addressof(s), WCONTINUED | WUNTRACED);
    if (ret < 0)
        throw std::runtime_error(std::string("waitpid: ") + strerror(errno));
    return s;
}

std::optional<subprocess::status> subprocess::subprocess::try_wait() const
{
    if (!_pid.has_value())
        return std::nullopt;
    int s, ret = waitpid(*_pid, std::addressof(s), WNOHANG | WCONTINUED | WUNTRACED);
    if (ret < 0)
        throw std::runtime_error(std::string("waitpid: ") + strerror(errno));
    else if (ret == 0)
        return std::nullopt;
    return s;
}
