#!/usr/bin/env bash

mkdir -p $HOME/Music/SongLibrary
cd $HOME/Music/SongLibrary

song=(1-06+Animal 1-11+Armageddon+It 1-14+Hysteria 1-01+Good+Times+Bad+Times 20+Rock+and+Roll+Is+King)

for i in "${song[@]}"; do
	if [ ! -f $i.mp3 ]; then
	wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/$i.mp3
	fi
done 

