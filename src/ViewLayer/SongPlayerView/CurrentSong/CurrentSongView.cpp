#include "CurrentSongView.h"

#include "I_CurrentSongPresenter.h"
#include "I_SongState.h"

#include <I_CurrentSongUi.h>
#include <ProgressBar.h>

#include <QVBoxLayout>
#include <QLabel>

CurrentSongView::CurrentSongView(I_CurrentSongPresenter& currentSongPresenter,
                                 I_CurrentSongUi& currentSongUi,
                                 ProgressBar& progressBar)
    : currentSong_(currentSongPresenter.songState())
    , currentSongUi_(currentSongUi)
    , progressBar_(progressBar)
{
    setupUi();
    connect(&currentSong_, SIGNAL(metaDataChanged()), this, SLOT(updateUiMetaData()));
    connect(&currentSong_, SIGNAL(durationChanged()), this, SLOT(updateUiSongPosition()));
    connect(&currentSong_, SIGNAL(positionChanged()), this, SLOT(updateUiSongPosition()));
}

CurrentSongView::~CurrentSongView()
{
}

void CurrentSongView::setupUi()
{
    currentSongUi_.infoLabel().setAlignment(Qt::AlignCenter);
    currentSongUi_.labelPic().setScaledContents(true);
    currentSongUi_.progressBarContainer().addWidget(&progressBar_);
}

void CurrentSongView::updateUiMetaData()
{
    currentSongUi_.infoLabel().setText(currentSong_.artist() + " - " + currentSong_.songName());

    if (!currentSong_.image().isNull())
    {
        currentSongUi_.labelPic().setPixmap(QPixmap::fromImage(currentSong_.image()));
    }
}

void CurrentSongView::updateUiSongPosition()
{
    progressBar_.progress = static_cast<double>(currentSong_.position()) / static_cast<double>(currentSong_.duration());
    progressBar_.update();
}
