#pragma once

#include <QWidget>
#include <QStandardPaths>

class OpenFile : public QWidget
{
    Q_OBJECT
public slots:
    void openFile();
}
