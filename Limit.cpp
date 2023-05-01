#include "Limit.h"
#include <algorithm>

LimitDetails::LimitDetails()
{
    totalVolume = 0;
    orderSize = 0;
}

LimitDetails::LimitDetails(const LimitDetails& other)
{
    totalVolume = other.totalVolume;
    orderSize = other.orderSize;
    headOrder = other.headOrder;
    tailOrder = other.tailOrder;
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


void Limit::addOrder(const Order* order) const
{
    details->totalVolume += order->numShares;

    DoubleLinkedList::pushBack((Node**)&(details->headOrder), (Node**)&details->tailOrder, (Node*)order);
    details->orderSize++;
}

void Limit::cancelOrder(const Order* order) const
{
    DoubleLinkedList::remove((Node**)&(details->headOrder), (Node**)&details->tailOrder, (Node*)order);
    details->orderSize--;
}

void Limit::fillOrder(unsigned int& quantity) const
{
    while (quantity > 0 && details->orderSize > 0)
    {
        if (details->headOrder->getNumShares() > quantity)
        {
            details->headOrder->numShares -= quantity;
            details->totalVolume -= quantity;
            quantity = 0;
        }
        else
        {
            quantity -= details->headOrder->getNumShares();
            details->totalVolume -= details->headOrder->getNumShares();
            DoubleLinkedList::remove((Node**)&details->headOrder, (Node**)&details->tailOrder, (Node*)details->headOrder);
            details->orderSize -= 1;
        }
    }
}


unsigned int Limit::getOrderSize() const
{
    return details->orderSize;
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
