reset

# set xyplane at -100000.0
set xrange [0:1]
set yrange [-1:1]
# set zrange [-1000:45000000000.0]

set dgrid 100,100,8
set contour base
set isosamples 100,100

set cntrparam bspline points 2 levels auto
# set cntrparam bspline points 2 levels discrete 5*10**9,10*10**9,20*10**9,30*10**9,40*10**9,45*10**9

set pm3d 
set palette defined (0 "#8ecae6",1 "#b8f2e6",2"#118ab2",3 "#2b9348",4 "#90be6d", 5 "#f9c74f",6 "#f8961e",7 "#ff6b6b",8 "#e01e37",9 "#7251b5")

set linetype 8 lc rgb "#8ecae6" lw 0.2 ps 0.1
set linetype 7 lc rgb "#b8f2e6" lw 0.2 ps 0.1
set linetype 6 lc rgb "#118ab2" lw 0.2 ps 0.1
# set linetype 5 lc rgb "#2b9348" lw 0.2 ps 0.1
set linetype 5 lc rgb "#90be6d" lw 0.2 ps 0.1
set linetype 4 lc rgb "#f9c74f" lw 0.2 ps 0.1
set linetype 3 lc rgb "#f8961e" lw 0.2 ps 0.1
set linetype 2 lc rgb "#ff6b6b" lw 0.2 ps 0.1

set hidden3d

set style increment user

# set view 60, 330, 1, 1

set view 60, 120, 1, 1

set terminal png size 2048,1536

set output sprintf("./test.png")
splot "./test" u 2:1:3 ps 0.2 pt 14  lc rgb '#778da9' t "points" 

set output





