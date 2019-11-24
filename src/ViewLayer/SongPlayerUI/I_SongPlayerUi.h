#pragma once

#include <QWidget>

class QLabel;
class QPushButton;
class QSlider;
class QVBoxLayout;

class I_SongPlayerUi : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongPlayerUi() {}

    virtual QLabel& infoLabel() = 0;
    virtual QPushButton& playButton() = 0;
    virtual QPushButton& nextSong() = 0;
    virtual QPushButton& prevSong() = 0;
    virtual QPushButton& shuffleButton() = 0;
    virtual QPushButton& loopButton() = 0;
    virtual QSlider& volumeControl() = 0;
    virtual QVBoxLayout& progressBarContainer() = 0;
    virtual QLabel& labelPic() = 0;
};
