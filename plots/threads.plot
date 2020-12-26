set term svg

set title 'How much time it takes to compute'
set xlabel 'Thread number'
set ylabel 'Time (ms)'

plot 'threads.txt' with linespoints title 'n=2800' lw 4
