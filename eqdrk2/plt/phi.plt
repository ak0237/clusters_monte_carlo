set terminal pngcairo size 720,720

set xrange [0.5:100.5]
set yrange [0.5:100.5]
set size ratio -1 
set palette rgb 21, 22, 23
set cbrange[0:1]
unset key

i = 0
while(i<=499){
	set output sprintf("phi-%d.png", i)
	plot sprintf("../dat/phi-%d.dat", i) u ($1+1):($2+1):($3) matrix w image
	unset output
	i = i + 1
}
