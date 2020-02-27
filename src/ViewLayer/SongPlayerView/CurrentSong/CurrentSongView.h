#pragma once

#include <QObject>

class I_CurrentSongPresenter;
class I_CurrentSongUi;
class I_SongEntity;
class ProgressBar;

class CurrentSongView : public QObject
{
    Q_OBJECT
public:
    explicit CurrentSongView(I_CurrentSongPresenter& currentSongPresenter,
                             I_CurrentSongUi& currentSongUi,
                             ProgressBar& progressBar);
    virtual ~CurrentSongView();

private:
    void setupUi();

private slots:
    void updateUiMetaData();
    void updateUiSongPosition();

private:
    I_SongEntity& currentSong_;
    I_CurrentSongUi& currentSongUi_;
    ProgressBar& progressBar_;
};
