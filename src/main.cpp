#include <iostream>

#include <Packet/Packet.hpp>
#include <Port/Port.hpp>
#include <View/MainWindow.hpp>

void ConfigurePort(asio::serial_port& port)
{
    port.set_option(asio::serial_port_base::baud_rate(115200));
    port.set_option(asio::serial_port_base::character_size(std::numeric_limits<std::uint8_t>::digits));
    port.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::even));
    port.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
    port.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
}

int main()
{
    using namespace std::chrono_literals;

    asio::io_context ioContext;
    asio::serial_port port(ioContext);
    asio::steady_timer responseTimer(ioContext);

#ifdef _WIN32
    const std::string portName { "COM3" };
#else
    const std::string portName { "/tmp/ttyAPP" };
#endif

    try
    {
        /* Сперва надо открыть порт и уже потом настраивать */
        port.open(portName);
        ConfigurePort(port);

        std::cout << "[main]: port opened\n";
    }
    catch (const asio::system_error& ex)
    {
        std::cerr << "[main]: " << ex.what() << std::endl;
        return EXIT_FAILURE;
    }

    auto workGuard = asio::make_work_guard(ioContext);    // Нужно, чтобы ioContext.run() сразу не закончился (т. к. пока ему не поручено задач)

    std::thread portThread([&ioContext] { ioContext.run(); });

    std::this_thread::sleep_for(50ms);

    Packet packet;
    packet.data = { 0xAB, 0xCD, 0x00, 0x01, 0xFF, 0x0A };

    std::vector<uint8_t> serializedPacket(packet.GetSerializedSize());
    packet.SerializeTo(std::begin(serializedPacket));

    const auto bufferToSendPtr = std::make_shared<std::vector<uint8_t>>(std::move(serializedPacket));

    asio::async_write(port, asio::buffer(*bufferToSendPtr),
            [bufferToSendPtr](std::error_code errorCode, std::size_t bytesWritten) // bufferToSendPtr захватывается ради продления lifetime до конца асинхронной операции
            {
                if (errorCode)
                {
                    std::cerr << "[port thread]: write error: " << errorCode.message() << '\n';
                }
                else
                {
                    std::cout << "[port thread]: successfully sent " << bytesWritten << " bytes\n";
                }
            });

    responseTimer.expires_after(3s);
    responseTimer.async_wait([&port, &workGuard](std::error_code errorCode)
            {
                if (!errorCode)
                {
                    std::cout << "[port thread]: 3s elapsed, shutting down\n";

                    std::error_code ignore;
                    port.cancel(ignore);
                    port.close(ignore);

                    workGuard.reset();    // Позволим ioContext.run() завершиться
                }
            });

    std::this_thread::sleep_for(4s);

    portThread.join();
}
