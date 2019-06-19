#pragma once
#include <QPushButton>

class listItem: public QPushButton
{
public:
    listItem(QString artist, QString name, QString path);
    ~listItem();
    void setPath(QString path);
    void setName(QString name);
    void setArtist(QString artist);
    void setButtonText();
    QString getName();
    QString getPath();
    QString getArtist();
private:
    QString artist_;
    QString name_;
    QString filepath_;
};

