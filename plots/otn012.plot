set term svg

set title 'With and without OpenMP'
set xlabel 'Size of matrix'
set ylabel 'Time (ms)'

plot 'otn0.txt' with linespoints title 'without OpenMP' lw 3, \
	'otn1.txt' with linespoints title 'with OpenMP (1 thread)' lw 3, \
	'otn2.txt' with linespoints title 'with OpenMP (2 thread)' lw 3
