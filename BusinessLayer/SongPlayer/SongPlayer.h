#pragma once

#include <QAbstractButton>
#include <QBoxLayout>
#include <QCoreApplication>
#include <QDebug>
#include <QFileDialog>
#include <QLabel>
#include <QMediaPlayer>
#include <QMouseEvent>
#include <QShortcut>
#include <QStandardPaths>
#include <QStyle>
#include <QTime>
#include <QToolButton>
#include <QWidget>
#include <QProgressBar>
#include <QScopedPointer>
#include <QMediaMetaData>
#include "../SongControl/SongControl.h"

class SongPlayer : public QWidget
{
    Q_OBJECT
public:
    SongPlayer(QWidget* parent = 0);
    QLabel* infoLabel_;
    QProgressBar* positionSlider_;
    ~SongPlayer();

public slots:
    void openFile();
    void openNext();
    void openPrevious();
    void playNext();
    void playPrevious();
    void playFile(const QString& filePath);
    void togglePlayback();
    void adjustVolume(int volume);

private slots:
    void updateState();
    void durationChanged(qint64 duration);
    void positionChanged(qint64 progress);
    void updateInfo();

private:
    QScopedPointer<SongControl> controller_;
    void createWidgets();
    void createShortcuts();
    QAbstractButton* playButton_;
    QLabel* positionLabel_;
    QPoint offset_;
    QMediaPlayer mediaPlayer_;
    qint64 position_;
    qint64 duration_;
    QString title_;
    QString artist_;
    QImage cover_;

signals:
    void updateGUI(const QString& title, const QString& author);
    void resetPosition(const QMediaPlayer& media);
    void updateProgress(qint64 position, qint64 duration);
};
