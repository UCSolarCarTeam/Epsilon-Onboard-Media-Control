#include "ProgressBar.h"

ProgressBar::ProgressBar()
{
}

ProgressBar::~ProgressBar()
{
}

void ProgressBar::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    QPen pen;
    pen.setWidth(7);
    pen.setColor(QColor(92,145,161));
    p.setPen(pen);

    p.setRenderHint(QPainter::Antialiasing);

    //consult drawArc method in Qt doc
    QRectF rectangle(27.0, 27.0, 138.0, 138.0);
    int startAngle = -90 * 16;
    int spanAngle = progress * 360 * 16;

    p.drawArc(rectangle, startAngle, spanAngle);
}
