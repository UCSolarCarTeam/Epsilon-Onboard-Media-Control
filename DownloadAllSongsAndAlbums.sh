#!/usr/bin/env bash

mkdir -p $HOME/Music/SongLibrary
mkdir -p $HOME/Pictures/Covers
cd $HOME/Music/SongLibrary

export AWS_ACCESS_KEY_ID=AKIAJ4M34KXJBKZK4L5A
export AWS_SECRET_ACCESS_KEY=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
export AWS_DEFAULT_REGION=us-west-2
export AWS_DEFAULT_OUTPUT=text

readarray -t song <<< "$(aws s3 ls s3://ucsolarteam.onboardmedia.songs | awk '{for (i=4; i<NF; i++) printf $i " "; print $NF}' | sed s/\ /\+/g | rev | cut -c 5- | rev )"
albumlist=()

for i in "${song[@]}"; do
	wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/$i.mp3
done 

album="$(eyeD3 ${song[0]}.mp3 | grep -o -P '(?<=: ).*(?=year)')"
album=${album//[[:blank:]]/}
album=${album::-4}
albumlist+=($album)
uniquealbumlist+=($album)
album="$HOME/Pictures/Covers/$album.jpg"
eyeD3 --write-images=$PWD ${song[0]}.mp3
mv OTHER.JPG $album


i=1
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
		album="$HOME/Pictures/Covers/$album.jpg"
		mv OTHER.JPG $album
		let k=k+1
	fi
	let i=i+1
done

mogrify -format jpg *.png
