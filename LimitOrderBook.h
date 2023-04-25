#ifndef LIMITORDERBOOK_H
#define LIMITORDERBOOK_H

#include <iostream>
#include <map>

using namespace std;

/**
 * @todo write docs
 */
class LimitOrderBook
{
    map<double, unsigned int> bids;
    map<double, unsigned int> asks;
public:
    bool limit_buy(double price, unsigned int quantity);
    bool limit_sell(double price, unsigned int quantity);
    friend ostream& operator<<(ostream& os, LimitOrderBook& book);
};

#endif // LIMITORDERBOOK_H
