FILE=$2.plot
DEPS=*.txt
redo-ifchange $FILE $DEPS
gnuplot $FILE
