#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"

SongPlayerUi::SongPlayerUi():
    ui_(new Ui::SongPlayerUi)
{
    ui_->setupUi(this);
    show();
    ui_->nextSong->setIcon(QIcon("/home/ben/Documents/SolarCar/Epsilon-Onboard-Media_Control/Epsilon-Onboard-Media-Control/DataLayer/Icons/Next.png"));
    ui_->prevSong->setIcon(QIcon("/home/ben/Documents/SolarCar/Epsilon-Onboard-Media_Control/Epsilon-Onboard-Media-Control/DataLayer/Icons/Previous.png"));
    ui_->PlayButton->setIcon(QIcon("/home/ben/Documents/SolarCar/Epsilon-Onboard-Media_Control/Epsilon-Onboard-Media-Control/DataLayer/Icons/Play.png"));
    ui_->nextSong->setIconSize(QSize(65,65));
    ui_->prevSong->setIconSize(QSize(65,65));
    ui_->PlayButton->setIconSize(QSize(65,65))

}

SongPlayerUi::~SongPlayerUi()
{
    delete ui_;
}

QPushButton& SongPlayerUi::PlayButton()
{
    return *ui_->PlayButton;
}

QPushButton& SongPlayerUi::OpenButton()
{
    return *ui_->OpenButton;
}

QLabel& SongPlayerUi::infoLabel()
{
    return *ui_->infoLabel;
}

QPushButton& SongPlayerUi::NextSong()
{
    return *ui_->nextSong;
}

QPushButton& SongPlayerUi::PrevSong()
{
    return *ui_->prevSong;
}

QVBoxLayout& SongPlayerUi::progressBarContainer()
{
    return *ui_->progressBarContainer;
}
