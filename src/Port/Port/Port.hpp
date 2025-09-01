#ifndef PORT_PORT_HPP
#define PORT_PORT_HPP

#include <asio.hpp>

class Port final
{
public:
    explicit Port() = default;

    Port(const Port&) = delete;
    Port(Port&&) = delete;
    Port& operator=(const Port&) = delete;
    Port& operator=(Port&&) = delete;

    void Test();

private:
    asio::io_context m_io;
    asio::serial_port m_serial {m_io};
};

#endif // PORT_PORT_HPP
