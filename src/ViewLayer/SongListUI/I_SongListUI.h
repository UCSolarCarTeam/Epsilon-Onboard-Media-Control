#pragma once
#include <QWidget>
#include <QPushButton>
#include <QScrollArea>

class I_SongListUI : public QWidget
{
    Q_OBJECT
public:
    virtual ~I_SongListUI() {}
    virtual QPushButton& listToPlayer() = 0;
    virtual QScrollArea& listScroll() = 0;
    virtual QWidget& scrollAreaWidgetContents() = 0;
};
