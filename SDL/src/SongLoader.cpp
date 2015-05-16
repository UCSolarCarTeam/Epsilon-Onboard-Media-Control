#include "SongLoader.h"

int main()
{

SongLoader test;
test.readSongNames();
test.shuffleSongNames();
std::cout<<test.nextSong()<<std::endl;
std::cout<<test.nextSong()<<std::endl;
std::cout<<test.nextSong()<<std::endl;

return 0;

}

SongLoader::SongLoader()
{
	counter=0;
	song=0;
	
}

int SongLoader::readSongNames()
{
	
	DIR *dir;
	struct dirent *ent;
	// Change string to directory with songs in it
	if ((dir = opendir("ExampleMusic")) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			
			{
			container[counter]=ent->d_name;
			counter++;
			
			}
		}
	}

	return 0;
}

int SongLoader::shuffleSongNames()
{

	std::random_device rd;
    std::mt19937 g(rd());
	std::shuffle ( container, container+counter, g );
	song=0;
	return 0;
}


std::string SongLoader::nextSong()
{
CurrentSong=container[song];
song++;
if(song>=counter)
shuffleSongNames();

return CurrentSong;
}













