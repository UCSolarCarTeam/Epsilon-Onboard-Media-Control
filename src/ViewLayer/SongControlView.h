#pragma once
#include <QObject>

class I_SongControlPresenter;
class I_SongControlUi;
class I_SongControlEntity;

class SongControlView : public QObject
{
    Q_OBJECT
public:
    SongControlView
    (
        I_SongControlPresenter& songControlPresenter,
        I_SongControlUi& songControlUi
     );
    virtual ~SongControlView() = default;

private slots:
    void playButtonClicked();
    void nextSongButtonClicked();
    void prevSongButtonClicked();
    void shuffleButtonClicked();
    void loopButtonClicked();
    void controlStateUpdate();

//    void setVolumeControl(); //Slider

private:
    I_SongControlPresenter& songControlPresenter_;
    I_SongControlUi& songControlUi_;
    I_SongControlEntity& songEntity_;
};
