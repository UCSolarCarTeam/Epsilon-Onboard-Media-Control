#pragma once

#include "I_SongController.h"

#include <QObject>
#include <QScopedPointer>

class I_SongPlayer;
class I_SongControlEntity;
class QUrl;
class QRandomGenerator;
template <class T> class QList;
template <class T> class QStack;

class SongController : public QObject, I_SongController
{
public:
    explicit SongController(I_SongPlayer& songPlayer, I_SongControlEntity& songControlEntity,
                            QList<QUrl>& songUrls);
    virtual ~SongController() override;

    void playNext() override;
    void playPrevious() override;
    void toggleLoop() override;
    void toggleShuffle() override;
    void togglePlay() override;
    void pause() override;

private:

    void loadSong();

    I_SongPlayer& songPlayer_;
    I_SongControlEntity& songControlEntity_;
    QList<QUrl>& songUrls_;

    int songIndex_;
   QScopedPointer<QRandomGenerator> generator_;
   QScopedPointer<QStack<int>> previousSongs_;

};
