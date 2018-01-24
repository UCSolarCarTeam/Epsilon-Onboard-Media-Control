#pragma once

#include <QWidget>
#include <QPaintEvent>
#include <QPainter>

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    ProgressBar();
    ~ProgressBar();
    double progress;

protected:
    void paintEvent(QPaintEvent *);
};
