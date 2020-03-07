#include "SongControlView.h"
#include "I_SongControlPresenter.h"
#include "I_SongControlUi.h"
#include "I_SongPlayerState.h"
#include <QPushButton>
#include <QSlider>
SongControlView::SongControlView
(
    I_SongControlPresenter& songControlPresenter,
    I_SongControlUi& songControlUi
):
    songControlPresenter_(songControlPresenter),
    songControlUi_(songControlUi),
    songState_(songControlPresenter_.songPlayerState())
{
    //Connecting buttons to data
    connect(&songControlUi_.playButton(), SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(&songControlUi_.nextSongButton(), SIGNAL(clicked()), this, SLOT(nextSongButtonClicked()));
    connect(&songControlUi_.prevSongButton(),  SIGNAL(clicked()), this, SLOT(prevSongButtonClicked()));
    connect(&songControlUi_.shuffleButton(),  SIGNAL(clicked()), this, SLOT(shuffleButtonClicked()));
    connect(&songControlUi_.loopButton(),  SIGNAL(clicked()), this, SLOT(loopButtonClicked()));
    connect(&songControlUi_.volumeControlSlider(), SIGNAL(valueChanged(int)), this, SLOT(volumeSliderMoved(int)));

    //Connecting states to UI
    connect(&songControlPresenter_.songPlayerState(), SIGNAL(controlStateChanged()), this, SLOT(updateSongControlUi()));
    connect(&songControlPresenter_.songPlayerState(), SIGNAL(playingStateChanged()), this, SLOT(updateSongControlUi()));
    connect(&songControlPresenter_.songPlayerState(), SIGNAL(volumeStateChanged()), this, SLOT(updateSongControlUi()));


    initializeUi();
}

SongControlView::~SongControlView()
{
}

void SongControlView::playButtonClicked()
{
    songControlPresenter_.songPlayerState().setPlaying(!songControlPresenter_.songPlayerState().playing());
}

void SongControlView::nextSongButtonClicked()
{
    songControlPresenter_.playNext();
}

void SongControlView::prevSongButtonClicked()
{
    songControlPresenter_.playPrevious();
}

void SongControlView::shuffleButtonClicked()
{
    songControlPresenter_.songPlayerState().setShuffle(!songControlPresenter_.songPlayerState().shuffle());
}

void SongControlView::loopButtonClicked()
{
    songControlPresenter_.songPlayerState().setLoop(!songControlPresenter_.songPlayerState().loop());
}

void SongControlView::updateSongControlUi()
{
    songControlUi_.playButton().setChecked(songState_.playing());
    songControlUi_.shuffleButton().setChecked(songState_.shuffle());
    songControlUi_.loopButton().setChecked(songState_.loop());
    songControlUi_.volumeControlSlider().setSliderPosition(songControlPresenter_.songPlayerState().volume());
}

void SongControlView::volumeSliderMoved(int newVolume)
{
    songControlPresenter_.songPlayerState().setVolume(newVolume);
}

void SongControlView::initializeUi()
{
    songControlUi_.playButton().setCheckable(true);
    songControlUi_.loopButton().setCheckable(true);
    songControlUi_.shuffleButton().setCheckable(true);
    updateSongControlUi();
}
