To compile:
g++ -std=c++11 Main.cpp SongLoader.cpp SongPlayer.cpp -o music -lmpg123 -pthread -lao

Songs must be located in the "/home/USER/Music" directory. 
To change the directory edit the songloader.cpp file.

After terminating the program a new console must be opened to run it again.