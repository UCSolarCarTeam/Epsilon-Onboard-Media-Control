#include "songplayer.h"

MusicPlayer::MusicPlayer(QWidget *parent) : QWidget(parent)
{
    createWidgets();
    createShortcuts();

    connect(&mediaPlayer, &QMediaPlayer::positionChanged, this, &MusicPlayer::updatePosition);
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, this, &MusicPlayer::updateDuration);
    connect(&mediaPlayer, &QMediaObject::metaDataAvailableChanged, this, &MusicPlayer::updateInfo);

}

void MusicPlayer::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath = "/home/benjamin/Documents/SolarCar/Epsilon-Onboard-Media-Control/SongLibrary";
    QFileDialog::getOpenFileName(this, tr("open file"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("mp3 files (*.mp3);;all files (*.*)"));
    if (!filePath.isEmpty())
    {
        playFile(filePath);
    }
}

void MusicPlayer::playFile(const QString &filePath)
{
    playButton->setEnabled(true);
    infoLabel->setText(QFileInfo(filePath).fileName());

    mediaPlayer.setMedia(QUrl::fromLocalFile(filePath));
    mediaPlayer.play();
}

void MusicPlayer::togglePlayback()
{
    if (mediaPlayer.mediaStatus() == QMediaPlayer::NoMedia)
    {
        openFile();
    }
    else if (mediaPlayer.state() == QMediaPlayer::PlayingState)
    {
        mediaPlayer.pause();
    }
    else
    {
        mediaPlayer.play();
    }

}

void MusicPlayer::seekForward()
{
    positionSlider->triggerAction(QSlider::SliderPageStepAdd);
}

void MusicPlayer::seekBackward()
{
    positionSlider->triggerAction(QSlider::SliderPageStepSub);
}

bool MusicPlayer::event(QEvent *event)
{
    return QWidget::event(event);
}

void MusicPlayer::mousePressEvent(QMouseEvent *event)
{

    offset = event->globalPos() - pos();
    event->accept();
}

void MusicPlayer::mouseMoveEvent(QMouseEvent *event)
{
    move(event->globalPos() - offset);
    event->accept();
}

void MusicPlayer::mouseReleaseEvent(QMouseEvent *event)
{
    offset = QPoint();
    event->accept();
}

void MusicPlayer::updateState(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::PlayingState)
    {
        playButton->setToolTip(tr("Pause"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else
    {
        playButton->setToolTip(tr("Play"));
        playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }
}

void MusicPlayer::updatePosition(qint64 position)
{
    positionSlider->setValue(position);

    QTime duration(0, position / 60000, qRound((position % 60000) / 1000.0));
    positionLabel->setText(duration.toString(tr("mm:ss")));
}

void MusicPlayer::updateDuration(qint64 duration)
{
    positionSlider->setRange(0, duration);
    positionSlider->setEnabled(duration > 0);
    positionSlider->setPageStep(duration / 10);
}

void MusicPlayer::setPosition(int position)
{
    // avoid seeking when the slider valuechange is triggered from updatePosition()
    if (qAbs(mediaPlayer.position() - position) > 99)
    {
        mediaPlayer.setPosition(position);
    }
}

void MusicPlayer::updateInfo()
{
    QStringList info;
    QString author = mediaPlayer.metaData("Author").toString();
    if (!author.isEmpty())
    {
        info += author;
    }
    QString title = mediaPlayer.metaData("Title").toString();
    if (!title.isEmpty())
    {
        info += title;
    }
    if (!info.isEmpty())
    {
        infoLabel->setText(info.join(tr(" - ")));
    }
}

void MusicPlayer::handleError()
{
    playButton->setEnabled(false);
    infoLabel->setText(tr("Error: %1").arg(mediaPlayer.errorString()));
}

void MusicPlayer::createWidgets()
{
    playButton = new QToolButton(this);
    playButton->setEnabled(false);
    playButton->setToolTip(tr("Play"));
    playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    connect(playButton, &QAbstractButton::clicked, this, &MusicPlayer::togglePlayback);

    QAbstractButton *openButton = new QToolButton(this);
    openButton->setText(tr("..."));
    openButton->setToolTip(tr("Open a file..."));
    openButton->setFixedSize(playButton->sizeHint());
    connect(openButton, &QAbstractButton::clicked, this, &MusicPlayer::openFile);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setEnabled(false);
    positionSlider->setToolTip(tr("Seek"));
    connect(positionSlider, &QAbstractSlider::valueChanged, this, &MusicPlayer::setPosition);

    infoLabel = new QLabel(this);
    positionLabel = new QLabel(tr("00:00"), this);
    positionLabel->setMinimumWidth(positionLabel->sizeHint().width());

    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setMargin(0);
    controlLayout->addWidget(openButton);
    controlLayout->addWidget(playButton);
    controlLayout->addWidget(positionSlider);
    controlLayout->addWidget(positionLabel);

    QBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(infoLabel);
    mainLayout->addLayout(controlLayout);

}

void MusicPlayer::createShortcuts()
{
    QShortcut *quitShortcut = new QShortcut(QKeySequence::Quit, this);
    connect(quitShortcut, &QShortcut::activated, QCoreApplication::quit);

    QShortcut *openShortcut = new QShortcut(QKeySequence::Open, this);
    connect(openShortcut, &QShortcut::activated, this, &MusicPlayer::togglePlayback);

    QShortcut *toggleShortcut = new QShortcut(Qt::Key_Space, this);
    connect(toggleShortcut, &QShortcut::activated, this, &MusicPlayer::togglePlayback);

    QShortcut *forwardShortcut = new QShortcut(Qt::Key_Right, this);
    connect(forwardShortcut, &QShortcut::activated, this, &MusicPlayer::seekForward);

    QShortcut *backwardShortcut = new QShortcut(Qt::Key_Left, this);
    connect(backwardShortcut, &QShortcut::activated, this, &MusicPlayer::seekBackward);
}
