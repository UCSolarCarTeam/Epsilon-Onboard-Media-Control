#!/usr/bin/env bash

song=(1-06+Animal 1-11+Armageddon+It 1-14+Hysteria 01-Take-On-Me)
uniquealbumlist=()
albumlist=()

album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
album=${album//[[:blank:]]/}
album=${album::-4}
albumlist+=($album)
uniquealbumlist+=($album)
album="../Covers/$album.jpg"
eyeD3 --write-images=$PWD ${song[0]}.mp3
mv OTHER.JPG $album


i=1
firstfilecheck=true
while [ $i -lt ${#song[@]} ]; do 
	album="$(eyeD3 ${song[$i]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
	album=${album//[[:blank:]]/}
	album=${album::-4}
	albumlist+=($album)
	albumcheck=false
	j=0
	while [ $j -lt ${#uniquealbumlist[@]} ]; do 
		if [ "$album" == "${uniquealbumlist[$j]}" ] ; then
			albumcheck=true
		fi
		let j=j+1
	done
	
	if [ "$albumcheck" = false ] ; then
		uniquealbumlist+=($album)
		echo song jpg: ${song[$i]}
		eyeD3 --write-images=$PWD ${song[$i]}.mp3
		album="../Covers/$album.jpg"
		mv OTHER.JPG $album
		let k=k+1
	fi
	let i=i+1
done

echo uniquealbumlist contains
printf '%s\n' "${uniquealbumlist[@]}"

echo albumlist contains
printf '%s\n' "${albumlist[@]}"







