#!/bin/bash

echo "compilando..."
make
echo "executando..."
./eqd.out
echo "fazendo o gráfico..."
cd plt
gnuplot phi.plt
echo "Fazendo o vídeo..."
ffmpeg -r 20 -i phi-%d.png -c:v libx264 -profile:v baseline -level 3.0 -pix_fmt yuv420p -y video.mp4

