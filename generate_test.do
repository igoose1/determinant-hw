FILE=$2.cpp
ARGS="-Wall -std=c++98 -O2"

redo-ifchange $FILE
g++ $ARGS $FILE -o $3
