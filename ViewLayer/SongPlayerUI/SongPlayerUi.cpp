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

QSlider& SongPlayerUi::PositionSlider()
{
    return *ui->PositionSlider;
}

QLabel& SongPlayerUi::infoLabel()
{
    return *ui->infoLabel;
}
