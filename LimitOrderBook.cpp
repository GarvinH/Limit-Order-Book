#include "LimitOrderBook.h"

ostream& operator<<(ostream& os, LimitOrderBook& book)
{
    set<Limit>::reverse_iterator mapRit;
    for (mapRit = book.asks.rbegin(); mapRit != book.asks.rend(); ++mapRit)
    {
        os << mapRit->getLimitPrice() << " " << mapRit->getTotalVolume() << "\n";
    }

    os << "\n";

    for (mapRit = book.bids.rbegin(); mapRit != book.bids.rend(); ++mapRit)
    {
        os << mapRit->getLimitPrice() << " " << mapRit->getTotalVolume() << "\n";
    }

    return os;
}

// returns true of successfully handled order (executed or added to book)
bool LimitOrderBook::limit_buy(GUID orderId, double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }


    set<Limit>::iterator it;

    // settle all fillable quantites
    it = asks.begin();
    while (it != asks.end() && it->getLimitPrice() <= price)
    {
        it->fillOrder(quantity);
        if (it->getOrderSize() == 0)
        {
            asks.erase(it);
            it = asks.begin();
        }
        else // left over orders on selling side means all buys are filled
        {
            return true;
        }
    }

    // Leftover orders
    for (it = bids.begin(); it != bids.end(); ++it)
    {
        if (it->getLimitPrice() == price)
        {
            break;
        }
    }

    if (it != bids.end()) // if limit exists
    {
        Order order(orderId, BUY, quantity, &(*it));

        it->addOrder(order);;
    }
    else
    {
        Limit limit(price);
        Order order(orderId, BUY, quantity, &limit);
        limit.addOrder(order);
        bids.insert(limit);
    }

    return true;
}

bool LimitOrderBook::limit_sell(GUID orderId, double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }

    set<Limit>::iterator it;
    set<Limit>::reverse_iterator rit;
    // settle all fillable quantites
    rit = bids.rbegin();
    while (rit != bids.rend() && rit->getLimitPrice() >= price)
    {
        rit->fillOrder(quantity);
        if (rit->getOrderSize() == 0)
        {
            bids.erase(prev(bids.end()));
            rit = bids.rbegin();
        }
        else // left over orders on selling side means all buys are filled
        {
            return true;
        }
    }

    // Leftover orders
    for (it = asks.begin(); it != asks.end(); ++it)
    {
        if (it->getLimitPrice() == price)
        {
            break;
        }
    }

    if (it != asks.end()) // if limit exists
    {
        Order order(orderId, SELL, quantity, &(*it));

        it->addOrder(order);;
    }
    else
    {
        Limit limit(price);
        Order order(orderId, SELL, quantity, &limit);
        limit.addOrder(order);
       asks.insert(limit);
    }

    return true;
}
