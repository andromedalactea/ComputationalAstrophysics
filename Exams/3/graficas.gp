# Number of steps for the simulation
lim = 4000
# Delay between frames in seconds
retardo = 0.000001
# Scaling factor for vector lengths
f = 0.01

# Set plot size to square for equal scaling on both axes
set size square
# Set the range for the x-axis
set xrange [-5.6e-5:2*1e-3+5.6e-5]
# Set the range for the y-axis
set yrange [-5.6e-5:2*1e-3+5.6e-5]

# First loop for plotting points only
do for [i=0:lim] {
  # Generate the title for each frame
  titulo = sprintf("paso = %.4d - tiempo = %.5f", i, i*5e-5)
  set title titulo
  # Generate the file name for each frame
  file = sprintf("state_%.4d", i)
  
  # Plot the data
  plot file every ::0::1599 u 2:3 w p ps 1 pt 7 lc rgb "blue" notitle, \
       "" every ::1600::1760 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::1761::1919 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::1920::2080 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::2081::2239 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle

  # Uncomment the line below to add a delay between frames
  # pause retardo
}

# Second loop for plotting vectors
do for [i=0:lim] {
  # Generate the title for each frame
  titulo = sprintf("paso = %.4d - tiempo = %.5f", i, i*5e-5)
  set title titulo
  # Generate the file name for each frame
  file = sprintf("state_%.4d", i)
  
  # Plot the data with vectors
  plot file every ::0::1599 u 2:3:($4*f):($5*f) w vectors lc rgb "blue" notitle, \
       "" every ::1600::1760 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::1761::1919 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::1920::2080 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle, \
       "" every ::2081::2239 u 2:3 w lp ps 1 pt 7 lc rgb "black" notitle
  
  # Uncomment the line below to add a delay between frames
  # pause retardo
}