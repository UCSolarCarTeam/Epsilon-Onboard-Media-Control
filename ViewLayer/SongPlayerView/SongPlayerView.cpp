#include "SongPlayerView.h"
#include "SongPlayerUi.h"
#include "SongPlayer.h"

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, SongPlayerUi& ui)
    :songPlayer_(songPlayer)
    ,ui_(ui)
{
    connect(&ui_.PlayButton(),SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));

    //show();
}

void SongPlayerView::handlePlayButtonClicked()
{
    songPlayer_.togglePlayback();
}
