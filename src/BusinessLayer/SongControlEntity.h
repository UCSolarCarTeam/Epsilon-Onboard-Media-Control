#pragma once

#include "I_SongControlEntity.h"

#include <QObject>

class SongControlEntity : public QObject, I_SongControlEntity
{
    Q_OBJECT
public:
    explicit SongControlEntity();
    virtual ~SongControlEntity();

    bool shuffle() override;
    void setShuffle(bool shuffle) override;

    bool loop() override;
    void setLoop(bool loop) override;

signals:
    void controlStateChanged() override;

private:
    bool shuffle_;
    bool loop_;
};
