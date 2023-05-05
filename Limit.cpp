#include "Limit.h"
#include <algorithm>

Limit::Limit(double limitPrice)
{
    this->limitPrice = limitPrice;
    totalVolume = 0;
    orderSize = 0;
    headOrder = nullptr;
    tailOrder = nullptr;
}

Limit::Limit(const Limit &other)
{
    this->limitPrice = other.limitPrice;
    totalVolume = other.totalVolume;
    orderSize = other.orderSize;
    headOrder = other.headOrder;
    tailOrder = other.tailOrder;
}

Limit::~Limit()
{
    delete this->headOrder;
}


void Limit::addOrder(Order* order)
{
    totalVolume += order->numShares;
    order->parentLimit = this;

    DoubleLinkedList::pushBack((Node**)&(headOrder), (Node**)&tailOrder, (Node*)order);
    orderSize++;
}

void Limit::cancelOrder(const Order* order)
{
    totalVolume -= order->numShares;
    DoubleLinkedList::remove((Node**)&(headOrder), (Node**)&tailOrder, (Node*)order);
    orderSize--;
}

void Limit::fillOrder(unsigned int& quantity, void (*onFill)(GUID orderId))
{
    while (quantity > 0 && orderSize > 0)
    {
        if (headOrder->getNumShares() > quantity)
        {
            headOrder->numShares -= quantity;
            totalVolume -= quantity;
            quantity = 0;
        }
        else
        {
            quantity -= headOrder->getNumShares();
            totalVolume -= headOrder->getNumShares();
            DoubleLinkedList::remove((Node**)&headOrder, (Node**)&tailOrder, (Node*)headOrder);
            onFill(headOrder->getIdNumber());
            orderSize -= 1;
        }
    }
}


unsigned int Limit::getOrderSize() const
{
    return orderSize;
}

unsigned int Limit::getTotalVolume() const
{
    return totalVolume;
}

double Limit::getLimitPrice() const
{
    return limitPrice;
}


bool Limit::operator<(const Limit& other) const
{
    return limitPrice < other.limitPrice;
}


/*
 *
 * Limit
 * --------------------------------------------------------------------------
 * LimitManager
 *
 */

bool LimitPointerComp::operator()(const Limit* lhs, const Limit* rhs)
{
    return *lhs < *rhs;
}



template<ORDER_TYPE orderType> void LimitManager<orderType>::addOrder(double price, Order* order)
{
    unordered_map<double, Limit*>::const_iterator it = priceLimitMap.find(price);

    // limit doesn't exist yet
    if (it == priceLimitMap.end())
    {
        Limit *limit = new Limit(price);
        limit->addOrder(order);

        limits.insert(limit);
        priceLimitMap[price] = limit;
    }
    else // limit exists
    {
        Limit *limit = priceLimitMap[price];

        if (limit->getOrderSize() == 0)
        {
            limits.insert(limit);
        }

        limit->addOrder(order);
    }
}

template<ORDER_TYPE orderType> void LimitManager<orderType>::cancelOrder(const Order* order)
{
    Limit *parentLimit = order->getParentLimit();
    if (parentLimit != nullptr)
    {
        parentLimit->cancelOrder(order);

        if (parentLimit->getOrderSize() == 0)
        {
            set<Limit*>::iterator it = find(limits.begin(), limits.end(), parentLimit);
            limits.erase(it);
        }
    }
}


template<ORDER_TYPE orderType> Limit * LimitManager<orderType>::getBest()
{
    if (limits.empty())
    {
        return nullptr;
    }

    switch(orderType)
    {
        case ORDER_TYPE::BUY:
            return *limits.rbegin();
            break;
        case ORDER_TYPE::SELL:
            return *limits.begin();
            break;
    }

    return nullptr;
}



/*
 *
 * LimitManager
 * --------------------------------------------------------------------------
 * Order
 *
 */

Order::Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, double limitPrice, Limit* parentLimit)
{
    this->idNumber = idNumber;
    this->orderType = orderType;
    this->numShares = numShares;
    this->limitPrice = limitPrice;
    this->parentLimit = parentLimit;
}


unsigned int Order::getIdNumber()
{
    return idNumber;
}

ORDER_TYPE Order::getOrderType()
{
    return orderType;
}

unsigned int Order::getNumShares()
{
    return numShares;
}

double Order::getLimitPrice()
{
    return limitPrice;
}


bool Order::operator==(const Order& other)
{
    return idNumber == other.idNumber;
}

Limit * Order::getParentLimit() const
{
    return parentLimit;
}

