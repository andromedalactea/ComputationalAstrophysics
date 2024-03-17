reset
set terminal pngcairo
set output "grafica_funcion_bessel.png"

set xlabel "x"
set ylabel "J_{/Symbol a}(x)"
set title "Funciones de Bessel J_{/Symbol a}(x)"

plot "funcion_de_bessel_orden_0.dat" u 1:2 w l lw 2 lc rgb "red" title "J_{0}(x)", \
     "funcion_de_bessel_orden_1.dat" u 1:2 w l lw 2 lc rgb "blue" title "J_{1}(x)", \
     "funcion_de_bessel_orden_2.dat" u 1:2 w l lw 2 lc rgb "black" title "J_{2}(x)"

reset
