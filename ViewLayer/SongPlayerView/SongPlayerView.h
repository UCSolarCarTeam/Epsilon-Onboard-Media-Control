#pragma once
#include <QObject>
#include "../SongPlayerUI/I_SongPlayerUi.h"
#include "../SongPlayerUI/SongPlayerUi.h"
#include "../BusinessLayer/SongPlayer/SongPlayer.h"

class SongPlayer;
class I_SongPlayerUi;

class SongPlayerView : public QWidget
{

    Q_OBJECT

public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui);
    ~SongPlayerView();
    void handlePlayPauseClicked();

private:
    I_SongPlayerUi& ui_;
    SongPlayer& songPlayer_;

private slots:
    void handlePlayButtonClicked();
    void handleOpenButtonClicked();
    void handleNextButtonClicked();
    void handlePrevButtonClicked();
    void updateTitle(const QString& filePath);
    void updatePosition(qint64 position);
    void setDuration(qint64 duration);
};
