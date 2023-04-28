# Limit Order Book

This repo tracks the implementation of a limit order book in increasing complexity.

1. Basic bid and ask tracking (FINISHED)
2. Limit and Order tracking (FINISHED)
3. Optimal performance (TBD)

## Basic bid and ask
Two lists that track quantities of prices. Capable of tracking executions when prices meet limit.

## Limit and Order tracking
Built with inspiration from [this blog](https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/).
However, it does not attempt to meet the performance requirements expected of a Limit Order Book. This branch acts as a milepoint towards the "Optimal Performance" version of the LOB.

Add - O(n) where n is the # of limits
Cancel - O(m) where m is the # of orders within a limit
Execute - Not implemented on this branch (ie, will be on Optimal Performance branch)
GetVolumeAtLimit - Not implemented on this branch
GetBestBid/Ask - Not implemented on this branch

The reason for the slower run time is the use of STL data structures and some of the limitations forced on its API which lower performance when compared to manually implementing the data structures.

## Optimal Performance
Builds off of "Limit and Order tracking" branch, but with performance aims of:
Add - O(log n) for the first order at a limit, and O(1) for all others
Cancel - O(1)
Execute - O(1)
GetVolumeAtLimit - O(1)
GetBestBid/Ask - O(1)

## Usage
### C++
This project uses CMake with cpp (GCC) 12.2.1


## Development
### Linux
This project was built using Fedora Linux and KDevelop. No guarantees that other environments will work out of box; may require a small amount of tinkering. For example, it should work with CLion on Windows with a small amount of adjustment.
