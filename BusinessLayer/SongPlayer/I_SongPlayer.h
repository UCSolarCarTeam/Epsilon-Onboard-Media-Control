#pragma once

#include <QWidget>

class I_SongPlayer : public QWidget
{
    Q_OBJECT
signals:
    void updateGUI(const QString& fileName, const QString& author);
    void togglePlayback();
    void openFile();
};
