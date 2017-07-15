#pragma once

#include <QPushButton>
#include <QLabel>
#include <QProgressBar>

class I_SongPlayerUi : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongPlayerUi() {}

    virtual QLabel& infoLabel() = 0;
    virtual QProgressBar& ProgressBar() = 0;
    virtual QPushButton& PlayButton() = 0;
    virtual QPushButton& OpenButton() = 0;
    virtual QPushButton& NextSong() = 0;
    virtual QPushButton& PrevSong() = 0;
};