#pragma once

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>

#include "I_SongPlayerUi.h"

namespace Ui {
class SongPlayerUi;
}

class SongPlayerUi : public I_SongPlayerUi
{
    Q_OBJECT

public:
    explicit SongPlayerUi();
    ~SongPlayerUi();
    QLabel& infoLabel();
    QPushButton& PlayButton();
    QPushButton& OpenButton();
    QProgressBar& ProgressBar();
    QPushButton& NextSong();
    QPushButton& PrevSong();


private:
    Ui::SongPlayerUi *ui_;
};
