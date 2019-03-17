#pragma once

#include <QWidget>
#include <QPushButton>
#include <QProgressBar>
#include <QLabel>
#include <QSlider>

#include "I_SongPlayerUi.h"
#include "../FontLoader/FontLoader.h"

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
    QPushButton& shuffleButton();
    QPushButton& loopButton();
    QProgressBar& progressBar();
    QPushButton& nextSong();
    QPushButton& prevSong();
    QVBoxLayout& progressBarContainer();
    QPushButton& playerToList();
    QSlider& volumeControl();

private:
    Ui::SongPlayerUi* ui_;
    QScopedPointer<FontLoader> fontLoader_;
};
