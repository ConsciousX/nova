#include <algorithm>

#include "TradeDB.h"

using namespace std;
    
void TradeDB::iterateTrade(function<void(const TradeRecord &trade)> func) const
{
    for (auto item : db)
    {
        func(item.second);
    }
}

bool TradeDB::addTrade(const TradeRecord &trade)
{
    auto iter = db.find(trade.id);
    if (iter == db.end())
    {
        db.insert(make_pair(trade.id, trade));
        return true;
    }

    return false;
}
