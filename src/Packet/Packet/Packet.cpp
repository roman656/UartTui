#include "Packet.hpp"

std::size_t Packet::GetSerializedSize() const noexcept
{
    std::size_t size = 0;

    size += std::size(SYNCROMARKER);
    size += DATA_SIZE_FIELD_SIZE;
    size += std::size(data);
    size += CRC_SIZE;

    return size;
}
