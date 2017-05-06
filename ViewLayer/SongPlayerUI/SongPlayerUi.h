#pragma once

#include <QWidget>
#include <QPushButton>
#include <QSlider>
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
     QSlider& PositionSlider();


private:
    Ui::SongPlayerUi *ui;
};
