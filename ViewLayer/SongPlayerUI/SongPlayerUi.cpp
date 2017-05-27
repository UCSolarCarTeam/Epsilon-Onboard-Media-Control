#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"

SongPlayerUi::SongPlayerUi():
    ui(new Ui::SongPlayerUi)
{
    ui->setupUi(this);
    show();
}

SongPlayerUi::~SongPlayerUi()
{
    delete ui;
}

QPushButton& SongPlayerUi::PlayButton()
{
    return *ui->PlayButton;
}

QPushButton& SongPlayerUi::OpenButton()
{
    return *ui->OpenButton;
}

QProgressBar& SongPlayerUi::ProgressBar()
{
    return *ui->progressBar;
}

QLabel& SongPlayerUi::infoLabel()
{
    return *ui->infoLabel;
}

QPushButton& SongPlayerUi::NextSong()
{
    return *ui->nextSong;
}

QPushButton& SongPlayerUi::PrevSong()
{
    return *ui->prevSong;
}
