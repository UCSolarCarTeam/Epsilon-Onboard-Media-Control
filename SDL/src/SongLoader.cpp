#include "SongLoader.h"
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

SongLoader::SongLoader()
{
	
}

int SongLoader::readSongNames(std::string container[])
{
	int count = 0;
	DIR *dir;
	struct dirent *ent;
	// Change string to directory with songs in it
	if ((dir = opendir("/home/mario/Documents/solarCarGit/onboardmediacontrol/SDL/assets/")) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
		{
			if (strstr(ent->d_name, ".ogg") != NULL)
			{
				container[count] = ent->d_name;
				count++;
			}
		}
	}
	printf("%d\n", count);
	return count;
}
