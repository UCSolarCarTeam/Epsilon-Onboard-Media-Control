#pragma once

#include <QWidget>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

namespace Ui {
class SongPlayerUi;
}

class SongPlayerUi : public QWidget
{
    Q_OBJECT

public:
    explicit SongPlayerUi(QWidget *parent = 0);
    ~SongPlayerUi();
     QPushButton& PlayButton();
     QPushButton& OpenButton();
     QSlider& PositionSlider();
     QLabel& infoLabel();

private:
    Ui::SongPlayerUi *ui;
};
