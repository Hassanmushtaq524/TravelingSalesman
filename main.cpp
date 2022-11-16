#include <bits/stdc++.h>
#include <iostream>
#include <math.h>
#include <fstream>
#include <dirent.h>
using namespace std;


// Input: matrix = Matrix of edges, neighbours = vector of edges of current node, colors = vector of colors, degree = queue of nodes and their degrees
// Output: updates the degrees of all the neighbours and updates the degree priority queue
void updateDegree(vector<vector<bool>> &matrix, vector<int> &colors, vector<int> &neighbours, priority_queue<pair<int, int>> &degree) {
    // looping through all neighbours of currNode and updating the degree value
    vector<pair<int, int>> temp;
    pair<int, int> top;
    int pos = 0, i = 0;
    for (auto neighbor: neighbours) {
        // if the node was already colored, then we can move to next neighbor
        if (colors[neighbor] >= 0)
            continue;
        // fill temp vector
        while (!degree.empty()) {
            top = degree.top();
            // if we see the current neighbor, we store its position for later
            if (top.second == neighbor) {
                pos = i;
            }
            degree.pop();
            temp.push_back(top);
            i++;
        }
        // change first pair value of the neighbour we want to change
        temp[pos].first = temp[pos].first + 1;
        // refill degree with updated values
        for (auto pair: temp) {
            degree.push(pair);
        }
        // clear temp
        temp.clear();
        i = 0;
    }
}

// Input: matrix = Matrix of edges, currNode = current node, neighbours = vector of edges of current node
// Output: fills neighbours with edges of current node
void findNeighbours(vector<vector<bool>> &matrix, int &currNode, vector<int> &neighbours) {
    int n = matrix[currNode].size();
    for (int i = 0; i < n; i++) {
        // skip over current node
        if (i == currNode) {
            continue;
        }
        // if we see a true in matrix[node], then we add that column number (other node) to neighbours
        if (matrix[currNode][i]) {
            neighbours.push_back(i);
        }
    }
}

// Input: matrix = Matrix of edges, currNode = current node, neighbours = vector of edges of current node, colors = vector of colors
// Output: sets possible color for currNode
void setPossibleColor(vector<vector<bool>> &matrix, vector<int> &colors, vector<int> &neighbours, int &currNode) {
    int color = 0;
    vector<int> neighbourColors;
    findNeighbours(matrix, currNode, neighbours);
    for (auto neighbour: neighbours) {
        neighbourColors.push_back(colors[neighbour]);
    }   
    // keep incrementing color until we find a new color
    while (find(neighbourColors.begin(), neighbourColors.end(), color) != neighbourColors.end()) {
        color++;
    }

    // set new color for currNode
    colors[currNode] = color;


}

// Input: matrix = Matrix of edges, n = number of nodes, e = number of edges
// Output: Returns minimum colors needed to color a graph 
int graphColor(vector<vector<bool>> &matrix, vector<int> &colors, int &startingNode) {

    // Stores how many neighboring nodes are colored for each node so that we can color the nodes with lowest possible colors first
    // second element in pair is the node
    int n = matrix.size();
    priority_queue<pair<int, int>> degree; 
    for (int i = 0; i < n; i++) {
        if (i == startingNode)
            continue;
        degree.push({-1, i});
    }
    // stores neighbours of a current node
    vector<int> neighbours;
    pair<int, int> top;
    int currNode = startingNode;

    // going through the priority queue
    for (int i = 0; i < n; i++) {
        
        
        setPossibleColor(matrix, colors, neighbours, currNode);
        // updating degree - increments the degrees of all neighbouring nodes of currNode
        updateDegree(matrix, colors, neighbours, degree);
        neighbours.clear();

        // get the top node with smallest domain
        top = degree.top();
        currNode = top.second;
        degree.pop();
    }
    int maxColors = set<int> (colors.begin(), colors.end()).size();
    return maxColors;

}


// Input: fin = pointer to ifstream object, fout = pointer to ofstream object
// Output: prints graphColor solution and matrix to the files
void solve(ifstream &fin, ofstream &fout) {
    
    // n = nodes, e = edges
    int n, e;
    fin >> n >> e;
    // matrix of true / false values representing if an edge exists
    vector<vector<bool>> matrix(n, vector<bool> (n, false));
    vector<int> colors(n, -1);
    int node1, node2;
    // input into matrix
    while (e--) {
        // node1 and node2 are positions in the matrix
        fin >> node1 >> node2;
        matrix[node1][node2] = true;
        matrix[node2][node1] = true;
    }
   
    
    // starting node will be the node with the most edges
    int startingNode = 0, count = 0, mostOnes = 0;
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         if (matrix[i][j]) {
    //             count++;
    //         }
    //     }
    //     if (count > mostOnes) {
    //         mostOnes = count;
    //         startingNode = i;
    //     }
    //     count = 0;
    // }

    startingNode = 0;


    // Outputting to file
    fout << graphColor(matrix, colors, startingNode) << endl;

    // Outputting matrix
     for (auto i : matrix) {
        for (auto j : i ) {
            fout << j << " ";
        }
        fout << endl;
    }
    fout << endl;
    fout << "colors: " << endl;
    for (auto x : colors) {
        fout << x << " ";
    }
    fout << endl;

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