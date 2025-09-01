#include <iostream>
#include <View/MainWindow.hpp>
#include <Port/Port.hpp>
#include <Packet/Packet.hpp>

int main()
{
    Packet packet;

    packet.data = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    std::vector<std::uint8_t> temp(packet.GetSerializedSize());
    packet.SerializeTo(std::begin(temp));

    std::for_each(std::cbegin(temp), std::cend(temp), [](const std::uint8_t byte)
            { std::cout << +byte << " "; });
    std::cout << '\n';

    Packet packet2;

    packet2.DeserializeFrom(std::cbegin(temp));

    const bool isOk = std::equal(std::cbegin(packet.data), std::cend(packet.data), std::cbegin(packet2.data));

    if (isOk)
    {
        std::cout << "OK" << std::endl;
    }
    else
    {
        std::cout << "ERROR" << std::endl;

        std::for_each(std::cbegin(packet2.data), std::cend(packet2.data), [](const std::uint8_t byte)
                { std::cout << +byte << " "; });
        std::cout << '\n';
    }

    Port port;

    port.Test();

    MainWindow window;

    window.Run();

    return 0;
}
