#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"

SongPlayerUi::SongPlayerUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SongPlayerUi)
{
    ui->setupUi(this);
}

SongPlayerUi::~SongPlayerUi()
{
    delete ui;
}

QPushButton& SongPlayerUi::PlayButton()
{
    return *ui->PlayButton;
}

QPushButton& ttsongplayerui::OpenButton()
{
    return *ui->OpenButton;
}

QSlider& SongPlayerUi::PositionSlider()
{
    return *ui->PositionSlider;
}
