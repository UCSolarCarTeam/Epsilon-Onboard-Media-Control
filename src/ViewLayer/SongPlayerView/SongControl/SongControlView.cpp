#include "SongControlView.h"
#include "I_SongControlPresenter.h"
#include "I_SongControlUi.h"
#include "I_SongControlEntity.h"
#include <QPushButton>
#include <QSlider>
SongControlView::SongControlView
(
    I_SongControlPresenter& songControlPresenter,
    I_SongControlUi& songControlUi
):
    songControlPresenter_(songControlPresenter),
    songControlUi_(songControlUi),
    songEntity_(songControlPresenter_.songControlEntity())
{
    //Connecting buttons to data
    connect(&songControlUi_.playButton(), SIGNAL(clicked()), this, SLOT(playButtonClicked()));
    connect(&songControlUi_.nextSongButton(), SIGNAL(clicked()), this, SLOT(nextSongButtonClicked()));
    connect(&songControlUi_.prevSongButton(),  SIGNAL(clicked()), this, SLOT(prevSongButtonClicked()));
    connect(&songControlUi_.shuffleButton(),  SIGNAL(clicked()), this, SLOT(shuffleButtonClicked()));
    connect(&songControlUi_.loopButton(),  SIGNAL(clicked()), this, SLOT(loopButtonClicked()));
    connect(&songControlUi_.volumeControlSlider(), SIGNAL(valueChanged(int)), this, SLOT(volumeSliderMoved(int)));

    //Connecting states to UI
    connect(&songControlPresenter_.songControlEntity(), SIGNAL(controlStateChanged()), this, SLOT(updateSongControlUi()));
    connect(&songControlPresenter_.songControlEntity(), SIGNAL(playingStateChanged()), this, SLOT(updateSongControlUi()));
    connect(&songControlPresenter_.songControlEntity(), SIGNAL(volumeStateChanged()), this, SLOT(updateSongControlUi()));


    initializeUi();
}

void SongControlView::playButtonClicked()
{
    songControlPresenter_.songControlEntity().setPlaying(!songControlPresenter_.songControlEntity().playing());
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
    songControlPresenter_.songControlEntity().setShuffle(!songControlPresenter_.songControlEntity().shuffle());
}

void SongControlView::loopButtonClicked()
{
    songControlPresenter_.songControlEntity().setLoop(!songControlPresenter_.songControlEntity().loop());
}

void SongControlView::updateSongControlUi()
{
    songControlUi_.playButton().setChecked(songEntity_.playing());
    songControlUi_.shuffleButton().setChecked(songEntity_.shuffle());
    songControlUi_.loopButton().setChecked(songEntity_.loop());
    songControlUi_.volumeControlSlider().setSliderPosition(songControlPresenter_.songControlEntity().volume());
}

void SongControlView::volumeSliderMoved(int newVolume)
{
    songControlPresenter_.songControlEntity().setVolume(newVolume);
}

void SongControlView::initializeUi()
{
    songControlUi_.playButton().setCheckable(true);
    songControlUi_.loopButton().setCheckable(true);
    songControlUi_.shuffleButton().setCheckable(true);
    updateSongControlUi();
}
