#!/usr/bin/env bash

song=(1-06+Animal 1-11+Armageddon+It 1-14+Hysteria)

for i in "${song[@]}"; do
	wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/$i.mp3
done 

eyeD3 --write-images=$PWD *.mp3

mv OTHER.JPG ${song[0]}.jpg 

i=1
while [ $i -lt ${#song[@]} ]; do 
	mv OTHER$i.JPG ${song[$i]}.jpg
	let i=i+1
done





