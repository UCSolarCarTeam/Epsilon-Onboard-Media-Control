#include "ProgressBar.h"

namespace
{
    // Angle must specified be in 1/16th of a degree
    const int FULL_CIRCLE = 5760;   // 360 * 16
    const int START_ANGLE = -1440;  // The bottom of the circle is -90 * 16
    const QColor DEFAULT_COLOR = QColor(219, 160, 56, 255);
}


ProgressBar::ProgressBar()
{
    color_ = DEFAULT_COLOR;
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::paintEvent(QPaintEvent*)
{
    QPainter p(this);

    pen_.setWidth(7);
    pen_.setColor(color_);
    p.setPen(pen_);

    p.setRenderHint(QPainter::Antialiasing);

    //consult drawArc method in Qt doc
    QRectF rectangle(27.0, 27.0, 138.0, 138.0);
    int spanAngle = progress * FULL_CIRCLE;

    p.drawArc(rectangle, START_ANGLE, spanAngle);
}

void ProgressBar::changeColor(QColor color)
{
    color_ = color;
}
