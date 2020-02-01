#pragma once

#include <QWidget>

class QSlider;
class QPushButton;

class I_SongControlUi : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongControlUi() {}

    virtual QPushButton& playButton() = 0;
    virtual QPushButton& nextSongButton() = 0;
    virtual QPushButton& prevSongButton() = 0;
    virtual QPushButton& shuffleButton() = 0;
    virtual QPushButton& loopButton() = 0;
    virtual QSlider& volumeControlSlider() = 0;
};
