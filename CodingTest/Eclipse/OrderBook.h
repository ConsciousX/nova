#include "OrderBook.h"

int OrderBook::AddOrder(const Order& order)
{
    if (order_map.find(order.id) != order_map.end())
    {
        return ERR_ADD_ORDER_DUP_ID;
    }

    if (order.side == 'B')
    {
        auto iter = bid_level.find(order.price);
        if (iter == bid_level.end())
        {
            //Create a new level
            auto result = bid_level.insert(std::make_pair(order.price, Level));
            if (result.second == false)
            {
                return ERR_ADD_ORDER_CREATE_LEVEL;
            }

            Level* level = &(result.first->seond);
            level->total_quantity += order.quantity;
            level->push_back(order);
            order_map[order.id] = level->rbegin();
        }
    }
    else
    {
        auto iter = offer_level.find(order.price);
        if (iter == offer_level.end())
        {
            //Create a new level
            auto result = offer_level.insert(std::make_pair(order.price, Level));
            if (result.second == false)
            {
                return ERR_ADD_ORDER_CREATE_LEVEL;
            }

            Level* level = &(result.first->seond);
            level->total_quantity += order.quantity;
            level->push_back(order);
            order_map[order.id] = level->rbegin();
        }
    }

    return OK;
}

int OrderBook::RemoveOrder(int id)
{
    auto order_iter = order_map.find(order.id);
    if (order_iter == order_map.end())
    {
        return ERR_REMOVE_ORDER_ID_NOT_EXIST;
    }

    Order* order = *(order_iter->second);
    if (order->side == 'B')
    {
        auto level_iter = bid_level.find(order->price);
        if (level_iter == bid_level.end())
        {
            return ERR_REMOVE_ORDER_LEVEL_NOT_EXIST;
        }

        level_iter->second.total_quantity -= order.quantity;
        level_iter->second.erase(order_iter->second);

        if (level_iter->second.empty())
        {
            bid_level.erase(level_iter);
        }
    }
    else
    {
        auto level_iter = offer_level.find(order->price);
        if (level_iter == offer_level.end())
        {
            return ERR_REMOVE_ORDER_LEVEL_NOT_EXIST;
        }

        level_iter->second.total_quantity -= order.quantity;
        level_iter->second.erase(order_iter->second);

        if (level_iter->second.empty())
        {
            offer_level.erase(level_iter);
        }
    }

    order_map.erase(order_iter);

    return OK;
}

int OrderBook::UpdateOrder(int id, int qty)
{
    auto order_iter = order_map.find(id);
    if (order_iter == order_map.end())
    {
        return ERR_UPDATE_ORDER_ID_NOT_EXIST;
    }


    Order* order = *(order_iter->second);
    if (order->side == 'B')
    {
        auto level_iter = bid_level.find(order->price);
        if (level_iter == bid_level.end())
        {
            return ERR_UPDATE_ORDER_LEVEL_NOT_EXIST;
        }

        level_iter->second.total_quantity += (qty - order.quantity);
    }
    else
    {
        auto level_iter = offer_level.find(order->price);
        if (level_iter == offer_level.end())
        {
            return ERR_UPDATE_ORDER_LEVEL_NOT_EXIST;
        }

        level_iter->second.total_quantity += (qty - order.quantity);
    }


    order_iter->second->quantity = qty;

    return OK;
}

double OrderBook::Price(char side, int level)
{
    if (side == 'B')
    {
        auto iter = bid_level.rbegin();
        std::advance(iter , level);

        return iter->first;
    }
    else
    {
        auto iter = offer_level.begin();
        std::advance(iter , level);

        return iter->first;
    }
}

int OrderBook::Qty(char side, int level)
{
    if (side == 'B')
    {
        auto iter = bid_level.rbegin();
        std::advance(iter, level);

        return iter->second.total_quantity;
    }
    else
    {
        auto iter = offer_level.begin();
        std::advance(iter , level);

        return iter->second.total_quantity;
    }
}

void OrderBook::Iterate(char side, std::function<void(const Order&)> func)
{
    if (side == 'B')
    {
        for(auto i = bid_level.rbegin();i != bid_level.rend();++i)
        {
            for(auto j = i->second.begin();j != i->second.end();++j)
            {
                func(*j);
            }
        }
    }
    else
    {
        for(auto i = ask_level.begin();i != ask_level.end();++i)
        {
            for(auto j = i->second.begin();j != i->second.end();++j)
            {
                func(*j);
            }
        }
    }
}

    
