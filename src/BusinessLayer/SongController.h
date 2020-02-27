#pragma once

#include "I_SongController.h"

#include <QObject>
#include <QScopedPointer>

class I_SongPlayer;
class I_SongControlEntity;
class I_SongUrlSource;
class QUrl;
class QRandomGenerator;
template <class T> class QStack;

class SongController : public QObject, public I_SongController
{
    Q_OBJECT
public:
    explicit SongController(I_SongPlayer& songPlayer, I_SongControlEntity& songControlEntity,
                            I_SongUrlSource& songUrlSource);
    virtual ~SongController() override;

    void playNext() override;
    void playPrevious() override;

private slots:
    void toggleSongPlayingState();
    void changeVolumeState();

private:
    void loadSong();

    I_SongPlayer& songPlayer_;
    I_SongControlEntity& songControlEntity_;
    QList<QUrl> songUrls_;

    int songIndex_;
    QScopedPointer<QRandomGenerator> generator_;
    QScopedPointer<QStack<int>> previousSongs_;

};
