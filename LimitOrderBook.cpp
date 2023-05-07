#include "LimitOrderBook.h"

void onOrderFilled(GUID orderId)
{

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
    asks.fillOrder(order, &onOrderFilled);

    if (order->getNumShares() > 0)
    {
        bids.addOrder(order);
    }

    return true;
}

bool LimitOrderBook::limitSell(GUID orderId, double price, unsigned int quantity)
{
    if (price <= 0)
    {
        return false;
    }

    Order *order = new Order(orderId, ORDER_TYPE::SELL, quantity, price);
    bids.fillOrder(order, &onOrderFilled);

    if (order->getNumShares() > 0)
    {
        asks.addOrder(order);
    }

    return true;
}
