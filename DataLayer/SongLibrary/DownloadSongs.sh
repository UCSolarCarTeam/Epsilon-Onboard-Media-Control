#!/usr/bin/env bash

wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/1-06+Animal.mp3
wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/1-11+Armageddon+It.mp3
wget https://s3-us-west-2.amazonaws.com/ucsolarteam.onboardmedia.songs/1-14+Hysteria.mp3
sudo apt-get install eyeD3
eyeD3 --write-images=$PWD 1-14+Hysteria.mp3 1-06+Animal.mp3 1-14+Hysteria.mp3 01-Take-On-Me.mp3
mv OTHER.JPG 1-06+Animal.jpg
mv OTHER1.JPG 1-11+Armageddon+It.jpg
mv OTHER2.JPG 1-14+Hysteria.jpg
mv OTHER3.JPG 01-Take-On-Me.jpg


