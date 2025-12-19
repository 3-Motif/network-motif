#include "graph.h"

// util function for getting random int
int getRandomNumber(int minValue, int maxValue){
    std::random_device rd; 
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(minValue, maxValue);
    return dist(gen);
}
// util function for getting random float
float getRandomNumber(float minValue, float maxValue){
    std::random_device rd; 
	static std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(minValue, maxValue);

    return dist(gen);
}


// hardcoded degree-sets of all 3-node subgraphs
set subgraph_1 = {{0,2}, {1,0}};
set subgraph_2 = {{2,0}, {0,1}};
set subgraph_3 = {{1,0}, {0,1}, {1,1}};
set subgraph_4 = {{2,1}, {0,1}, {1,1}};
set subgraph_5 = {{1,1}, {1,0}};
set subgraph_6 = {{2,2}, {1,1}};
set subgraph_7 = {{0,2}, {1,1}, {2,0}};
set subgraph_8 = {{1,1}};
set subgraph_9 = {{0,2}, {2,1}};
set subgraph_10 = {{2,0}, {1,2}};
set subgraph_11 = {{1,2}, {1,1}, {2,1}};
set subgraph_12 = {{2,1}, {1,2}, {2,2}};
set subgraph_13 = {{2,2}};

std::vector<set> degree_sets = {subgraph_1, subgraph_2, subgraph_3, subgraph_4, subgraph_5, subgraph_6, subgraph_7, subgraph_8, subgraph_9, subgraph_10, subgraph_11, subgraph_12, subgraph_13};

std::vector<int> Graph::countSubgraph(Eigen::MatrixXi adjacencyMatrix){
    std::vector<int> counts(degree_sets.size());

    std::size_t _order = adjacencyMatrix.rows();

    for (size_t i = 0; i < _order; i++){
        for (std::size_t j = i+1; j < _order; j++){
            for (std::size_t k = j+1; k < _order; k++){
                Eigen::MatrixXi curr_subgraph(3,3);
                curr_subgraph(0,0) = adjacencyMatrix(i,i);
				curr_subgraph(0,1) = adjacencyMatrix(i,j);
				curr_subgraph(0,2) = adjacencyMatrix(i,k);

				curr_subgraph(1,0) = adjacencyMatrix(j,i);
				curr_subgraph(1,1) = adjacencyMatrix(j,j);
				curr_subgraph(1,2) = adjacencyMatrix(j,k);

				curr_subgraph(2,0) = adjacencyMatrix(k,i);
				curr_subgraph(2,1) = adjacencyMatrix(k,j);
				curr_subgraph(2,2) = adjacencyMatrix(k,k);

                // calculate the row and column sums of this subgraph
				Eigen::VectorXi row_sum = curr_subgraph.rowwise().sum();
				Eigen::VectorXi col_sum = curr_subgraph.colwise().sum();

                // Construct the degree set of this subgraph --(in_degree, out_degree)
				set curr_degree_set = { { col_sum(0), row_sum(0)}, { col_sum(1), row_sum(1)}, { col_sum(2), row_sum(2)}};

                for (size_t m = 0; m < counts.size(); m++){
                    if(curr_degree_set == degree_sets[m]) counts[m] = counts[m] + 1;
                }
            }
        }
    }
    return counts;
    
}


Eigen::MatrixXi Graph::generateRandomGraph(){
    Eigen::MatrixXi randGraph = adjacencyMatrix;

    // 1000 is working for now
    std::size_t switchingSteps = edgeCount * 1000;
    for (std::size_t i = 0; i < switchingSteps; i++){
        int source1 = getRandomNumber(0, vertexCount-1);
        int source2 = getRandomNumber(0, vertexCount-1);
        int target1 = getRandomNumber(0, vertexCount-1);
        int target2 = getRandomNumber(0, vertexCount-1);
        // prevent trivial exchange and self-edge
        if(source1 == source2 || source1 == target2) continue;

        // check if the edge exists
        if(randGraph(source1, target1) != 1 || randGraph(source2, target2) != 1) continue;

        // prevent double edges
        if(randGraph(target1, source2) == 1 || randGraph(target2, source1) == 1) continue;

        // swtich the edges
        randGraph(source1, target1) = 0;
        randGraph(source2, target2) = 0;
        randGraph(source1, target2) = 1;
        randGraph(source2, target1) = 1;
    }
    return randGraph;
}

// Eigen::MatrixXi Graph::generateRandomGraphViaGraphon(){
//     // the graphon function
//     float graphon(vertex1, vertex2){
//         // for a constant graphon -- f(x,y) = p = 0.4
//         const float p = 0.4;
//         return p
//     }

//     std::vector<float> vertices(vertexCount);

//     // give each vertices a randomly allocated points from the interval [0,1]
//     for (std::size_t i = 0; i < vertexCount; i++){
//         vertices[i] = getRandomNumber(0.0, 1.0);
//     }

//     Eigen::MatrixXi randomGraph;
//     std::random_device rd;
//     std::mt19937 gen(rd());

//     for (std::size_t i = 0; i < vertexCount; i++){
//         for (std::size_t j = 0; j < vertexCount; j++){
//             if (i == j){
//                 randomGraph(i, j) = 0;  // Zero on the diagonal
//             } else {
//                 std::bernoulli_distribution dist(graphon(vertices[i], vertices[j])); 
//                 randomGraph(i, j) = dist(gen);
//             }
//         }
//     }

//     return randomGraph;

// }



Graph::Graph(const std::string& networkFile){
    // parse the string and populate matrix 
    std::istringstream stream(networkFile);

    int order = 0;
    int size = 0;

    std::vector<std::pair<int, int>> entries;
    std::string line;

    while(std::getline(stream, line)){
        std::istringstream currLine(line);
        int source, target;
        if(currLine >> source >> target){
            entries.emplace_back(source, target);

            size++;
            order = std::max(order, std::max(source, target));
        }
    }

    vertexCount = order;
    edgeCount = size;

    adjacencyMatrix = Eigen::MatrixXi::Zero(order, order);
    for(const auto& [source, target]:entries){
        adjacencyMatrix(source-1, target-1) = 1;
    }
}

int Graph::order(){
    return vertexCount;
}
int Graph::size(){
    return edgeCount;
}

int Graph::get(int row, int col){
    return adjacencyMatrix(row, col);
}

std::vector<int> Graph::getAllSubgraphCounts(){
    return countSubgraph(adjacencyMatrix);
}

std::vector<int> Graph::getAllRandSubgraphCounts(){
    Eigen::MatrixXi randGraph = generateRandomGraph();
    return countSubgraph(randGraph);
}

std::vector<double> Graph::getAllRandSubgraphAvgCounts(std::size_t ensemble_size){
    // std::size_t ensemble_size = 20;
    std::vector<std::vector<int>> counts(ensemble_size);

    for (size_t i = 0; i < ensemble_size; i++){
        Eigen::MatrixXi randGraph = generateRandomGraph();
        counts[i] = countSubgraph(randGraph);
    }

    std::vector<double> meanCounts(degree_sets.size(), 0.0);

    // add up the counts
    for(const auto& randGraphs:counts){
        for(std::size_t subgraphCount = 0; subgraphCount < degree_sets.size(); subgraphCount++){
            meanCounts[subgraphCount] += randGraphs[subgraphCount];
        }
    }
    // divide by total number of random graphs to get the mean
    for(double& count:meanCounts){
        count /= counts.size();
    }

    return meanCounts;

}
