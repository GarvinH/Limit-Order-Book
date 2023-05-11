#include <iostream>
#include "LimitOrderBook.h"

int main(int argc, char **argv) {

    LimitOrderBook book;
    book.limitBuy(1, 12, 10);

    // cout << book;

    book.limitSell(2, 13, 10);

    // cout << book;

    book.limitBuy(3, 11, 10);
    book.limitSell(4, 14, 10);

    // cout << book;

    book.limitSell(5, 11, 15);

    // cout << book;

    book.limitBuy(6, 13.5, 20);

    cout << book;

    cout << "getBestBuy Test 1: " << (book.getBestBuy() == 13.5 ? "Pass" : "Fail") << endl;
    cout << "getBestBuyVolume Test 1: " << (book.getBestBuyVolume() == 10 ? "Pass" : "Fail") << endl;

    cout << "getBestSell Test 1: " << (book.getBestSell() == 14 ? "Pass" : "Fail") << endl;
    cout << "getBestSellVolume Test 1: " << (book.getBestSellVolume() == 10 ? "Pass" : "Fail") << endl;

    cout << "getBuyVolume Test 1: " << (book.getBuyVolume(11) == 5 ? "Pass" : "Fail") << endl;
    cout << "getSellVolume Test 1: " << (book.getSellVolume(17) == 0 ? "Pass" : "Fail") << endl;
    return 0;
}
