# Epsilon Onboard Media Player

This program is the onboard media control for the University of Calgary's Solar Car Schulich Elysia. This program is a music player which runs on the car's secondary Raspberry Pi on the center display.

## Playing Music

The media player will search for songs in the `/home/{user}/Music/SongLibrary` folder. Currently the media player will only decode files of the `.mp3`format. 

## Class Diagram

![Class Diagram](pictures/ClassDiagram.png)

## Download Songs
If you only need a small number of songs, you can run the `./DownloadSongs.sh` in the terminal to download a pre-selected selection of songs.

To download all the songs hosted on the AWS bucket:

**1. Install AWS CLI**

In order to download all song, you need to install AWS CLI by running `sudo apt-get install awscli`

**2. Obtain Access Keys**

To directly download from the aws bucket, you will need to obtain the Access Key ID and the Secret Access Key.

**3. Configure the AWS CLI**

Run `aws configure` in the terminal to configure the profile for AWS.

Input the access keys obtained. 

The region name is `us-west-2`.

**4. Download all songs**

You can now run `./DownloadSongs.sh -a` to download all songs hosted on the AWS bucket.
