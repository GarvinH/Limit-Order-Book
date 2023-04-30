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

    return 0;
}
