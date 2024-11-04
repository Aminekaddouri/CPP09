#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <string>
#include <map>

class BitcoinExchange
{
private:
    std::map<std::string, double> exchangeRates;

public:
    BitcoinExchange(const std::string &databaseFile);
    double getExchangeRate(const std::string &date) const;
    void processInputFile(const std::string &inputFile) const;
    // bool isValidDate(const std::string &date) const;
};

#endif