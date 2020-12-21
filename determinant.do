FILE=$2.cpp
ARGS="-DTESTING -Wall -Werror -std=c++17 -fopenmp -O2"

redo-ifchange $FILE
g++ $ARGS $FILE -o $3
