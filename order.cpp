#include "order.h"


Order::Order() {}

Order::Order(const vector<Coord> route) {
    for (auto node : route) {
        tour.push_back(node);
    }
}

Order::Order(Order &o) {
    for (auto node : o.tour) {
        tour.push_back(node);
    }
}

void Order::operator=(const Order &someOrder) {
    tour.clear();
    for (auto node : someOrder.tour) {
        tour.push_back(node);
    }
}

double Order::distance(int node1, int node2) {
    return sqrt(pow(tour[node1].x - tour[node2].x, 2) + pow(tour[node1].y - tour[node2].y, 2));
}

double Order::getDistance() {
    int n = tour.size();
    double d = 0;
    for (int i = 1; i < n; i++) {
        d += distance(i - 1, i);
    }
    d += distance(n - 1, 0);
    return d;
}

void Order::randomize() {
    // switch two cities
    // int n = tour.size();
    // int i1 = rand() % n, i2 = rand() % n; 
    // // swap
    // swap(tour[i1], tour[i2]);
    random_shuffle(tour.begin(), tour.end());
}

void Order::print() {
    for (auto node : tour) {
        cout << "(" << node.x << ", " << node.y << ")" << ", "; 
    }
    cout << endl;
}