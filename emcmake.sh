emcc graph.cpp bindings.cpp -o app/src/graph.js \
    -std=c++17 \
    -I ../Eigen \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    --bind