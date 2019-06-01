#pragma once
#include <QPushButton>
#include <QScrollArea>
#include <QWidget>
#include "I_SongListUI.h"

namespace Ui {
class SongListUI;
}

class SongListUI : public I_SongListUI
{
    Q_OBJECT

public:
    explicit SongListUI();
    ~SongListUI();
    QPushButton& listToPlayer();
    QScrollArea& listScroll();

private:
    Ui::SongListUI *ui_;
};


