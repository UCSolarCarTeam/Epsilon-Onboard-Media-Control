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

