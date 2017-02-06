#!/bin/bash
x=1;
PWD="./movie"
for i in *jpg; do
	counter=$(printf %03d $x);
	ln -s "$i" "$PWD"  "$counter".jpg;
	x=$(($x+1));
done
avconv -framerate 30 -i "$PWD"/frame%d.jpg -c:v libx264 -r 30 -pix_fmt yuv420p out_video.mp4