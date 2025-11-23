source emsdk/emsdk_env.sh

emcc src/main.cpp src/fs.cpp \
    -o main.js \
    -std=c++17 \
    -s WASM=1 \
    -s MODULARIZE=1 \
    -s EXPORT_NAME="Module" \
    -s EXPORTED_RUNTIME_METHODS='["ccall", "cwrap"]' \
    -s ALLOW_MEMORY_GROWTH=1 \
    -lembind \
    -O2