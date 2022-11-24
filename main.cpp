#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
#include <float.h>
using namespace std;


// 
// Output: returns the distance between two nodes
double nodeDistance(int node1, int node2, vector<double> &x, vector<double> &y) {
    // cout << x[node1] << " " << x[node2] << endl;
    // cout << y[node1] << " " << y[node2] << endl;
    double distance = sqrt(pow(x[node1] - x[node2], 2) + pow(y[node1] - y[node2], 2));
    return distance;
}

// Input: 
// Output: returns the minimum cost to traverse the nodes
double travelSales(int pos, double currentLength, vector<double> &x, vector<double> &y, vector<int> &route, double &minCost) {
   int n = route.size();
   double newLength;
   if (pos == n - 1) {
    minCost = min(minCost,  currentLength + nodeDistance(route[pos], route[0], x, y));
   } else {
    for (int i = pos + 1; i < n; i++) {
        swap(route[pos + 1], route[i]);
        newLength = currentLength + nodeDistance(route[pos], route[pos + 1], x, y);
        // skip if distance to next node already greater than our current best
        if (newLength >= minCost) {
            continue;
        }
            minCost = min(minCost, travelSales(pos + 1, newLength, x, y, route, minCost));
        
        // undo swap
        swap(route[pos + 1], route[i]);
    }
   }
    return minCost;
}   


// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints travelling salesman solution
void solve(ifstream &fin, ofstream &fout) {
    
    int n; // number of nodes
    fin >> n;
    vector<double> x; // holds x values of nodes
    vector<double> y; // holds y values of nodes
    vector<int> route(n, 0);
    // initial route
    for (int i = 0; i < n; i++) {
        route[i] = i;
    }
    double xVal, yVal;
    while (n--) {
        fin >> xVal >> yVal;
        x.push_back(xVal);
        y.push_back(yVal);
    }
    


    
    int pos = 0;
    double minCost = DBL_MAX;
    double currentLength = 0;
    fout << travelSales(pos, currentLength, x, y, route, minCost) << endl;
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