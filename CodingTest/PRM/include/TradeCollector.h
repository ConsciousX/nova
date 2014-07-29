#pragma once

#include <map>
#include <set>

#include "TradeDB.h"

class TradeCollector
{
public:
    void collectTrade(const TradeDB &db);

    void printAll(std::ostream& os) const;
private:
    std::map<std::string, std::set<std::string>> tradeMap;
    std::set<std::string> allDB;
};

