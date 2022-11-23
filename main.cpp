#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
using namespace std;



// Input: 
// Output: returns the minimum cost to traverse the nodes
double travelSales(int node, vector<double> &x, vector<double> &y, vector<int> route) {
    route.push_back(node);
    if (route.size() == x.size()) {
        double distance = sqrt(pow(x[node] - x[0], 2) + pow(y[node] - y[0], 2));
        return distance;
    }
    int n = x.size();
    int minNode;
    double minCost = 99999;
    double cost;
    for (int i = 0; i < n; i++) {
        // node has not been explored
        if (find(route.begin(), route.end(), i) == route.end()) {
            cost = travelSales(i, x, y, route);
            if (cost < minCost) {
                minCost = cost;
                minNode = i;
            }
        }
    }
    double distance = sqrt(pow(x[node] - x[minNode], 2) + pow(y[node] - y[minNode], 2));
    return minCost + distance;
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
    int node = 0;
    double cost = 0;
    fout << travelSales(node, x, y, route) << endl;
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