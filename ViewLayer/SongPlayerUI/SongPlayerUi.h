#pragma once

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QSlider>

#include "I_SongPlayerUi.h"

namespace Ui
{
    class SongPlayerUi;
}

class SongPlayerUi : public I_SongPlayerUi
{
    Q_OBJECT

public:
    explicit SongPlayerUi();
    ~SongPlayerUi();
    QLabel& labelPic();
    QLabel& infoLabel();
    QPushButton& playButton();
    QProgressBar& progressBar();
    QPushButton& nextSong();
    QPushButton& prevSong();
    QPushButton& ShuffleButton();
    QPushButton& LoopButton();
    QVBoxLayout& progressBarContainer();
    QSlider& volumeControl();

private:
    Ui::SongPlayerUi* ui_;
};
