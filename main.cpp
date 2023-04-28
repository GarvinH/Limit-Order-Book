#include <iostream>
#include "LimitOrderBook.h"

int main(int argc, char **argv) {

    LimitOrderBook book;
    book.limit_buy(1, 12, 10);

    // cout << book;

    book.limit_sell(2, 13, 10);

    // cout << book;

    book.limit_buy(3, 11, 10);
    book.limit_sell(4, 14, 10);

    // cout << book;

    book.limit_sell(5, 11, 15);

    // cout << book;

    book.limit_buy(6, 13.5, 20);

    cout << book;

    return 0;
}
