#include <map>
#include <unordered_map>
#include <list>
#include <function>
#include <algorithm>

#define OK 0
#define ERR_ADD_ORDER_DUP_ID -1
#define ERR_ADD_ORDER_CREATE_LEVEL -2
#define ERR_REMOVE_ORDER_ID_NOT_EXIST -3
#define ERR_REMOVE_ORDER_LEVEL_NOT_EXIST -4
#define ERR_UPDATE_ORDER_ID_NOT_EXIST -5

struct Order
{
    int id;
    char side;
    double price;
    int quantity;
};

struct Level
{
    Level()
        :total_quantity(0)
    {
    }
    std::list<Order> order_list;
    int total_quantity;
};

class OrderBook
{
public:
    int AddOrder(const Order& order);
    int RemoveOrder(int id);
    int UpdateOrder(int id, int qty);
    double Price(char side, int level);
    double Qty(char side, int level);
    void Iterate(char side, std::fuction<void(const Order&)> func);
private:
    std::map<double, Level> bid_level, offer_level;
    std::unordered_map<int, std::list<Order>::iterator> order_map;
};
