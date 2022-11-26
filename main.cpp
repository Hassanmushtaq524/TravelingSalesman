#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
using namespace std;

double nextDouble(default_random_engine &generator, uniform_real_distribution<double> &distribution) {
    double num = distribution(generator);
    return num;
}

double nodeDistance(int node1, int node2, vector<double> &x, vector<double> &y) {
    return sqrt(pow(x[node1] - x[node2], 2) + pow(y[node1] - y[node2], 2));
}

double getDistance(vector<int> &route,  vector<double> &x, vector<double> &y) {
    int n = route.size();
    double d = 0;
    for (int i = 1; i < n; i++) {
        d += nodeDistance(route[i-1], route[i], x, y);
    }
    return d;
}

void generateNewOrder(vector<int> &route, vector<double> &x, vector<double> &y) {
    int n = x.size();
    int i1 = (rand() % (n-1)) + 1, i2 = (rand() % (n-1)) + 1;
    // cout << i1 << " " << i2 << endl;
    // perform two random swaps
    // it is important that the starting and ending node are 0;
    swap(route[i1], route[i2]);
} 

double Anneal(vector<int> &order,  vector<double> &x, vector<double> &y) {
    srand(unsigned(time(NULL)));
    default_random_engine generator;
    uniform_real_distribution<double> distribution(0.0,1.0);
    // store current and original order
    vector<int> currentOrder(order);
    vector<int> originalOrder;
    double distance0, distance1;
    double T = 1e50;
    double deltaT = 0.99;
    double absoluteT = 0.0001;
    double difference, minDistance;
    distance0 = getDistance(currentOrder, x, y);
    while (T > absoluteT) {
        // copy original order
        originalOrder = currentOrder;
        // randomize it
        generateNewOrder(currentOrder, x, y);
        // get new distance of the new permutation
        distance1 = getDistance(currentOrder, x, y);
        difference = distance1 - distance0;
        // keep new order based on a probability, otherwise revert back
        if (difference < 0 ||  exp((-difference)/T) > nextDouble(generator, distribution)) {
            //  keeping new order
           distance0 = distance1;
        } else {
            // revert
            currentOrder = originalOrder;
        }
        T *= deltaT;
    }
    order = currentOrder;
    minDistance = distance0;
    return minDistance;
}

int shortestNode(int node, vector<int> &order, vector<double> &x, vector<double> &y) {
    int n = x.size();
    double min = DBL_MAX;
    int minNode = 0;
    double distance;
    for (int i = 0; i < n; i++) {
        // if node is current Node or is already in the route, then we skip
        if (i == node || find(order.begin(), order.end(), i) != order.end()) {
            continue;
        }

        distance = nodeDistance(node, i, x, y);

        // if smaller distance found, change minNode and min
        if (distance < min) {
            min = distance;
            minNode = i;
        }

    }
    return minNode;
}

void greedyOrder(vector<int> &order, vector<double> &x, vector<double> &y) {
    int n =  x.size();
    order.clear();
    order.push_back(0);
    while (order.size() != n) {
        order.push_back(shortestNode(order[order.size()-1], order, x, y));
    }
    order.push_back(0);
}

// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints travelling salesman solution
void solve(ifstream &fin, ofstream &fout) {
    
    int n;
    fin >> n;
    // x and y vector hold x and y values of point
    vector<double> x;
    vector<double> y;
    double xVal, yVal;
    for (int i = 0; i < n; i++) {
        fin >> xVal >> yVal;
        x.push_back(xVal);
        y.push_back(yVal);
    }

    // initial order is nodes 0->1...n->0
    vector<int> order;
    

    // we will perform 10 iterations, and restarting each time
    double currentDistance, shortestDistance = DBL_MAX;
    // for (int i = 0; i < 10; i++) {
    //     // restart
        greedyOrder(order, x, y);
        fout << "greedy order: ";
        for (auto x : order) {
            fout << x << " ";
        }
        fout << endl;
        fout << "greedy cost: " << getDistance(order, x, y) << endl;
        currentDistance = Anneal(order, x, y);
        // if (currentDistance < shortestDistance) {
        //     shortestDistance = currentDistance;
        // }
    // }

    fout << currentDistance << endl;
    for (auto x : order) {
        fout << x << " ";
    }
}


int main () {
    
    // Getting all the files in input dir
    DIR *dir; struct dirent *diread;
    vector<string> files;

    if ((dir = opendir("./inputs")) != nullptr) {
        while ((diread = readdir(dir)) != nullptr) {
            files.push_back(diread->d_name);
        }
        closedir (dir);
    } else {
        perror ("opendir");
        return EXIT_FAILURE;
    }
    
    // Running All test cases
    ifstream fin;
    ofstream fout;   
    string inFile, outFile;       
    // for (auto file : files) {
    //     if (file == "." || file == "..")
    //         continue;
    //     cout << file << " "; 
    //     inFile = "./inputs/" + file;
    //     fin.open(inFile.data(), ios::in);
    //     outFile = "./outputs/" + file + "_out"; 
    //     fout.open(outFile.data(), ios::out);
    //     solve(fin, fout);
    //     fin.close();
    //     fout.close();
    // }
    inFile = "./inputs/sampleInput";
        fin.open(inFile.data(), ios::in);
        outFile = "./outputs/sampleInput_out"; 
        fout.open(outFile.data(), ios::out);
        solve(fin, fout);
        fin.close();
        fout.close();
    
    
    
}