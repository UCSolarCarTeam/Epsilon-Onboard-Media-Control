#include "listItem.h"

listItem::listItem(QString artist, QString name, QString path)
    : artist_(artist),
      name_(name),
      filepath_(path)
{
    listButton_ = new QPushButton();
    setButtonText();
    listButton_->setStyleSheet("color:white;");
    connect(listButton_, SIGNAL(clicked()), this, SLOT(handleButtonPressed()));
}

listItem::~listItem()
{

}

void listItem:: setButtonText()
{
    QString temp = getName() + " - " + getArtist();
    listButton_->setText(temp);
}

void listItem:: setArtist(QString artist)
{
    this->artist_ = artist;
}

void listItem:: setName(QString name)
{
    this->name_ = name;
}

void listItem:: setPath(QString path)
{
    this->filepath_ = path;
}

QString listItem:: getArtist()
{
    return this->artist_;
}

QString listItem:: getName()
{
    return this->name_;
}

QString listItem:: getPath()
{
    return this->filepath_;
}

QPushButton* listItem:: getButton()
{
    return this->listButton_;
}

void listItem:: handleButtonPressed()
{
    emit songChanged(filepath_);
}


