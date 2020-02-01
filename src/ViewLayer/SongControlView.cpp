#include "SongControlView.h"
#include "I_SongControlPresenter.h"
#include "SongPlayerUI/I_SongControlUi.h"
#include "I_SongControlEntity.h"
#include <QPushButton>
SongControlView::SongControlView
(
    I_SongControlPresenter& songControlPresenter,
    I_SongControlUi& songControlUi
):
    songControlPresenter_(songControlPresenter),
    songControlUi_(songControlUi),
    songEntity_(songControlPresenter_.songControlEntity())
{
    connect(&songControlUi_.playButton(), SIGNAL(clicked()), this, SLOT(playedButtonClicked()));
    connect(&songControlUi_.nextSongButton(), SIGNAL(clicked()), this, SLOT(nextSongButtonClicked()));
    connect(&songControlUi_.prevSongButton(),  SIGNAL(clicked()), this, SLOT(prevSongButtonClicked()));
    connect(&songControlUi_.shuffleButton(),  SIGNAL(clicked()), this, SLOT(shuffleButtonClicked()));
    connect(&songControlUi_.loopButton(),  SIGNAL(clicked()), this, SLOT(loopButtonClicked()));
    connect(&songControlPresenter_.songControlEntity(), SIGNAL(controlStateChanged()), this, SLOT(controlStateUpdate()));
//  connect(&songControlUi_.volumeControlSlider())
}

void SongControlView::playButtonClicked()
{
    songControlPresenter_.togglePlay();
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
    songControlPresenter_.toggleShuffle();
}

void SongControlView::loopButtonClicked()
{
    songControlPresenter_.toggleLoop();
}

void SongControlView::controlStateUpdate()
{
    songControlUi_.loopButton().setChecked(songEntity_.loop());
}
