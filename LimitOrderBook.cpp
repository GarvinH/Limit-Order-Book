#include "LimitOrderBook.h"

void LimitOrderBook::onOrderFilled(GUID orderId)
{
    // repository stuff and cleanup

    // save the order to repository
    // cout << "Saved order " << orderId << " to repository" << endl;

    // remove order from local memory
    unordered_map<GUID, Order*>::iterator it = orderMap.find(orderId);
    if (it != orderMap.end())
    {
        delete it->second;
        orderMap.erase(it);
    }
}


ostream& operator<<(ostream& os, const LimitOrderBook& book)
{
    os << book.asks;
    os << endl;
    os << book.bids;

    return os;
}

LimitOrderBook::LimitOrderBook()
{
    bids = LimitManager(ORDER_TYPE::BUY);
    asks = LimitManager(ORDER_TYPE::SELL);
}


// returns true of successfully handled order (executed or added to book)
bool LimitOrderBook::limitBuy(GUID orderId, double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }

    Order *order = new Order(orderId, ORDER_TYPE::BUY, quantity, price);
    asks.fillOrder(order, [&](GUID orderId) -> void {onOrderFilled(orderId);});

    if (order->getNumShares() > 0)
    {
        bids.addOrder(order);
    }

    return true;
}

bool LimitOrderBook::limitSell(GUID orderId, double price, unsigned int quantity)
{
    if (price < 0)
    {
        return false;
    }

    Order *order = new Order(orderId, ORDER_TYPE::SELL, quantity, price);
    bids.fillOrder(order, [&](GUID orderId) -> void {onOrderFilled(orderId);});

    if (order->getNumShares() > 0)
    {
        asks.addOrder(order);
    }

    return true;
}

bool LimitOrderBook::marketBuy(GUID orderId, unsigned int quantity)
{
    return limitBuy(orderId, DBL_MAX, quantity);
}

bool LimitOrderBook::marketSell(GUID orderId, unsigned int quantity)
{
    return limitSell(orderId, 0, quantity);
}

double LimitOrderBook::getBestBuy()
{
    Limit* limit = bids.getBest();
    if (limit == nullptr)
    {
        return -1;
    }

    return limit->getLimitPrice();
}

unsigned int LimitOrderBook::getBestBuyVolume()
{
    Limit* limit = bids.getBest();
    if (limit == nullptr)
    {
        return 0;
    }

    return limit->getTotalVolume();
}

double LimitOrderBook::getBestSell()
{
    Limit* limit = asks.getBest();
    if (limit == nullptr)
    {
        return -1;
    }
    return limit->getLimitPrice();
}

unsigned int LimitOrderBook::getBestSellVolume()
{
    Limit* limit = asks.getBest();
    if (limit == nullptr)
    {
        return 0;
    }

    return limit->getTotalVolume();
}

unsigned int LimitOrderBook::getBuyVolume(double price)
{
    Limit* limit = bids.getLimit(price);
    if (limit == nullptr)
    {
        return 0;
    }

    return limit->getTotalVolume();
}

unsigned int LimitOrderBook::getSellVolume(double price)
{
    Limit* limit = asks.getLimit(price);
    if (limit == nullptr)
    {
        return 0;
    }

    return limit->getTotalVolume();
}


