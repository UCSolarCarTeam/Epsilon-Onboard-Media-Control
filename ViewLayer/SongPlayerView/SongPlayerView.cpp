#include "SongPlayerView.h"
#include <QDebug>

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar)
    : songPlayer_(songPlayer)
    , ui_(ui)
    , bar_(bar)
{
    ui_.infoLabel().setAlignment(Qt::AlignCenter);
    bar_.show();
    //ui_.nextSong -> setIcon(QIcon("Data"));
    connect(&ui_.PlayButton(), SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.OpenButton(), SIGNAL(clicked()), this, SLOT(handleOpenButtonClicked()));
    connect(&ui_.NextSong(), SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
    connect(&ui_.PrevSong(), SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));
    connect(&songPlayer_, SIGNAL(updateTitle(const QString&)), this, SLOT(updateTitle(const QString&)));
    connect(&songPlayer_, SIGNAL(updatePosition(qint64)), this, SLOT(updatePosition(qint64)));
    connect(&songPlayer_, SIGNAL(updateDuration(qint64)), this, SLOT(setDuration(qint64)));
    connect(&songPlayer_,SIGNAL(updateProgress(qint64,qint64)), this,SLOT(updateProgress(qint64,qint64)));
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

void SongPlayerView::handleNextButtonClicked()
{
    songPlayer_.playNext();
}

void SongPlayerView::handlePrevButtonClicked()
{
    songPlayer_.playPrevious();
}

void SongPlayerView::updateTitle(const QString& filePath)
{
    ui_.infoLabel().setText(QFileInfo(filePath).fileName());
}

void SongPlayerView::updatePosition(qint64 position)
{
    position = position / 1000;
    ui_.ProgressBar().setValue(position);
}

void SongPlayerView::setDuration(qint64 duration)
{
    duration = duration / 1000;
    ui_.ProgressBar().setMaximum(duration);
}

void SongPlayerView::updateProgress(qint64 position, qint64 duration)
{
    bar_.progress = (double)position/(double)duration;
    bar_.update();
}
