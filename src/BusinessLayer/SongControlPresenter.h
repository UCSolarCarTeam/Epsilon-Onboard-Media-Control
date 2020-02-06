#pragma once
#include <QObject>
#include "I_SongControlPresenter.h"

class I_SongControlEntity;
class I_SongController;

class SongControlPresenter : public QObject, I_SongControlPresenter
{
    Q_OBJECT
public:
    SongControlPresenter(I_SongController& songController, I_SongControlEntity& songEntity);


    // I_SongControlPresenter interface
public:
    void togglePlay() override;
    void playNext() override;
    void playPrevious() override;
    void toggleShuffle() override;
    void toggleLoop() override;
    I_SongControlEntity &songControlEntity() const override;

private:
    I_SongController& songController_;
    I_SongControlEntity& songEntity_;
};
