#include "LimitOrderBook.h"

ostream& operator<<(ostream& os, LimitOrderBook& book)
{
    map<double, unsigned int>::reverse_iterator mapRit;
    for (mapRit = book.asks.rbegin(); mapRit != book.asks.rend(); ++mapRit)
    {
        os << mapRit->first << " " << mapRit->second << "\n";
    }

    os << "\n";

    for (mapRit = book.bids.rbegin(); mapRit != book.bids.rend(); ++mapRit)
    {
        os << mapRit->first << " " << mapRit->second << "\n";
    }

    return os;
}

// returns true of successfully handled order (executed or added to book)
bool LimitOrderBook::limit_buy(double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }

    while (quantity > 0 && !asks.empty() && asks.begin()->first <= price)
    {
        if (asks.begin()->second > quantity)
        {
            asks.begin()->second -= quantity;
            return true;
        }
        else
        {
            quantity -= asks.begin()->second;
            asks.erase(asks.begin());
        }
    }

    if (quantity > 0)
    {
        bids[price] += quantity;
    }

    return true;
}

bool LimitOrderBook::limit_sell(double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }

    while (quantity > 0 && !bids.empty() && bids.rbegin()->first >= price)
    {
        if (bids.rbegin()->second > quantity)
        {
            bids.rbegin()->second -= quantity;
            return true;
        }
        else
        {
            quantity -= bids.rbegin()->second;
            bids.erase(prev(bids.end()));
        }
    }

    if (quantity > 0)
    {
        asks[price] += quantity;
    }

    return true;
}
