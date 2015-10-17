#Ensures user is root

USER=`whoami`
if [ $USER = "root" ]
        then
        echo "Running as ROOT"
else
        echo "***********YOU ARE NOT ROOT************" 
        exit 0
fi

#Sets up Autoboot


echo "You are running on the pi, we will set up Auto Launch"
cd ..
sudo mkdir /home/Music
cp assets/*.ttf /usr/share/fonts
cp SongLibrary/*.mp3 /home/Music

FILECONTENTS=`grep -Eo "onboardmediacontrol" /etc/rc.local`
echo "filecontents = $FILECONTENTS"
if [ -z $FILECONTENTS ]
then
        echo "Setting up AutoLaunch"
        sed -i '$ d' /etc/rc.local
        sudo sh -c 'CAMERAPATH=`pwd`; echo "$CAMERAPATH/BackupCamera" >> /etc/rc.local'
        echo "exit 0" >> /etc/rc.local
else
        echo "Autolaunch already set up!"
fi

Sets up Fastboot
apt-get install systemd
FASTBOOT=`cat /boot/cmdline.txt`
SYSTEMSET=`echo $FASTBOOT | grep -o "systemd"`
if [ -z $SYSTEMSET ]
then
sudo sh -c 'FASTBOOT=`cat /boot/cmdline.txt`; echo -n "$FASTBOOT init=/bin/systemd" > /boot/cmdline.txt'
fi 
