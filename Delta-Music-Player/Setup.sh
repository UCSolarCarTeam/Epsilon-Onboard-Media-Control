USER=`whoami`
if [ $USER = "root" ]
    then
    echo "Running as ROOT"
else
    echo "***********YOU ARE NOT ROOT************"
    exit 0
fi

apt-get update --yes
apt-get install build-essential --yes

git clone https://github.com/gypified/libmpg123.git
cd libmpg123
./configure
make
sudo make install
cd ..

apt-get install libcv-dev --yes
apt-get install libopencv-dev --yes
apt-get install libao-dev --yes
apt-get install libasound2-dev --yes
apt-get install libpulse-dev --yes

apt-get install libdbus-1-dev --yes
apt-get install libudev-dev --yes