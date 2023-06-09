#ifndef LIMIT_H
#define LIMIT_H

#include <set>
#include <unordered_map>
#include <functional>
#include "DoubleLinkedList.h"

using namespace std;
using namespace DoubleLinkedList;

typedef unsigned int GUID; // replace with most appropriate type for GUIDs
enum ORDER_TYPE { BUY = true, SELL = false };

class Order;
class LimitManager;

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
    void fillOrder(unsigned int &quantity, std::function<void(GUID)> onFilled);
public:
    Limit(double limitPrice);
    Limit(const Limit &other);
    ~Limit();

    unsigned int getOrderSize() const;
    unsigned int getTotalVolume() const;
    double getLimitPrice() const;
    bool operator<(const Limit &other) const;
    friend class Order;
    friend class LimitManager;
};

struct LimitPointerComp
{
    bool operator()(const Limit* lhs, const Limit* rhs) const;
};

class LimitManager
{
    ORDER_TYPE orderType;
    set<Limit*, LimitPointerComp> limits;
    unordered_map<double, Limit*> priceLimitMap;
    void removeFromSet(Limit* limit);
public:
    LimitManager();
    LimitManager(ORDER_TYPE orderType);
    void addOrder(Order *order);
    void cancelOrder(const Order *order);

    // takes order from opposite action
    void fillOrder(Order *order, std::function<void(GUID)> onFilled);
    Limit* getBest();
    Limit* getLimit(double price);

    friend ostream& operator<<(ostream& os, const LimitManager &lm);
};

ostream& operator<<(ostream& os, const LimitManager &lm);



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
    Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, double limitPrice);
    unsigned int getIdNumber() const;
    ORDER_TYPE getOrderType() const;
    unsigned int& getNumShares();
    double getLimitPrice() const;
    bool operator==(const Order &other);
    Limit* getParentLimit() const;

    friend class Limit;
};

#endif // LIMIT_H
