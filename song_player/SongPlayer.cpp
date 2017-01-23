#include "SongPlayer.h"

namespace
{
const int MS_TO_MINUTES = 60000;
const double MS_TO_SECONDS = 1000.0;
const int PAGE_STEP_INCREMENTS = 10;
}

SongPlayer::SongPlayer(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createShortcuts();

    connect(&mediaPlayer_, &QMediaPlayer::positionChanged, this, &SongPlayer::updatePosition);
    connect(&mediaPlayer_, &QMediaPlayer::durationChanged, this, &SongPlayer::updateDuration);
    connect(&mediaPlayer_, &QMediaObject::metaDataAvailableChanged, this, &SongPlayer::updateInfo);

}

void SongPlayer::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("open file"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("mp3 files (*.mp3);;all files (*.*)"));
    if (!filePath.isEmpty())
    {
        playFile(filePath);
    }
    else
    {
        qDebug() << "File path is empty";
    }
}

void SongPlayer::playFile(const QString &filePath)
{
    playButton_->setEnabled(true);
    infoLabel_->setText(QFileInfo(filePath).fileName());

    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer_.play();
}

void SongPlayer::togglePlayback()
{
    if (mediaPlayer_.mediaStatus() == QMediaPlayer::NoMedia)
    {
        openFile();
    }
    else if (mediaPlayer_.state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer_.pause();
    }
    else
    {
        mediaPlayer_.play();
    }

}

void SongPlayer::seekForward()
{
    positionSlider_->triggerAction(QSlider::SliderPageStepAdd);
}

void SongPlayer::seekBackward()
{
    positionSlider_->triggerAction(QSlider::SliderPageStepSub);
}

bool SongPlayer::event(QEvent *event)
{
    return QWidget::event(event);
}

void SongPlayer::mousePressEvent(QMouseEvent *event)
{

    offset_ = event->globalPos() - pos();
    event->accept();
}

void SongPlayer::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset_);
    event->accept();
}

void SongPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    offset_ = QPoint();
    event->accept();
}

void SongPlayer::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        playButton_->setToolTip(tr("Pause"));
        playButton_->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playButton_->setToolTip(tr("Play"));
        playButton_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void SongPlayer::updatePosition(qint64 position)
{
    positionSlider_->setValue(position);

    QTime duration(0, position / MS_TO_MINUTES, qRound((position % MS_TO_MINUTES) / MS_TO_SECONDS));
    positionLabel_->setText(duration.toString(tr("mm:ss")));
}

void SongPlayer::updateDuration(qint64 duration)
{
    positionSlider_->setRange(0, duration);
    positionSlider_->setEnabled(duration > 0);
    positionSlider_->setPageStep(duration / PAGE_STEP_INCREMENTS);
}

void SongPlayer::setPosition(int position)
{
    // avoid seeking when the slider valuechange is triggered from updatePosition()
    if (qAbs(mediaPlayer_.position() - position) > 99)
    {
        mediaPlayer_.setPosition(position);
    }
}

void SongPlayer::updateInfo()
{
    QStringList info;
    QString author = mediaPlayer_.metaData("Author").toString();
    if (!author.isEmpty())
    {
        info += author;
    }
    QString title = mediaPlayer_.metaData("Title").toString();
    if (!title.isEmpty())
    {
        info += title;
    }
    if (!info.isEmpty())
    {
        infoLabel_->setText(info.join(tr(" - ")));
    }
}

void SongPlayer::handleError()
{
    playButton_->setEnabled(false);
    infoLabel_->setText(tr("Error: %1").arg(mediaPlayer_.errorString()));
}

void SongPlayer::createWidgets()
{
    playButton_ = new QToolButton(this);
    playButton_->setEnabled(false);
    playButton_->setToolTip(tr("Play"));
    playButton_->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton_, &QAbstractButton::clicked, this, &SongPlayer::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton_->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &SongPlayer::openFile);

    positionSlider_ = new QSlider(Qt::Horizontal, this);
    positionSlider_->setEnabled(false);
    positionSlider_->setToolTip(tr("Seek"));
    connect(positionSlider_, &QAbstractSlider::valueChanged, this, &SongPlayer::setPosition);

    infoLabel_ = new QLabel(this);
    positionLabel_ = new QLabel(tr("00:00"), this);
    positionLabel_->setMinimumWidth(positionLabel_->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton_);
    controlLayout->addWidget(positionSlider_);
    controlLayout->addWidget(positionLabel_);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel_);
    mainLayout->addLayout(controlLayout);

}

void SongPlayer::createShortcuts()
{
    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, this);
    connect(quitShortcut, &QShortcut::activated, QCoreApplication::quit);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &SongPlayer::togglePlayback);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &SongPlayer::togglePlayback);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &SongPlayer::seekForward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &SongPlayer::seekBackward);
}
