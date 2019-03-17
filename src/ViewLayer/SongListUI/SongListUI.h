#pragma once
#include <QPushButton>
#include <QListWidget>
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
    QListWidget& listOfSongs();

private:
    Ui::SongListUI *ui_;
};


