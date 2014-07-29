#include <algorithm>
#include <iostream>

#include "TradeCollector.h"

using namespace std;

void TradeCollector::collectTrade(const TradeDB &db)
{
    //Add db
    if (allDB.find(db.getId()) == allDB.end())
    {
        allDB.insert(db.getId());
    }

    db.iterateTrade([&](const TradeRecord &trade) {
        auto iter = tradeMap.find(trade.id);
        if (iter == tradeMap.end())
        {
            auto result = tradeMap.insert(make_pair(trade.id, set<string>()));
            if (result.second)
            {
                iter = result.first;
            }
        }

        iter->second.insert(db.getId());
    });
}

void TradeCollector::printAll(ostream& os) const
{
    for_each(begin(tradeMap), end(tradeMap), [&](const std::pair<string, set<string>>& trade){
        os<<trade.first;
        string copyFrom;
        vector<string> copyTo;
        for_each(begin(allDB), end(allDB), [&](const string& db){
            if (trade.second.find(db) != trade.second.end())
            {
                if (copyFrom.empty())
                {
                    copyFrom = db;
                }
            }
            else
            {
                copyTo.push_back(db);
            }
        });
        for_each(begin(copyTo), end(copyTo), [&](const string& item){
            os<<" from "<<copyFrom<<" to "<<item;
        });
        os<<endl;
    });
}




