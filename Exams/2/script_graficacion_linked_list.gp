reset
set term pngcairo size 900,600    
set output 'grafico.png'          

# Establecer rangos y etiquetas de ejes
set xrange [0:100]
set yrange [0:100]
set xlabel 'Eje X' offset 0,0.1
set ylabel 'Eje Y' offset 2,0

# Título del gráfico
set title "Vecinos de un punto dado con el algoritmo Linked List"

# Establecer el grid
set xtics 16.6666
set ytics 16.6666
set format x "%0.0f"  # Formato para redondear a entero más cercano 
set format y "%0.0f"  
set grid xtics ytics lc rgb 'purple' lt 1 lw 2

# Configurar la leyenda para que esté fuera del área de graficación
set key outside right top vertical Right noreverse enhanced autotitles box lt black linewidth 1.0

plot 'posiciones.dat' using 2:3 with points pt 7 lc rgb 'blue' title 'Todos los puntos', \
     'vecinos.dat' using 2:3 with points pt 7 lc rgb 'red' title 'Vecinos', \
     'posiciones.dat' using ($1 == 10 ? $2 : 1/0):($1 == 10 ? $3 : 1/0) with points pt 7 lc rgb 'green' title 'Punto de interés'
reset
# IMPORTANTE: Para cambiar el punto de interés, se debe modificar el valor de $1 == 10 (ambos) por el id del punto deseado.
# y para el cual se hizo la ejecución del programa.
