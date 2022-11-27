#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
using namespace std;

// Input:
// Output: returns the node closest to the current Node
int minDistanceNode(int curNode, vector<double> &x, vector<double> &y, vector<int> &route) {
    int n = x.size();
    double min = 999999;
    int minNode = 0;
    double distance;
    for (int i = 0; i < n; i++) {
        // if node is current Node or is already in the route, then we skip
        if (i == curNode || find(route.begin(), route.end(), i) != route.end()) {
            continue;
        }

        distance = pow(x[curNode] - x[i], 2) + pow(y[curNode] - y[i], 2);
        distance = sqrt(distance);

        // if smaller distance found, change minNode and min
        if (distance < min) {
            min = distance;
            minNode = i;
        }

    }
    return minNode;
}

// Input: 
// Output: returns the minimum cost to traverse the nodes
double travelSales(vector<double> &x, vector<double> &y, vector<int> &route) {
    // the starting node
    int initialNode = 0;
    // the minimum cost
    double cost = 0;
    // add the initial node to our cost
    route.push_back(initialNode);
    int node = initialNode;

    // loop until we reach the end
    while (route.size() != x.size()) {
        node = minDistanceNode(route[route.size()-1], x, y, route);
        route.push_back(node);
    }

    // calculate final return distance
    route.push_back(initialNode);

    for (int i = 1; i < route.size();i++) {
        cost += sqrt(pow(x[route[i]] - x[route[i-1]],2) + pow(y[route[i]] - y[route[i-1]],2));
    }
    return cost; 
}


// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints travelling salesman solution
void solve(ifstream &fin, ofstream &fout) {
    
    int n; // number of nodes
    fin >> n;
    vector<double> x; // holds x values of nodes
    vector<double> y; // holds y values of nodes

    double xVal, yVal;
    while (n--) {
        fin >> xVal >> yVal;
        x.push_back(xVal);
        y.push_back(yVal);
    }

    vector<int> route;
    fout << travelSales(x, y, route) << endl;
    for (auto x : route) {
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
    for (auto file : files) {
        if (file == "." || file == "..")
            continue;
        inFile = "./inputs/" + file;
        fin.open(inFile.data(), ios::in);
        outFile = "./outputs/" + file + "_out"; 
        fout.open(outFile.data(), ios::out);
        solve(fin, fout);
        fin.close();
        fout.close();
        cout << file << " tested!" << endl; 
    }

    
    
}