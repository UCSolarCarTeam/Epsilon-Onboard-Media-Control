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
    void changeColor(QColor color);

private:
    QPen pen_;
    QColor color_;

protected:
    void paintEvent(QPaintEvent *);
};
