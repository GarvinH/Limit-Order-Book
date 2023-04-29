#include "Limit.h"
#include <algorithm>

LimitDetails::LimitDetails()
{
    totalVolume = 0;
}

LimitDetails::LimitDetails(const LimitDetails& other)
{
    totalVolume = other.totalVolume;
    orderList = other.orderList;
}



Limit::Limit(double limitPrice)
{
    this->limitPrice = limitPrice;
    this->details = new LimitDetails();
}

Limit::Limit(const Limit &other)
{
    this->limitPrice = other.limitPrice;
    this->details = new LimitDetails(*other.details);
}

Limit::~Limit()
{
    delete this->details;
}


void Limit::addOrder(const Order& order) const
{
    details->totalVolume += order.numShares;

    details->orderList.push_back(order);
}

void Limit::cancelOrder(const Order& order) const
{
    list<Order>::iterator it = find(details->orderList.begin(), details->orderList.end(), order);
    if (it != details->orderList.end())
    {
        details->totalVolume -= order.numShares;
        details->orderList.erase(it);
    }
}

void Limit::fillOrder(unsigned int& quantity) const
{
    while (quantity > 0 && !details->orderList.empty())
    {
        if (details->orderList.begin()->getNumShares() > quantity)
        {
            details->orderList.begin()->numShares -= quantity;
            details->totalVolume -= quantity;
            quantity = 0;
        }
        else
        {
            quantity -= details->orderList.begin()->getNumShares();
            details->totalVolume -= details->orderList.begin()->getNumShares();
            details->orderList.erase(details->orderList.begin());
        }
    }
}


unsigned int Limit::getOrderSize() const
{
    return details->orderList.size();
}

unsigned int Limit::getTotalVolume() const
{
    return details->totalVolume;
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
 * Order
 *
 */

Order::Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, const Limit* parentLimit):parentLimit(parentLimit)
{
    this->idNumber = idNumber;
    this->orderType = orderType;
    this->numShares = numShares;
    // this->parentLimit = parentLimit;
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

bool Order::operator==(const Order& other)
{
    return idNumber == other.idNumber;
}
