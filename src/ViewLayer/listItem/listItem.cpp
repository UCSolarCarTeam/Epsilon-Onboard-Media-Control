#include "listItem.h"

listItem::listItem()
{

}

listItem::~listItem()
{

}

void listItem:: setArtist(QString artist)
{
    this->artist = artist;
}

void listItem:: setName(QString name)
{
    this->name = name;
}

void listItem:: setPath(QString path)
{
    this->filepath = path;
}

QString listItem:: getArtist()
{
    return this->artist;
}

QString listItem:: getName()
{
    return this->name;
}

QString listItem:: getPath()
{
    return this->filepath;
}
