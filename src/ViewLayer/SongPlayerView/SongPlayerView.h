#pragma once

#include <QWidget>

class SongPlayer;
class I_SongPlayerUi;
class ProgressBar;
class ContainerUI;

class SongPlayerView : public QWidget
{
    Q_OBJECT

public:
    SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar, ContainerUI& containerUI);
    ~SongPlayerView();
    void handlePlayPauseClicked();

private:
    SongPlayer& songPlayer_;
    I_SongPlayerUi& ui_;
    ProgressBar& bar_;
    ContainerUI& containerUI_;

private slots:
    void handlePlayButtonClicked();
    void handleNextButtonClicked();
    void handlePrevButtonClicked();
    void handleShuffleButtonClicked();
    void handleLoopButtonClicked();
    void handleVolumeControl();
    void handlePlayerToListClicked();
    void updateGUI(const QString& title, const QString& artist, const QPixmap& cover);
    void updateProgress(qint64 position, qint64 duration);
};
