#include "SongPlayerView.h"

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui)
    :songPlayer_(songPlayer)
    ,ui_(ui)
{
    ui_.ProgressBar().setMinimum(0);
    ui_.ProgressBar().setTextVisible(false);
    connect(&ui_.PlayButton(),SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.OpenButton(),SIGNAL(clicked()), this, SLOT(handleOpenButtonClicked()));
    connect(&songPlayer_,SIGNAL(updateTitle(const QString&)), this, SLOT(updateTitle(const QString&)));
    connect(&songPlayer_,SIGNAL(updatePosition(qint64)), this, SLOT(updatePosition(qint64)));
    connect(&songPlayer_,SIGNAL(updateDuration(qint64)), this, SLOT(setDuration(qint64)));
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

void SongPlayerView::updateTitle(const QString &filePath)
{
    qDebug() << QFileInfo(filePath).fileName();
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
