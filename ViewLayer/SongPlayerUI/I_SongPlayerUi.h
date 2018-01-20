#pragma once

#include <QPushButton>
#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QSlider>

class I_SongPlayerUi : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongPlayerUi() {}

    virtual QLabel& infoLabel() = 0;
    virtual QPushButton& PlayButton() = 0;
    virtual QPushButton& NextSong() = 0;
    virtual QPushButton& PrevSong() = 0;
    virtual QPushButton& ShuffleButton() = 0;
    virtual QPushButton& LoopButton() = 0;
    virtual QSlider& volumeControl() = 0;
    virtual QVBoxLayout& progressBarContainer() = 0;
};
