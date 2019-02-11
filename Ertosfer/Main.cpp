#include "Ertosfer.h"
#include <iostream>
#include <functional>
#include <thread>
#include <future>

int main()
{
    const size_t num = 1000000;
    std::cout << " start calculate! \n";
    auto result = SieveEratosthenesCalculate(num);
    auto memory_used = sizeof(SieveEratosthenesData::block_t) * result.size;
    std::cout << " memory used " << memory_used << "byte. " << memory_used / 1024 << "Kb. " << memory_used / 1024 / 1024 << "Mb.\n";
    std::cout << " calculated completed!\n";

    int tab = 0;
    for (size_t i = 2; i <= 100; ++i)
    {
        if (result.get(i))
        {
            std::cout << i << "\t";
            tab++;
            if (tab > 10)
            {
                std::cout << "\n";
                tab = 0;
            }
        }
    }

    SieveEratosthenesData data;
    size_t interval = 1000 * 1000 * 100;
    data.resize( 6 * interval + 5);
    memory_used = sizeof(SieveEratosthenesData::block_t) * data.size;
    std::cout << "\n memory used " << memory_used << "byte. " << memory_used / 1024 << "Kb. " << memory_used / 1024 / 1024 << "Mb.\n";

    auto async1 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 2, 1 * interval); });
    auto async2 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 1 * interval + 1, 2 * interval); });
    auto async3 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 2 * interval + 1, 3 * interval); });
    auto async4 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 3 * interval + 1, 4 * interval); });
    auto async5 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 4 * interval + 1, 5 * interval); });
    auto async6 = std::async(std::launch::async, [&data, interval]() { SieveEratosthenesCalculate(&data, 5 * interval + 1, 6 * interval); });


    async1.get();
    async2.get();
    async3.get();
    async4.get();
    async5.get();
    async6.get();

    for (size_t i = 0; i < 6; ++i)
    {
        tab = 0;
        std::cout << "\n";
        for (size_t ii = 0; tab < 10; ++ii)
        {
            size_t v = i * interval + ii;
            if (data.get(v))
            {
                std::cout << v << "\t";
                tab++;
            }
        }
    }

    system("pause");
    return 0;
}