#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
#include "coord.h"
#include "order.h"
using namespace std;


double nextDouble() {
    double f = (double) rand() / RAND_MAX;
    return f;
}

double Anneal(vector<Coord> &path) {
    srand(unsigned(time(0)));
    Order currentOrder(path);
    
    double distance0, distance1;
    double T = 10000.0;
    double deltaT = 0.99;
    double absoluteT = 0.0001;
    double difference, minDistance;
    Order originalOrder, shortestOrder;
    distance0 = currentOrder.getDistance();
    while (T > absoluteT) {
        // get initial distance
        originalOrder = currentOrder;
        // randomize it
        currentOrder.randomize();
        // get new distance of the new permutation
        distance1 = currentOrder.getDistance();
        difference = distance1 - distance0;
        // keep new order based on a probability, otherwise revert back
        if (difference < 0 || exp((-difference)/T) < nextDouble()) {
            //  keeping new order
           distance0 = distance1;
        } else {
            currentOrder = originalOrder;
        }
        T *= deltaT;
    }
    path.clear();
    for (auto node : currentOrder.tour) {
        path.push_back(node);
    }
    minDistance = distance0;
    return minDistance;
}

// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints travelling salesman solution
void solve(ifstream &fin, ofstream &fout) {
    
    int n; 
    fin >> n;

    vector<Coord> path;
    double xVal, yVal;

    while (n--) {
        fin >> xVal >> yVal;
        path.push_back(Coord(xVal, yVal));
    }

    double shortestPath = Anneal(path);
    fout << shortestPath << endl;
    for (auto node : path) {
        fout << "(" << node.x << ", " << node.y << "), ";
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
        cout << file << " "; 
        inFile = "./inputs/" + file;
        fin.open(inFile.data(), ios::in);
        outFile = "./outputs/" + file + "_out"; 
        fout.open(outFile.data(), ios::out);
        solve(fin, fout);
        fin.close();
        fout.close();
    }

    // inFile = "./inputs/sampleInput";
    //     fin.open(inFile.data(), ios::in);
    //     outFile = "./outputs/sampleInput_out"; 
    //     fout.open(outFile.data(), ios::out);
    //     solve(fin, fout);
    //     fin.close();
    //     fout.close();
    
}