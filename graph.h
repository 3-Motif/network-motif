#include <iostream>
#include <vector>
#include <set>
#include <random>
#include "../Eigen/Core"

typedef std::set<std::vector<int>> set;

class Graph{
    private:
    // count the number on 3-node subgraphs present in the graph associated with the adjacency matrix
    std::vector<int> countSubgraph(Eigen::MatrixXi adjacencyMatrix);

    // generate random graph associated with the real graph using switching algorithm
    Eigen::MatrixXi generateRandomGraph();

    // Use the given graphon to generate random graph
    Eigen::MatrixXi generateRandomGraphViaGraphon();

    public:
    Eigen::MatrixXi adjacencyMatrix;
    int vertexCount;
    int edgeCount;

    Graph(const std::string& networkFile);

    // return number of vertices
    int order();
    // return number of edges
    int size();
    // get the entry of matrix[row][col]
    int get(int row, int col);

    // count all the 3-node subgraphs in the real network
    std::vector<int> getAllSubgraphCounts();

    // count all the 3-node subgraphs in the rand network
    std::vector<int> getAllRandSubgraphCounts();

    // From an ensemble of rand networks get the average count of all 3-node subgraphs
    std::vector<double> getAllRandSubgraphAvgCounts(std::size_t ensemble_size);

};