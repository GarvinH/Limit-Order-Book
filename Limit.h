#ifndef LIMIT_H
#define LIMIT_H

#include <list>
#include "DoubleLinkedList.h"

using namespace std;
using namespace DoubleLinkedList;

class Order;

// placeholder solution because of std::set forcing constant values
class LimitDetails
{
    unsigned int orderSize;
    unsigned int totalVolume;
    Order *headOrder;
    Order *tailOrder;
public:
    LimitDetails();
    LimitDetails(const LimitDetails &other);

    friend class Limit;
};

/**
 * @todo write docs
 */
class Limit
{
    double limitPrice;
    // unsigned int orderSize;
    // unsigned int totalVolume;
    // list<Order> orderList;
    LimitDetails *details; // see comment on limit details class

public:
    Limit(double limitPrice);
    Limit(const Limit &other);
    ~Limit();
    void addOrder(const Order *order) const;
    void cancelOrder(const Order *order) const;
    void fillOrder(unsigned int &quantity) const;
    unsigned int getOrderSize() const;
    unsigned int getTotalVolume() const;
    double getLimitPrice() const;
    bool operator<(const Limit &other) const;
    friend class Order;
};

typedef unsigned int GUID; // replace with most appropriate type for GUIDs
enum ORDER_TYPE { BUY = true, SELL = false };

class Order: public Node
{
    GUID idNumber;
    ORDER_TYPE orderType;
    unsigned int numShares;
    // unsigned int entryTime;
    // unsigned int eventTime;
    const Limit *parentLimit;
public:
    Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, const Limit *parentLimit);
    unsigned int getIdNumber();
    ORDER_TYPE getOrderType();
    unsigned int getNumShares();
    bool operator==(const Order &other);

    friend class Limit;
};

#endif // LIMIT_H
