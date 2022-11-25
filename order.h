#ifndef ORDER_H
#define ORDER_H

#include "coord.h"
#include <bits/stdc++.h>

using namespace std;

class Order {
    public: 
        Order();
        Order(const vector<Coord> route);
        // copy constructor
        Order(Order &o);
        // 
        void operator=(const Order &someOrder);
        // returns total distance of the tour
        double getDistance();
        // randomizes the tour
        void randomize();

        void print();

        double distance(int node1, int node2);
        vector<Coord> tour;
        
};

#endif