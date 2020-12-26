FILE=$2.cpp
ARGS="-DTESTING -Wall -std=c++11 -fopenmp -O2"

redo-ifchange $FILE
c++ $ARGS $FILE -o $3
