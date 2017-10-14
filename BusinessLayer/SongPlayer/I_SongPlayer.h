#pragma once

#include <QWidget>

class I_SongPlayer : public QWidget
{
    Q_OBJECT
signals:
    void updateGUI(const QString& fileName, const QString& author, const QImage& cover);
    void togglePlayback();
    void openFile();
};
