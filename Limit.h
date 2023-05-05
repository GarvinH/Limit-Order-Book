#ifndef LIMIT_H
#define LIMIT_H

#include <set>
#include <unordered_map>
#include "DoubleLinkedList.h"

using namespace std;
using namespace DoubleLinkedList;

typedef unsigned int GUID; // replace with most appropriate type for GUIDs
enum ORDER_TYPE { BUY = true, SELL = false };

class Order;
template<ORDER_TYPE> class LimitManager;

/**
 * @todo write docs
 */
class Limit
{
    double limitPrice;
    unsigned int orderSize;
    unsigned int totalVolume;
    Order *headOrder;
    Order *tailOrder;

    void addOrder(Order *order);
    void cancelOrder(const Order *order);
public:
    Limit(double limitPrice);
    Limit(const Limit &other);
    ~Limit();

    void fillOrder(unsigned int &quantity, void (*onFill)(GUID orderId));
    unsigned int getOrderSize() const;
    unsigned int getTotalVolume() const;
    double getLimitPrice() const;
    bool operator<(const Limit &other) const;
    friend class Order;
    template<ORDER_TYPE> friend class LimitManager;
};

struct LimitPointerComp
{
    bool operator()(const Limit* lhs, const Limit* rhs);
};

template <ORDER_TYPE orderType>
class LimitManager
{
    set<Limit*, LimitPointerComp> limits;
    unordered_map<double, Limit*> priceLimitMap;
public:
    void addOrder(double price, Order *order);
    void cancelOrder(const Order *order);
    Limit* getBest();

};

class Order: public Node
{
    GUID idNumber;
    ORDER_TYPE orderType;
    unsigned int numShares;
    double limitPrice;
    // unsigned int entryTime;
    // unsigned int eventTime;
    Limit *parentLimit;
public:
    Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, double limitPrice, Limit *parentLimit);
    unsigned int getIdNumber();
    ORDER_TYPE getOrderType();
    unsigned int getNumShares();
    double getLimitPrice();
    bool operator==(const Order &other);
    Limit* getParentLimit() const;

    friend class Limit;
};

#endif // LIMIT_H
