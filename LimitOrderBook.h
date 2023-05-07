#ifndef LIMITORDERBOOK_H
#define LIMITORDERBOOK_H

#include <iostream>
#include <unordered_map>
#include "Limit.h"

using namespace std;

/**
 * @todo write docs
 */
class LimitOrderBook
{
    LimitManager bids;
    LimitManager asks;
    unordered_map<GUID, Order*> orderMap;
public:
    LimitOrderBook();
    bool limitBuy(GUID orderId, double price, unsigned int quantity);
    bool limitSell(GUID orderId, double price, unsigned int quantity);
    friend ostream& operator<<(ostream& os, const LimitOrderBook& book);
    friend void onOrderFilled(GUID orderId);
};

#endif // LIMITORDERBOOK_H
