#include "SongPlayerView.h"
#include <QDebug>

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar)
    : songPlayer_(songPlayer)
    , ui_(ui)
    , bar_(bar)
{
    ui_.infoLabel().setAlignment(Qt::AlignCenter);
    ui_.PlayButton().setCheckable(true);
    ui_.PlayButton().setChecked(false);
    ui_.ShuffleButton().setCheckable(true);
    ui_.ShuffleButton().setChecked(false);
    ui_.LoopButton().setCheckable(true);
    ui_.LoopButton().setChecked(false);
    connect(&ui_.PlayButton(), SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.NextSong(), SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
    connect(&ui_.PrevSong(), SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));
    connect(&ui_.ShuffleButton(), SIGNAL(clicked()), this, SLOT(handleShuffleButtonClicked()));
    connect(&ui_.LoopButton(), SIGNAL(clicked()), this, SLOT(handleLoopButtonClicked()));
    connect(&ui_.volumeControl(), SIGNAL(valueChanged(int)), this, SLOT(handleVolumeControl()));
    connect(&songPlayer_, SIGNAL(updateGUI(const QString&, const QString&)), this, SLOT(updateGUI(const QString&, const QString&)));
    connect(&songPlayer_,SIGNAL(updateProgress(qint64,qint64)), this,SLOT(updateProgress(qint64,qint64)));
    ui_.progressBarContainer().addWidget(&bar_);
}

SongPlayerView::~SongPlayerView()
{
}

void SongPlayerView::handlePlayButtonClicked()
{
    songPlayer_.togglePlayback();
}

void SongPlayerView::handleNextButtonClicked()
{
    ui_.PlayButton().setChecked(true);
    songPlayer_.playNext();
}

void SongPlayerView::handlePrevButtonClicked()
{
    ui_.PlayButton().setChecked(true);
    songPlayer_.playPrevious();
}

void SongPlayerView::handleShuffleButtonClicked()
{
    if(ui_.LoopButton().isChecked())
    {
        ui_.LoopButton().setChecked(false);
        songPlayer_.toggleLoop();
    }

    songPlayer_.toggleShuffle();
}

void SongPlayerView::handleLoopButtonClicked()
{
    if(ui_.ShuffleButton().isChecked())
    {
        ui_.ShuffleButton().setChecked(false);
        songPlayer_.toggleShuffle();
    }

    songPlayer_.toggleLoop();
}

void SongPlayerView::handleVolumeControl()
{
    int volume = ui_.volumeControl().value();
    songPlayer_.adjustVolume(volume);
}

void SongPlayerView::updateGUI(const QString& title, const QString& artist)
{
    ui_.infoLabel().setText(artist + " - " + title);
}

void SongPlayerView::updateProgress(qint64 position, qint64 duration)
{
    bar_.progress = (double)position/(double)duration;
    bar_.update();
}
