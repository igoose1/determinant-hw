FILE=$2.cpp
ARGS="-DTESTING -Wall -std=c++17 -fopenmp -pthread -O2"

redo-ifchange $FILE
g++ $ARGS $FILE -o $3
