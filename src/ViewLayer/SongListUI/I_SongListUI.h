#pragma once
#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class I_SongListUI : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongListUI() {}
    virtual QPushButton& listToPlayer() = 0;
    virtual QListWidget& listOfSongs() = 0;

};
