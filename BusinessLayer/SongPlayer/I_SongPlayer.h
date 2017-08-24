#pragma once

#include <QWidget>

class I_SongPlayer : public QWidget
{
    Q_OBJECT
signals:
    void updateTitle(const QString& fileName);
    void togglePlayback();
    void openFile();
};
