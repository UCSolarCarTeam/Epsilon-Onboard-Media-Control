#include <QDir>
#include "SongPlayerView.h"

namespace
{
    const QString STYLESHEET = "QSlider::groove:vertical {"
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

    const QColor DEFAULT_COLOR = QColor(219, 160, 56, 255);
}

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar)
    : songPlayer_(songPlayer)
    , ui_(ui)
    , bar_(bar)
{
    ui_.infoLabel().setAlignment(Qt::AlignCenter);
    ui_.playButton().setCheckable(true);
    ui_.playButton().setChecked(false);
    ui_.shuffleButton().setCheckable(true);
    ui_.shuffleButton().setChecked(false);
    ui_.loopButton().setCheckable(true);
    ui_.loopButton().setChecked(false);
    connect(&ui_.playButton(), SIGNAL(clicked()), this, SLOT(handlePlayButtonClicked()));
    connect(&ui_.nextSong(), SIGNAL(clicked()), this, SLOT(handleNextButtonClicked()));
    connect(&ui_.prevSong(), SIGNAL(clicked()), this, SLOT(handlePrevButtonClicked()));
    connect(&ui_.shuffleButton(), SIGNAL(clicked()), this, SLOT(handleShuffleButtonClicked()));
    connect(&ui_.loopButton(), SIGNAL(clicked()), this, SLOT(handleLoopButtonClicked()));
    connect(&ui_.volumeControl(), SIGNAL(valueChanged(int)), this, SLOT(handleVolumeControl()));
    connect(&songPlayer_, SIGNAL(updateGUI(const QString&, const QString&, const QPixmap&)), this, SLOT(updateGUI(const QString&, const QString&, const QPixmap&)));
    connect(&songPlayer_, SIGNAL(updateProgress(qint64, qint64)), this, SLOT(updateProgress(qint64, qint64)));
    ui_.progressBarContainer().addWidget(&bar_);
}

SongPlayerView::~SongPlayerView()
{
}

void SongPlayerView::handlePlayButtonClicked()
{
    songPlayer_.togglePlayback(ui_.playButton().isChecked());
}

void SongPlayerView::handleNextButtonClicked()
{
    ui_.playButton().setChecked(true);
    songPlayer_.playNext();
}

void SongPlayerView::handlePrevButtonClicked()
{
    ui_.playButton().setChecked(true);
    songPlayer_.playPrevious();
}

void SongPlayerView::handleShuffleButtonClicked()
{
    if (ui_.loopButton().isChecked())
    {
        ui_.loopButton().setChecked(false);
        songPlayer_.toggleLoop();
    }

    songPlayer_.toggleShuffle();
}

void SongPlayerView::handleLoopButtonClicked()
{
    if (ui_.shuffleButton().isChecked())
    {
        ui_.shuffleButton().setChecked(false);
        songPlayer_.toggleShuffle();
    }

    songPlayer_.toggleLoop();
}

void SongPlayerView::handleVolumeControl()
{
    int volume = ui_.volumeControl().value();
    songPlayer_.adjustVolume(volume);
}

void SongPlayerView::updateGUI(const QString& title, const QString& artist, const QPixmap& cover)
{
    ui_.infoLabel().setText(artist + " - " + title);
    QString styleSheet = STYLESHEET;
    QColor white = DEFAULT_COLOR;
    QVector<QColor> colors;
    ui_.volumeControl().setStyleSheet(styleSheet.arg(white.name()));
    bar_.changeColor(white);

    if (!cover.isNull())
    {
        ui_.labelPic().setPixmap(cover);
        ui_.labelPic().setScaledContents(true);
        QImage img(cover.toImage());
        QColor color = songPlayer_.getColor(img);
        ui_.volumeControl().setStyleSheet(styleSheet.arg(color.name()));
        bar_.changeColor(color);
    }

    QImage img(cover.toImage());
    QColor color = songPlayer_.getColor(img);
    ui_.volumeControl().setStyleSheet(styleSheet.arg(color.name()));
    bar_.changeColor(color);
}

void SongPlayerView::updateProgress(qint64 position, qint64 duration)
{
    bar_.progress = (double)position / (double)duration;
    bar_.update();
}
