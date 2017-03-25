#include "SongPlayerView.h"
#include "SongPlayerUi.h"
#include "SongPlayer.h"

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, SongPlayerUi& ui)
    :songPlayer_(songPlayer)
    ,ui_(ui)
{
    connect(&ui_.PlayButton(),SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.OpenButton(),SIGNAL(clicked()), this, SLOT(handleOpenButtonClicked()));
}

SongPlayerView::~SongPlayerView()
{
}

void SongPlayerView::handlePlayButtonClicked()
{
    songPlayer_.togglePlayback();
}

void SongPlayerView::handleOpenButtonClicked()
{
    songPlayer_.openFile();
}
