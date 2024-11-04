#include "BitcoinExchange.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <cctype>

// Function to trim leading and trailing whitespace from a string
std::string trim(const std::string &str) {
    std::string::const_iterator start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }
    std::string::const_iterator end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));
    return std::string(start, end + 1);
}

// Constructor: Load exchange rates from the database CSV
BitcoinExchange::BitcoinExchange(const std::string &databaseFile) {
    std::ifstream file(databaseFile.c_str()); // Convert to const char*
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << databaseFile << std::endl;
        return;
    }

    std::string line, date;
    double rate;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        line = trim(line); // Trim the line
        std::istringstream ss(line);
        if (getline(ss, date, ',') && ss >> rate) {
            exchangeRates[trim(date)] = rate; // Store trimmed date
        }
    }
    file.close();
}

// Retrieve the exchange rate for the closest prior date
double BitcoinExchange::getExchangeRate(const std::string &date) const {
    std::map<std::string, double>::const_iterator it = exchangeRates.lower_bound(trim(date)); // Trim date for lookup
    if (it == exchangeRates.begin() && it->first != date) return -1; // No prior date
    if (it == exchangeRates.end() || it->first != date) --it;
    return it->second;
}

// Process each line in the input file and output results
void BitcoinExchange::processInputFile(const std::string &inputFile) const {
    std::ifstream file(inputFile.c_str()); // Convert to const char*
    if (!file.is_open()) {
        std::cerr << "Error: could not open file " << inputFile << std::endl;
        return;
    }

    std::string line, date, valueStr;
    getline(file, line); // Skip the header line

    while (getline(file, line)) {
        line = trim(line); // Trim the line
        std::istringstream ss(line);
        if (!getline(ss, date, '|') || !(getline(ss >> std::ws, valueStr))) {
            std::cerr << "Error: bad input => " << line << std::endl;
            continue;
        }

        date = trim(date); // Trim the date
        valueStr = trim(valueStr); // Trim the value string

        std::stringstream valueStream(valueStr);
        double value;
        if (!(valueStream >> value)) {
            std::cerr << "Error: invalid value." << std::endl;
            continue;
        }

        if (value < 0) {
            std::cerr << "Error: not a positive number." << std::endl;
            continue;
        } else if (value > 1000) {
            std::cerr << "Error: too large a number." << std::endl;
            continue;
        }

        double rate = getExchangeRate(date);
        if (rate < 0) {
            std::cerr << "Error: date not found in database => " << date << std::endl;
            continue;
        }

        double result = rate * value;
        std::cout << date << " => " << value << " = " <<  result << std::endl;
    }
    file.close();
}
