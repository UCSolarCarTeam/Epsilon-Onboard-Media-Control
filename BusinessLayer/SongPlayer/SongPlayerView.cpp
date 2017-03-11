#include "SongPlayerView.h"
#include "SongPlayerUi.h"
#include "SongPlayer.h"

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, SongPlayerUi& ui)
    :songPlayer_(songPlayer)
    ,ui_(ui)
{
    connect(&ui_.PlayButton(),SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));

    connect(&ui_.OpenButton(), SIGNAL(clicked()), this, SLOT(hanlePlayButtonClicked()));

    connect(&ui_.PositionSlider(), SIGNAL(valueChanged(int)), this, SLOT(handlePositionSlider(int)));

    //show();
}

void SongPlayerView::handlePlayButtonClicked()
{
    songPlayer_.togglePlayback();
}

void SongPlayerView::handleOpenButtonClicked()
{
    songPlayer_.openFile();
}

void SongPlayerView::handlePositionSlider(int position)
{
    songPlayer_.setPosition(position);
}
