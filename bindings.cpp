#include <emscripten/bind.h>
#include "graph.h"

using namespace emscripten;

EMSCRIPTEN_BINDINGS(graph_module) {
    class_<Graph>("Graph")
        .constructor<const std::string&>()
        .function("get", &Graph::get)
        .function("order", &Graph::order)
        .function("size", &Graph::size)
        .function("getAllSubgraphCounts", &Graph::getAllSubgraphCounts)
        .function("getAllRandSubgraphCounts", &Graph::getAllRandSubgraphCounts)
        .function("getAllRandSubgraphAvgCounts", &Graph::getAllRandSubgraphAvgCounts);


    register_vector<int>("VectorInt");
    register_vector<double>("VectorDouble");
    // register_vector<std::vector<int>>("VectorVectorInt");
}