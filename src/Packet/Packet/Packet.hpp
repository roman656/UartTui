#ifndef PACKET_PACKET_HPP
#define PACKET_PACKET_HPP

#include <algorithm>
#include <array>
#include <cstdint>
#include <iomanip>
#include <numeric>
#include <vector>

struct Packet final
{
    std::vector<std::uint8_t> data;

    [[nodiscard]]
    std::size_t GetSerializedSize() const noexcept;

    template<class OutputIterator>
    OutputIterator SerializeTo(OutputIterator destinationFirst) const;

    template<class InputIterator>
    void DeserializeFrom(InputIterator sourceFirst);

private:
    static constexpr std::array<std::uint8_t, 4> SYNCROMARKER = { 0xAB, 0x0B, 0xA0, 0xFF };
    static constexpr std::size_t DATA_SIZE_FIELD_SIZE = 4;
    static constexpr std::size_t CRC_SIZE = 1;
};

template<class OutputIterator>
OutputIterator Packet::SerializeTo(OutputIterator destinationFirst) const
{
    const auto dataSize = static_cast<std::uint32_t>(std::size(data));
    const std::size_t bufferSize = GetSerializedSize();
    std::vector<std::uint8_t> buffer(bufferSize);
    auto it = std::begin(buffer);

    it = std::copy(std::cbegin(SYNCROMARKER), std::cend(SYNCROMARKER), it);

    /* Little-endian */
    *it++ = static_cast<std::uint8_t>(dataSize >> (8 * 0));
    *it++ = static_cast<std::uint8_t>(dataSize >> (8 * 1));
    *it++ = static_cast<std::uint8_t>(dataSize >> (8 * 2));
    *it++ = static_cast<std::uint8_t>(dataSize >> (8 * 3));

    it = std::copy(std::cbegin(data), std::cend(data), it);

    const std::uint8_t crc = std::reduce(std::begin(buffer), it, std::uint8_t{});

    *it = crc;

    return std::copy(std::cbegin(buffer), std::cend(buffer), destinationFirst);
}

template<class InputIterator>
void Packet::DeserializeFrom(InputIterator sourceFirst)
{
    /* syncromarker */

    std::vector<std::uint8_t> buffer(std::size(SYNCROMARKER));
    auto it = std::begin(buffer);

    std::copy_n(sourceFirst, std::size(SYNCROMARKER), it);
    std::advance(sourceFirst, std::size(SYNCROMARKER));

    if (!std::equal(std::cbegin(SYNCROMARKER), std::cend(SYNCROMARKER), std::cbegin(buffer)))
    {
        throw std::runtime_error("Packet deserialization error: bad syncromarker");
    }

    /* data size */

    buffer.resize(std::size(SYNCROMARKER) + DATA_SIZE_FIELD_SIZE);

    it = std::begin(buffer) + std::size(SYNCROMARKER);

    std::copy_n(sourceFirst, DATA_SIZE_FIELD_SIZE, it);
    std::advance(sourceFirst, DATA_SIZE_FIELD_SIZE);

    it = std::begin(buffer) + std::size(SYNCROMARKER);

    std::uint32_t dataSize = 0;
    dataSize |= static_cast<std::uint32_t>(*it++ << (8 * 0));
    dataSize |= static_cast<std::uint32_t>(*it++ << (8 * 1));
    dataSize |= static_cast<std::uint32_t>(*it++ << (8 * 2));
    dataSize |= static_cast<std::uint32_t>(*it++ << (8 * 3));

    /* data & crc */

    buffer.resize(std::size(SYNCROMARKER) + DATA_SIZE_FIELD_SIZE + dataSize + CRC_SIZE);

    it = std::begin(buffer) + std::size(SYNCROMARKER) + DATA_SIZE_FIELD_SIZE;
    it = std::copy_n(sourceFirst, dataSize + CRC_SIZE, it);

    --it;    // To crc

    const std::uint8_t readCrc = *it;
    const std::uint8_t crc = std::reduce(std::begin(buffer), it, std::uint8_t{});

    if (crc != readCrc)
    {
        std::ostringstream stream;

        stream << "Packet deserialization error: CRC mismatch, got 0x"
                << std::uppercase << std::hex << std::setw(2) << std::setfill('0')
                << static_cast<unsigned>(readCrc)
                << " expected 0x"
                << std::setw(2) << std::setfill('0')
                << static_cast<unsigned>(crc);

        throw std::runtime_error(stream.str());
    }

    data.resize(dataSize);
    it = std::begin(buffer) + std::size(SYNCROMARKER) + DATA_SIZE_FIELD_SIZE;

    std::copy_n(it, dataSize, std::begin(data));
}

#endif // PACKET_PACKET_HPP
