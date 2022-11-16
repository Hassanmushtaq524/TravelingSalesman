#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
using namespace std;



// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints travelling salesman solution
void solve(ifstream &fin, ofstream &fout) {
    
  

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

    
    
}