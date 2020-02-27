#pragma once
#include <QObject>
#include "I_SongControlPresenter.h"

class I_SongControlEntity;
class I_SongController;

class SongControlPresenter : public QObject, public I_SongControlPresenter
{
    Q_OBJECT
public:
    explicit SongControlPresenter(I_SongController& songController, I_SongControlEntity& songEntity);
    virtual ~SongControlPresenter();

public:
    void playNext() override;
    void playPrevious() override;
    I_SongControlEntity& songControlEntity() const override;

private:
    I_SongController& songController_;
    I_SongControlEntity& songEntity_;
};
