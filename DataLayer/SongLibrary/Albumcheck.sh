#!/usr/bin/env bash

song=(1-06+Animal 1-11+Armageddon+It 1-14+Hysteria)

for i in "${song[@]}"; do
	wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/$i.mp3
done 

eyeD3 --write-images=$PWD *.mp3

album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
album=${album// /_}
album=${album//[[:blank:]]/}
album="$album.jpg"
echo album file is: $album

mv OTHER.JPG $album 

i=1
while [ $i -lt ${#song[@]} ]; do 
	mv OTHER$i.JPG ${song[$i]}.jpg
	let i=i+1
done

#mogrify -format jpg *.png





