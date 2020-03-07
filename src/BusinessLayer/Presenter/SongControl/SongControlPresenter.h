#pragma once

#include "I_SongControlPresenter.h"

#include <QObject>

class I_SongPlayerState;
class I_SongController;

class SongControlPresenter : public QObject, public I_SongControlPresenter
{
    Q_OBJECT
public:
    explicit SongControlPresenter(I_SongController& songController, I_SongPlayerState& songPlayerState);
    virtual ~SongControlPresenter();

public:
    void playNext() override;
    void playPrevious() override;
    I_SongPlayerState& songPlayerState() const override;

private:
    I_SongController& songController_;
    I_SongPlayerState& songState_;
};
