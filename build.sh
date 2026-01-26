#!/bin/bash

echo "==============================="
echo " Build Project"
echo "==============================="

mkdir -p build
cd build || exit 1

echo "Configurando com CMake..."
cmake ..

if [ $? -ne 0 ]; then
    echo "ERRO no cmake"
    exit 1
fi

echo "Compilando..."
make

if [ $? -ne 0 ]; then
    echo "ERRO na compilacao"
    exit 1
fi

echo "==============================="
echo "Executando teste"
echo "==============================="

./main