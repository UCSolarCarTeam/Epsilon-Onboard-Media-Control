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

QPushButton& SongPlayerUi::PlayButton()
{
    return *ui_->PlayButton;
}

QPushButton& SongPlayerUi::OpenButton()
{
    return *ui_->OpenButton;
}

QProgressBar& SongPlayerUi::ProgressBar()
{
    return *ui_->progressBar;
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
