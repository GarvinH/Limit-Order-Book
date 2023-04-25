#include <iostream>
#include "LimitOrderBook.h"

int main(int argc, char **argv) {

    LimitOrderBook book;
    book.limit_buy(12, 10);

    // cout << book;

    book.limit_sell(13, 10);

    // cout << book;

    book.limit_buy(11, 10);
    book.limit_sell(14, 10);

    // cout << book;

    book.limit_sell(11, 15);

    // cout << book;

    book.limit_buy(13.5, 20);

    cout << book;

    return 0;
}
