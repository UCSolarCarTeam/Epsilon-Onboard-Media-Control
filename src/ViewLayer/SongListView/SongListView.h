#pragma once
#include <QWidget>
#include "../SongListUI/I_SongListUI.h"
#include "../ContainerUI/ContainerUI.h"
#include "../../BusinessLayer/SongPlayer/SongPlayer.h"
#include "../listItem/listItem.h"
#include "../SongPlayerUI/SongPlayerUi.h"

class SongPlayer;
class I_SongListUI;
class I_SongPlayerUi;
class SongListView: public QWidget
{

    Q_OBJECT
public:
    SongListView(SongPlayer& songPlayer, I_SongListUI& ui, ContainerUI& containerUI, I_SongPlayerUi& songPlayerUI);
    ~SongListView();
private:
    SongPlayer& songPlayer_;
    I_SongListUI& ui_;
    ContainerUI& containerUI_;
    I_SongPlayerUi& songPlayerUI_;
    QVector<listItem*> infoList_;
    void addSongsToList();
    void addFilePaths();
public slots:
    void handleListToPlayerClicked();
    void handleSongButtonClicked(QString path);
};

