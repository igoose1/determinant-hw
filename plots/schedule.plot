set term svg

set title 'Different schedule types'
set xlabel 'Chunk Size'
set ylabel 'Time (ms)'

set logscale x

plot 'static.txt' with linespoints title 'static' lw 4, \
	'dynamic.txt' with linespoints title 'dynamic' lw 4, \
	'guided.txt' with linespoints title 'guided' lw 4
