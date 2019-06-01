#pragma once
#include <QPushButton>

class listItem: public QPushButton
{
public:
    listItem();
    ~listItem();
    void setPath(QString path);
    void setName(QString name);
    void setArtist(QString artist);
    QString getName();
    QString getPath();
    QString getArtist();
private:
    QString name;
    QString artist;
    QString filepath;
};

