#include <QFileDialog>
#include <QDebug>
#include "OpenFile.h"

void OpenFile::openFile()
{
    const QStringList musicPaths = QStandardPaths::standardLocations(QStandardPaths::MusicLocation);
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("open file"),
                                     musicPaths.isEmpty() ? QDir::homePath() : musicPaths.first(),
                                     tr("mp3 files (*.mp3);;all files (*.*)"));
    if (!filePath.isEmpty())
    {
  //      playFile(filePath);
    }
    else
    {
        qDebug() << "File path is empty";
    }
}

void OpenFile::openNext()
{/*
    const QString filePath = QString::fromStdString(controller.next_song());
    if(!filePath.isEmpty())
    {
       playFile(filePath); 
    }
    else
    {
        qDebug() << "Warning filepath is empty";
    }*/
}
