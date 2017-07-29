#pragma once
#include <QObject>
#include <QSlider>
#include "../SongPlayerUI/I_SongPlayerUi.h"
#include "../SongPlayerUI/SongPlayerUi.h"
#include "../ProgressBar/ProgressBar.h"
#include "../BusinessLayer/SongPlayer/SongPlayer.h"

class SongPlayer;
class I_SongPlayerUi;
class ProgressBar;

class SongPlayerView : public QWidget
{
    Q_OBJECT

public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar);
    ~SongPlayerView();
    void handlePlayPauseClicked();

private:
    I_SongPlayerUi& ui_;
    SongPlayer& songPlayer_;
    ProgressBar& bar_;

private slots:
    void handlePlayButtonClicked();
    void handleOpenButtonClicked();
    void handleNextButtonClicked();
    void handlePrevButtonClicked();
    void updateTitle(const QString& filePath);
    void updatePosition(qint64 position);
    void updateProgress(qint64 position,qint64 duration);
    void setDuration(qint64 duration);
};
