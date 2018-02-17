#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"

SongPlayerUi::SongPlayerUi():
    ui_(new Ui::SongPlayerUi)
{
    ui_->setupUi(this);
    show();
}

SongPlayerUi::~SongPlayerUi()
{
    delete ui_;
}

QPushButton& SongPlayerUi::playButton()
{
    return *ui_->playButton;
}

QLabel& SongPlayerUi::infoLabel()
{
    return *ui_->infoLabel;
}

QPushButton& SongPlayerUi::nextSong()
{
    return *ui_->nextSong;
}

QPushButton& SongPlayerUi::prevSong()
{
    return *ui_->prevSong;
}

QSlider& SongPlayerUi::volumeControl()
{
    return *ui_->volumeControl;
}

QVBoxLayout& SongPlayerUi::progressBarContainer()
{
    return *ui_->progressBarContainer;
}

QLabel& SongPlayerUi::labelPic()
{
    return *ui_->labelPic;
}
