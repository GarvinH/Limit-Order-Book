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

void Limit::fillOrder(unsigned int& quantity, std::function<void(GUID)> onFilled)
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
            onFilled(headOrder->getIdNumber());
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

LimitManager::LimitManager()
{
    // hack since using template on enum requires either moving
    // all this code into the header
    // and the below constructor isn't available to us
    // when declaring a LimitManager inside another header file
}


LimitManager::LimitManager(ORDER_TYPE orderType)
{
    this->orderType = orderType;
}


bool LimitPointerComp::operator()(const Limit* lhs, const Limit* rhs) const
{
    return *lhs < *rhs;
}

void LimitManager::removeFromSet(Limit* limit)
{
    set<Limit*>::iterator it = find(limits.begin(), limits.end(), limit);
    if (it != limits.end())
    {
        limits.erase(it);
    }
}


void LimitManager::addOrder(Order* order)
{
    if (orderType != order->getOrderType())
    {
        cout << "Error: trying to add order to the wrong side of the book" << endl;
        return;
    }

    unordered_map<double, Limit*>::const_iterator it = priceLimitMap.find(order->getLimitPrice());

    // limit doesn't exist yet
    if (it == priceLimitMap.end())
    {
        Limit *limit = new Limit(order->getLimitPrice());
        limit->addOrder(order);

        limits.insert(limit);
        priceLimitMap[order->getLimitPrice()] = limit;
    }
    else // limit exists
    {
        Limit *limit = priceLimitMap[order->getLimitPrice()];

        if (limit->getOrderSize() == 0)
        {
            limits.insert(limit);
        }

        limit->addOrder(order);
    }
}

void LimitManager::cancelOrder(const Order* order)
{
    if (orderType != order->getOrderType())
    {
        cout << "Error: tried to remove an order from the wrong side of the book" << endl;
        return;
    }

    Limit *parentLimit = order->getParentLimit();
    if (parentLimit != nullptr)
    {
        parentLimit->cancelOrder(order);

        if (parentLimit->getOrderSize() == 0)
        {
            removeFromSet(parentLimit);
        }
    }
}

void LimitManager::fillOrder(Order* order, std::function<void(GUID)> onFilled)
{
    if (orderType == order->getOrderType())
    {
        cout << "Error: trying to fill an order on the same side of the book" << endl;
        return;
    }

    Limit* best = getBest();
    // orderType BUY means BUY tree handling a sell order
    // orderType SELLL means SELL tree handling a buy order
    while (best != nullptr && order->getNumShares() > 0 && ((orderType == ORDER_TYPE::BUY && best->getLimitPrice() >= order->getLimitPrice()) || (orderType == ORDER_TYPE::SELL && best->getLimitPrice() <= order->getLimitPrice())))
    {
        best->fillOrder(order->getNumShares(), onFilled);
        if (best->getOrderSize() == 0)
        {
            removeFromSet(best);
            best = getBest();
        }
    }
}



Limit * LimitManager::getBest()
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

Limit * LimitManager::getLimit(double price)
{
    unordered_map<double, Limit*>::iterator it = priceLimitMap.find(price);
    if (it == priceLimitMap.end())
    {
        return nullptr;
    }

    return priceLimitMap[price];
}


ostream& operator<<(ostream& os, const LimitManager &lm)
{
    set<Limit*>::reverse_iterator rit = lm.limits.rbegin();
    for (; rit != lm.limits.rend(); ++rit)
    {
        os << (*rit)->getLimitPrice() << " " << (*rit)->getTotalVolume() << endl;
    }

    return os;
}


/*
 *
 * LimitManager
 * --------------------------------------------------------------------------
 * Order
 *
 */

Order::Order(GUID idNumber, ORDER_TYPE orderType, unsigned int numShares, double limitPrice)
{
    this->idNumber = idNumber;
    this->orderType = orderType;
    this->numShares = numShares;
    this->limitPrice = limitPrice;
}


unsigned int Order::getIdNumber() const
{
    return idNumber;
}

ORDER_TYPE Order::getOrderType() const
{
    return orderType;
}

unsigned int& Order::getNumShares()
{
    return numShares;
}

double Order::getLimitPrice() const
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

