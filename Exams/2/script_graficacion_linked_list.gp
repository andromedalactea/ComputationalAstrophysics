reset
set term pngcairo size 800,600    
set output 'grafico.png'          

# Establecer rangos y etiquetas de ejes
set xrange [0:100]
set yrange [0:100]
set xlabel 'Eje X'
set ylabel 'Eje Y'

# Establecer el grid
set grid xtics ytics mxtics mytics lc rgb 'gray' lw 1
set mxtics 6
set mytics 6

plot 'posiciones.dat' using 2:3 with points pt 7 lc rgb 'blue' title 'Todos los puntos', \
     'vecinos.dat' using 2:3 with points pt 7 lc rgb 'red' title 'Vecinos', \
     'posiciones.dat' using ($1 == 10 ? $2 : 1/0):($1 == 10 ? $3 : 1/0) with points pt 7 lc rgb 'green' title 'Punto de interés'

