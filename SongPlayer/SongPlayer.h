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
#include <QSlider>
#include <QStandardPaths>
#include <QStyle>
#include <QTime>
#include <QToolButton>
#include <QWidget>

class SongPlayer : public QWidget
{
    Q_OBJECT
public:
    SongPlayer(QWidget* parent = 0);

public slots:
    void openFile();
    void playFile(const QString& filePath);
    void togglePlayback();
    void seekForward();
    void seekBackward();
    void setPosition(int position);

protected:
    bool event(QEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

private slots:
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void updateInfo();
    void handleError();

private:
    void createWidgets();
    void createShortcuts();


    QMediaPlayer mediaPlayer_;
    QAbstractButton* playButton_;
    QSlider* positionSlider_;
    QLabel* positionLabel_;
    QLabel* infoLabel_;
    QPoint offset_;
};
