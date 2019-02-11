#pragma once

#include <cstdint>
#include <exception>
#include <stdexcept>
#include <string>
#include <algorithm>
//data
struct SieveEratosthenesData
{
    inline SieveEratosthenesData()
    {

    }
    inline SieveEratosthenesData(const SieveEratosthenesData &copy)
    {
        std::memcpy(data, copy.data, sizeof(block_t) * copy.size);
        size = copy.size;
        begin = data;
        end = data + size;
    }
    inline SieveEratosthenesData(SieveEratosthenesData &&move)
    {
        data = move.data;
        begin = data;
        size = move.size;
        end = data + size;
        move.data = nullptr;
        move.begin = nullptr;
        move.end = nullptr;
        move.size = 0;
    }
    ~SieveEratosthenesData()
    {
        if (data != nullptr)
            delete[] data;
    }

    using block_t = uint8_t;

    inline bool getBit(size_t pos, block_t bit)
    {
        if (pos >= size)
            throw std::range_error("byte(" + std::to_string(pos) + ") Out of range");
        return (data[pos] & (block_t(1) << bit));
    }

    inline uint8_t* getBlock(size_t pos)
    {
        if (pos >= size)
            throw std::range_error("byte(" + std::to_string(pos) + ") Out of range");
        return data + pos;
    }

    inline bool get(size_t idx)
    {
       
        block_t bit = idx % sizeof(block_t);
        size_t pos = (idx - bit) / sizeof(block_t);
        if (pos >= size)
            throw std::range_error("byte(" + std::to_string(pos) + ") Out of range");

        return getBit(pos, bit);
    }

    inline void resize(size_t size_)
    {
        auto new_data = new block_t[size_];
        if (data != nullptr)
        {
            auto delta = size_ - size;
            if (delta >= 0)
            {
                std::memcpy(new_data, data, sizeof(block_t) * size);
                if (delta != 0)
                    std::fill_n(data + size, delta, std::numeric_limits<block_t>::max());
            }
            else
            {
                std::memcpy(new_data, data, sizeof(block_t) * (size + delta));
            }
            delete[]data;
        }
        else
        {
            std::fill_n(data, size, std::numeric_limits<block_t>::max());
        }
        size = size_;
        data = new_data;
        begin = new_data;
        end = new_data + size;
    }

    inline void set(size_t idx)
    {
        block_t bit = idx % sizeof(block_t);
        size_t pos = (idx - bit) / sizeof(block_t);
        if (pos >= size)
            throw std::range_error("byte(" + std::to_string(pos) + ") Out of range");

        auto block = data + pos;
        *block |= block_t(1) << bit;

    }

    inline void clear(size_t idx)
    {
        block_t bit = idx % sizeof(block_t);
        size_t pos = (idx - bit) / sizeof(block_t);
        if (pos >= size)
            throw std::range_error("byte(" + std::to_string(pos) + ") Out of range");

        auto block = data + pos;
        *block &= ~(block_t(1) << bit);
    }

    inline void dataClear()
    {
        if (data != nullptr)
            delete[] data;
        block_t *data = nullptr;
        block_t *begin = nullptr;
        block_t *end = nullptr;
        size_t size = 0;
    }

    block_t *data = nullptr;
    block_t *begin = nullptr;
    block_t *end = nullptr;
    size_t size = 0;
};


inline SieveEratosthenesData SieveEratosthenesCalculate(size_t n)
{
    SieveEratosthenesData data;
    auto size = (n / sizeof(SieveEratosthenesData::block_t)) + 2;
    data.resize(size);
    data.clear(0);
    data.clear(1);
    for (size_t i = 2; i <= n; ++i)
    {
        if (data.get(i))
        {
            for (size_t j = i * i; j <= n; j += i)
                data.clear(j);
        }
    }

    return data;
}

inline void SieveEratosthenesCalculate(SieveEratosthenesData *data, size_t begin, size_t end)
{
    for (size_t i = begin; i <= end; ++i)
    {
        if (data->get(i))
        {
            for (size_t j = i * i; j <= end; j += i)
                data->clear(j);
        }
    }
}