#ifndef LIMITORDERBOOK_H
#define LIMITORDERBOOK_H

#include <iostream>
#include <unordered_map>
#include <cfloat>
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
    void onOrderFilled(GUID orderId);
public:
    LimitOrderBook();
    bool limitBuy(GUID orderId, double price, unsigned int quantity);
    bool limitSell(GUID orderId, double price, unsigned int quantity);
    bool marketBuy(GUID orderId, unsigned int quantity);
    bool marketSell(GUID orderId, unsigned int quantity);
    double getBestBuy();
    unsigned int getBestBuyVolume();
    double getBestSell();
    unsigned int getBestSellVolume();
    unsigned int getBuyVolume(double price);
    unsigned int getSellVolume(double price);
    friend ostream& operator<<(ostream& os, const LimitOrderBook& book);
};

#endif // LIMITORDERBOOK_H
