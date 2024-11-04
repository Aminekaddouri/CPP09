#include "BitcoinExchange.hpp"
#include <iostream>

int main(int ac, char **av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./btc <input_file>" << std::endl;
        return (1);
    }

    BitcoinExchange btc("data.csv");
    btc.processInputFile(av[1]);

    return (0);
}