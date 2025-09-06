#include "Port.hpp"

#include <iostream>

Port::Port(std::string_view name)
{

}

void Port::Test()
{
    using namespace std::chrono_literals;

    constexpr unsigned baud = 115200;
    asio::steady_timer timer {m_ioContext};
    asio::error_code errorCode;

    timer.expires_after(10ms);
    timer.wait(errorCode);

    std::cout << "Timer error code = " << errorCode.value() << " \"" << errorCode.message() << "\"\n";

    errorCode.clear();

    m_serial.set_option(asio::serial_port_base::baud_rate(baud), errorCode);

    std::cout << "Serial port error code = " << errorCode.value() << " \"" << errorCode.message() << "\"\n";
}
