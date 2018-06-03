#include "GStreamerMediaPlayer.h"

GStreamerMediaPlayer::GStreamerMediaPlayer()
{
    connect(&mediaPlayer_, SIGNAL(stateChanged(QMediaPlayer::State)), this, SIGNAL(stateChanged()));
    connect(&mediaPlayer_, SIGNAL(durationChanged(qint64)), this, SIGNAL(durationChanged(qint64)));
    connect(&mediaPlayer_, SIGNAL(positionChanged(qint64)), this, SIGNAL(positionChanged(qint64)));
    connect(&mediaPlayer_, SIGNAL(metaDataAvailableChanged(bool)), this, SIGNAL(metaDataAvailableChanged(bool)));
}
void GStreamerMediaPlayer::play()
{
    mediaPlayer_.play();
}
void GStreamerMediaPlayer::pause()
{
    mediaPlayer_.pause();
}
qint64 GStreamerMediaPlayer::position()
{
    return mediaPlayer_.position();
}
qint64 GStreamerMediaPlayer::duration()
{
    return mediaPlayer_.duration();
}
MediaStatus GStreamerMediaPlayer::mediaStatus()
{
    MediaStatus status = MediaStatus::Error;

    switch(mediaPlayer_.mediaStatus())
    {
        case QMediaPlayer::NoMedia:
        {
            status = MediaStatus::NoMedia;
            break;
        }
        default:
        {
            break;
        }
    }
        return status;
}

PlayerState GStreamerMediaPlayer::state()
{
    PlayerState status = PlayerState::Stopped;

    switch(mediaPlayer_.state())
    {
        case QMediaPlayer::StoppedState:
        {
            status = PlayerState::Stopped;
            break;
        }
        case QMediaPlayer::PausedState:
        {
            status = PlayerState::Paused;
            break;
        }
        case QMediaPlayer::PlayingState:
        {
            status = PlayerState::Playing;
            break;
        }
        default:
        {
            break;
        }
    }
        return status;
}

void GStreamerMediaPlayer::setMedia(const QString& filePath)
{
    mediaPlayer_.setMedia(QUrl::fromLocalFile(filePath));
}
void GStreamerMediaPlayer::setVolume(int volume)
{
    mediaPlayer_.setVolume(volume);
}
QString GStreamerMediaPlayer::metaData(const QString& key)
{
    return mediaPlayer_.metaData(key).toString();
}
