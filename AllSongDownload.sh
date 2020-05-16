#!/usr/bin/env bash

mkdir -p $HOME/Music/SongLibrary
cd $HOME/Music/SongLibrary

aws configure

aws s3 sync s3://ucsolarteam.onboardmedia.songs .
