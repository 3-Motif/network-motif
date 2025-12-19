emcc graph.cpp bindings.cpp -o app/src/graph.js \
    -std=c++17 \
    -I ../Eigen \
    -fno-exceptions \
    -s MODULARIZE=1 \
    -s EXPORT_ES6=1 \
    -s DISABLE_EXCEPTION_CATCHING=1 \
    -s NO_FILESYSTEM=1 \
    -s EXPORTED_RUNTIME_METHODS=[] \
    --bind

 