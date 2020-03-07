#pragma once

#include <QPen>
#include <QWidget>

class QPaintEvent;

class ProgressBar : public QWidget
{
    Q_OBJECT
public:
    ProgressBar();
    ~ProgressBar();
    void changeColor(QColor color);

private:
    double progress_;
    QPen pen_;
    QColor color_;

protected:
    void paintEvent(QPaintEvent*);
};
