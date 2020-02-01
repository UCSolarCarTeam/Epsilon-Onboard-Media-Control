#include "CurrentSongView.h"

#include "I_CurrentSongPresenter.h"
#include "I_SongEntity.h"

#include <SongPlayerUI/I_CurrentSongUi.h>
#include <ProgressBar/ProgressBar.h>

#include <QVBoxLayout>
#include <QLabel>

CurrentSongView::CurrentSongView(I_CurrentSongPresenter &currentSongPresenter,
                                 I_CurrentSongUi &currentSongUi,
                                 ProgressBar& progressBar)
    : currentSong_(currentSongPresenter.songEntity())
    , currentSongUi_(currentSongUi)
    , progressBar_(progressBar)
{
    setupUi();
    connect(&currentSong_, SIGNAL(metaDataChanged()), this, SLOT(updateUiMetaData()));
    connect(&currentSong_, SIGNAL(positionChanged()), this, SLOT(updateUiSongPosition()));
}

CurrentSongView::~CurrentSongView()
{
}

void CurrentSongView::setupUi()
{
    currentSongUi_.infoLabel().setAlignment(Qt::AlignCenter);
    currentSongUi_.progressBarContainer().addWidget(&progressBar_);
}

void CurrentSongView::updateUiMetaData()
{
    currentSongUi_.infoLabel().setText(currentSong_.artist() + " - " + currentSong_.songName());
    if(!currentSong_.image().isNull())
    {
        currentSongUi_.labelPic().setPixmap(QPixmap::convertFromImage(currentSong_.image()));
    }
}

void CurrentSongView::updateUiSongPosition()
{
    progressBar_.progress = static_cast<double>(currentSong_.position()) / static_cast<double>(currentSong_.duration());
    progressBar_.update();
}
