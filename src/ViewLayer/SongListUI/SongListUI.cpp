#include "SongListUI.h"
#include "ui_SongListUI.h"
#include <QStyle>
#include <QDesktopWidget>
#include <QListWidget>

SongListUI::SongListUI() :
    ui_(new Ui::SongListUI)
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

SongListUI::~SongListUI()
{
    delete ui_;
}

QPushButton& SongListUI::listToPlayer()
{
    return *ui_->listToPlayer;
}

QListWidget& SongListUI::listOfSongs()
{
    return *ui_->listOfSongs;
}
