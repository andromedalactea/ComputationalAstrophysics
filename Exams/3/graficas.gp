

lim = 4000
retardo = 0.000001
f = 0.01

set size square
set xrange [-5.6e-5:2*1e-3+5.6e-5]
set yrange [-5.6e-5:2*1e-3+5.6e-5]

do for [i=0:lim]{
  titulo = sprintf("paso = %.4d - tiempo = %.5f",i,i*5e-5)  
  set title titulo
  file = sprintf("state_%.4d",i)
    plot file every ::0::1599 u 2:3 w p ps 1 pt 7 lc rgb "blue" not,\
	 "" every ::1600::1760 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::1761::1919 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::1920::2080 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::2081::2239 u 2:3 w lp ps 1 pt 7 lc rgb "black" not
	 #"" every ::1920::1960 u 2:3 w lp ps 1 pt 7 lc rgb "black" not

  #pause retardo
}

do for [i=0:lim]{
  titulo = sprintf("paso = %.4d - tiempo = %.5f",i,i*5e-5)  
  set title titulo
  file = sprintf("state_%.4d",i)
    plot file every ::0::1599 u 2:3:($4*f):($5*f) w vectors lc rgb "blue" not,\
	"" every ::1600::1760 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::1761::1919 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::1920::2080 u 2:3 w lp ps 1 pt 7 lc rgb "black" not,\
	 "" every ::2081::2239 u 2:3 w lp ps 1 pt 7 lc rgb "black" not
	 #"" every ::1920::1960 u 2:3 w lp ps 1 pt 7 lc rgb "black" not

  pause retardo
}