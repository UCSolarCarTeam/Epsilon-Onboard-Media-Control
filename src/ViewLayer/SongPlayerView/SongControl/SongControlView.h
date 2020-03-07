#pragma once
#include <QObject>

class I_SongControlPresenter;
class I_SongControlUi;
class I_SongPlayerState;

class SongControlView : public QObject
{
    Q_OBJECT
public:
    SongControlView
    (
        I_SongControlPresenter& songControlPresenter,
        I_SongControlUi& songControlUi
    );
    virtual ~SongControlView();

private slots:
    void playButtonClicked();
    void nextSongButtonClicked();
    void prevSongButtonClicked();
    void shuffleButtonClicked();
    void loopButtonClicked();
    void updateSongControlUi();
    void volumeSliderMoved(int newVolume);

private:

    void initializeUi();

    I_SongControlPresenter& songControlPresenter_;
    I_SongControlUi& songControlUi_;
    I_SongPlayerState& songState_;
};
