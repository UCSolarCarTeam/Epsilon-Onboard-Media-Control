#pragma once

#include "I_CurrentSongPresenter.h"

#include <QObject>

class CurrentSongPresenter : public QObject, public I_CurrentSongPresenter
{
public:
    explicit CurrentSongPresenter(I_SongEntity& songEntity);
    virtual ~CurrentSongPresenter();

public:
    I_SongEntity& songEntity() const override;

private:
    I_SongEntity& songEntity_;
};
