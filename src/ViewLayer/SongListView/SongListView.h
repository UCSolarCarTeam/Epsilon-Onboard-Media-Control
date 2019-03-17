#pragma once
#include <QWidget>
#include "../SongListUI/I_SongListUI.h"
#include "../ContainerUI/ContainerUI.h"

class I_SongListUI;
class SongListView: public QWidget
{

    Q_OBJECT
public:
    SongListView(I_SongListUI& ui, ContainerUI& containerUI);
    ~SongListView();
private:
    I_SongListUI& ui_;
    ContainerUI& containerUI_;
private slots:
    void handleListToPlayerClicked();
    void addSongsToList();
};

