#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"
#include <QStyle>
#include <QDesktopWidget>

SongPlayerUi::SongPlayerUi():
    ui_(new Ui::SongPlayerUi)
{
    ui_->setupUi(this);
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignBottom,
            size(),
            qApp->desktop()->availableGeometry()
        )
    );
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

QPushButton& SongPlayerUi::shuffleButton()
{
    return *ui_->shuffleButton;
}

QPushButton& SongPlayerUi::loopButton()
{
    return *ui_->loopButton;
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

QPushButton& SongPlayerUi::playerToList()
{
    return *ui_->playerToList;
}
