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

if [ $HOME = "/home/pi" ]
then
echo "You are running on the pi, we will set up Auto Launch"
cd ..
FILECONTENTS=`grep -Eo "onboardmediacontrol" /etc/xdg/lxsession/LXDE-pi/autostart`
echo "filecontents = $FILECONTENTS"
        if [ -z $FILECONTENTS ]
        then
                echo "Setting up AutoLaunch"
                sudo sh -c 'CAMERAPATH=`pwd`; echo "@$CAMERAPATH/main" >> /etc/xdg/lxsession/LXDE-pi/autostart'
        else
                echo "Autolaunch already set up!"
        fi
fi

#Sets up Fastboot
apt-get install systemd
FASTBOOT=`cat /boot/cmdline.txt`
SYSTEMSET=`echo $FASTBOOT | grep -o "systemd"`
if [ -z $SYSTEMSET ]
then
sudo sh -c 'FASTBOOT=`cat /boot/cmdline.txt`; echo -n "$FASTBOOT init=/bin/systemd" > /boot/cmdline.txt'
fi 
