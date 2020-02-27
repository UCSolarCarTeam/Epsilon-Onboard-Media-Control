#include <QStyle>
#include <QDesktopWidget>

#include "SongPlayerUi.h"
#include "ui_SongPlayerUi.h"
#include "FontLoader.h"

SongPlayerUi::SongPlayerUi():
    ui_(new Ui::SongPlayerUi)
    , fontLoader_(new FontLoader())
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
    setFixedSize(size());

    //Font loading
    QApplication::setFont(fontLoader_->loadFont(Font::BURLINGAME));

    show();
}

SongPlayerUi::~SongPlayerUi()
{
}

QPushButton& SongPlayerUi::playButton()
{
    return *ui_->playButton;
}

QLabel& SongPlayerUi::infoLabel()
{
    return *ui_->infoLabel;
}

QPushButton& SongPlayerUi::nextSongButton()
{
    return *ui_->nextSong;
}

QPushButton& SongPlayerUi::prevSongButton()
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

QSlider& SongPlayerUi::volumeControlSlider()
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
