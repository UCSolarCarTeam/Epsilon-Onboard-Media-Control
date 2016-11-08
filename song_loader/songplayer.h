#pragma once

#include <QWidget>
#include <QMediaPlayer>

class MusicPlayer : public QWidget
{
    Q_OBJECT
public:
    MusicPlayer(QWidget *parent = 0);

public slots:
    void openFile();
    void playFile(const QString& filePath);
    void togglePlayback();
    void seekForward();
    void seekBackward();

protected:
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private slots:
    void stylize();
    void updateState(QMediaPlayer::State state);
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
    void handleError();

    void updateTaskbar();
    void updateThumbnailToolBar();

private:
    void createWidgets();
    void createShortcuts();
    void createJumpList();
    void createTaskbar();
    void createThumbnailToolBar();

    QWinTaskbarButton* taskbarButton;
    QWinTaskbarProgress* taskbarProgress;
    QWinThumbnailToolBar* thumbnailToolBar;
    QWinThumbnailToolButton *playToolButton;
    QWinThumbnailToolButton *forwardToolButton;
    QWinThumbnailToolButton *backwardToolButton;

    QMediaPlayer mediaPlayer;
    QAbstractButton *playButton;
    VolumeButton *volumeButton;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *infoLabel;
    QPoint offset;
};
