#!/usr/bin/env bash

song=(1-06+Animal 1-11+Armageddon+It 1-14+Hysteria 01DangerZone 01TakeOnMe 02PumpedUpKicks)
albumlist=()
#for i in "${song[@]}"; do
#	wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/$i.mp3
#done 

#album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
#album=${album// /_}
#album=${album//[[:blank:]]/}
#album=${album::-4}
#albumlist+=($album)

album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
album=${album//[[:blank:]]/}
album=${album::-4}
albumlist+=($album)

i=1
while [ $i -lt ${#song[@]} ]; do 
	album="$(eyeD3 ${song[$i]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
	album=${album//[[:blank:]]/}
	album=${album::-4}
	albumcheck=false
	j=0
	while [ $j -lt ${#albumlist[@]} ]; do 
		if [ "$album" == "${albumlist[$j]}" ] ; then
			albumcheck=true
		fi
		let j=j+1
	done
	
	if [ "$albumcheck" = false ] ; then
		albumlist+=($album)
	fi

	let i=i+1
done

echo list contains
printf '%s\n' "${albumlist[@]}"

#eyeD3 --write-images=$PWD *.mp3

#album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
#album=${album// /_}
#album=${album//[[:blank:]]/}
#album=${album::-4}
#album="../Covers/$album.jpg"
#echo album file is: $album

#mv OTHER.JPG $album 

#i=1
#while [ $i -lt ${#song[@]} ]; do 
#	mv OTHER$i.JPG ${song[$i]}.jpg
#	let i=i+1
#done

#mogrify -format jpg *.png





