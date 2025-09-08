#include <gtest/gtest.h>

#include <Packet/Packet.hpp>

TEST(PacketTests, SerializedPacketSizeIsValid)
{
    /* Arrange */
    const std::vector<std::uint8_t> data { 1, 2, 3, 4, 5, 6 };
    const Packet sut { data };
    const std::size_t expectedValue = 4 + 4 + data.size() + 1;    // sync + dataSize + data + crc

    /* Act */
    const std::size_t actualValue = sut.GetSerializedSize();

    /* Assert */
    ASSERT_EQ(expectedValue, actualValue);
}
