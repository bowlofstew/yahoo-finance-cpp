#pragma once
#ifndef __READER__
#define __READER__

#include <string>
#include <vector>
#include <fstream>

#include <boost/algorithm/string.hpp>

class row {
public:
    const std::string date;
    const double open;
    const double high;
    const double low;
    const double close;
    const long volume;
    const double adjusted_close;

    row(const std::string& dateA, double openA, double highA, double lowA,
        double closeA, long volumeA, double adjA) : date(dateA),
                                                    open(openA),
                                                    high(highA),
                                                    low(lowA),
                                                    close(closeA),
                                                    volume(volumeA),
                                                    adjusted_close(adjA) {}
};


class table {
public:
    const std::string symbol;
    table(const std::string& symbolA) : symbol(symbolA){}
    void add_row(const row& r) {
        rows.push_back(r);
    }
    std::vector<row> rows;
};

class reader {
public:
    table get_from_file(const std::string& file) {
        std::vector<std::string> symbols;
        boost::split(symbols, file, boost::is_any_of("_"));
        if(symbols.size() != 2) {
            throw new std::runtime_error("incorrect number of symbol tokens");
        }
        table t(symbols[0]);
        bool is_header = true;
        std::ifstream input(file);
        for( std::string line; getline( input, line ); ) {
            if(is_header) {
                is_header = false;
            } else {
                std::vector<std::string> csv_records;
                boost::split(csv_records, line, boost::is_any_of(","));
                if(csv_records.size() != 7) {
                    throw new std::runtime_error("invalid number of CSV fields");
                }
                row r(csv_records[0],
                      std::stod(csv_records[1]),
                      std::stod(csv_records[2]),
                      std::stod(csv_records[3]),
                      std::stod(csv_records[4]),
                      std::stol(csv_records[5]),
                      std::stod(csv_records[6])
                );
                t.add_row(r);
            }
        }
        return t;
    }
};

#endif