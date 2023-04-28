#ifndef LIMITORDERBOOK_H
#define LIMITORDERBOOK_H

#include <iostream>
#include <set>
#include "Limit.h"

using namespace std;

/**
 * @todo write docs
 */
class LimitOrderBook
{
    set<Limit> bids;
    set<Limit> asks;
public:
    bool limit_buy(GUID orderId, double price, unsigned int quantity);
    bool limit_sell(GUID orderId, double price, unsigned int quantity);
    friend ostream& operator<<(ostream& os, LimitOrderBook& book);
};

#endif // LIMITORDERBOOK_H
