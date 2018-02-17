#include "SongPlayerView.h"
#include <QDebug>
#include <QDir>

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar)
    : songPlayer_(songPlayer)
    , ui_(ui)
    , bar_(bar)
{
    ui_.infoLabel().setAlignment(Qt::AlignCenter);
    ui_.PlayButton().setCheckable(true);
    ui_.PlayButton().setChecked(false);
    connect(&ui_.PlayButton(), SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.NextSong(), SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
    connect(&ui_.prevSong(), SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));
    connect(&ui_.volumeControl(), SIGNAL(valueChanged(int)), this, SLOT(handleVolumeControl()));
    connect(&songPlayer_, SIGNAL(updateGUI(const QString&, const QString&, const QPixmap&)), this, SLOT(updateGUI(const QString&, const QString&, const QPixmap&)));
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

void SongPlayerView::handleVolumeControl()
{
    int volume = ui_.volumeControl().value();
    songPlayer_.adjustVolume(volume);
}

void SongPlayerView::updateGUI(const QString& title, const QString& artist, const QPixmap& cover)
{
    ui_.infoLabel().setText(artist + " - " + title);
    if (!cover.isNull())
    {
        ui_.labelPic().setPixmap(cover);
        ui_.labelPic().setScaledContents(true);
    }
    QImage img(cover.toImage());
    QColor color = songPlayer_.getColor(img);
    QString styleSheet = "QSlider::groove:vertical {"
            "background: %1;"
            "width: 4px;"
            "position: absolute;}"

            "QSlider::handle:vertical {"
            "height: 16px;"
            "border-radius: 8px;"
            "background: grey;"
            "margin: 0  -6px;}"

            "QSlider::add-page:vertical {"
            "background: %1;}"

            "QSlider::sub-page:vertical {"
            "background: white;}";
    ui_.volumeControl().setStyleSheet(styleSheet.arg(color.name()));

}

void SongPlayerView::updateProgress(qint64 position, qint64 duration)
{
    bar_.progress = (double)position/(double)duration;
    bar_.update();
}
