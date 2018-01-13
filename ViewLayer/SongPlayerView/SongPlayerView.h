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
    void handleNextButtonClicked();
    void handlePrevButtonClicked();
    void handleVolumeControl();
    void updateGUI(const QString& title, const QString& artist, const QImage& cover);
    void updateProgress(qint64 position,qint64 duration);
};
