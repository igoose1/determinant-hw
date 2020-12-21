FILE=$2.cpp
ARGS="-Wall -Werror -std=c++17 -O2"

redo-ifchange $FILE
g++ $ARGS $FILE -o $3
