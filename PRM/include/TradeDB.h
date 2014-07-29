#pragma once

#include <string>
#include <map>
#include <functional>

struct TradeRecord
{
    TradeRecord(const std::string& tradeId)
        :id(tradeId)
    {}
    std::string id;

    //other record
};

class TradeDB
{
public:
    TradeDB(const std::string& dbId)
        :id(dbId)
    {}
    const std::string& getId() const
    {
        return id;
    }
    bool addTrade(const TradeRecord &trade);
    void iterateTrade(std::function<void(const TradeRecord &trade)> func) const;
private:
    std::string id;
    std::map<std::string, TradeRecord> db;
};

