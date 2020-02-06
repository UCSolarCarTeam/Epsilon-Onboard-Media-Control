#include <QDir>
#include <QLabel>
#include <QPushButton>
#include <QObject>
#include <QLabel>
#include <QFuture>
#include <QSlider>
#include <QtConcurrent/QtConcurrent>
#include <QColor>
#include <QVBoxLayout>
#include <ContainerUI/ContainerUI.h>

#include "ProgressBar/ProgressBar.h"
#include "SongPlayerView.h"
#include "SongPlayerUI/I_SongPlayerUi.h"
#include "../BusinessLayer/SongPlayer/SongPlayer.h"

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

    const QColor DEFAULT_COLOR = QColor(255, 255, 255, 255);
    const int NUM_THREADS = 4;
}

SongPlayerView::SongPlayerView(SongPlayer& songPlayer, I_SongPlayerUi& ui, ProgressBar& bar, ContainerUI& containerUI)
    : songPlayer_(songPlayer)
    , ui_(ui)
    , bar_(bar)
    , containerUI_(containerUI)
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
    connect(&ui_.playerToList(), SIGNAL(clicked()), this, SLOT(handlePlayerToListClicked()));
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

void SongPlayerView::handlePlayerToListClicked()
{
    containerUI_.setCurrentIndex(1);
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

        for (int i = 0; i < NUM_THREADS; i++)
        {
            //spawn threads
            QFuture<QColor> future = QtConcurrent::run(&this->songPlayer_, &SongPlayer::getColor, img, i );
            //add brightest color to vector
            colors.push_back(future.result());
        }

        QColor max = colors.at(0);

        //find brightest color in image
        for (int i = 0; i < colors.size(); i++)
        {
            if (colors.at(i).saturation() > max.saturation())
            {
                max = colors.at(i);
            }
        }

        ui_.volumeControl().setStyleSheet(styleSheet.arg(max.name()));
        bar_.changeColor(max);
    }
}

void SongPlayerView::updateProgress(qint64 position, qint64 duration)
{
    bar_.progress = static_cast<double>(position) / static_cast<double>(duration);
    bar_.update();
}
