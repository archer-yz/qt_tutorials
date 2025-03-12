#include "analog_clock.hpp"

#include <QPainter>
#include <QTime>
#include <QTimer>

AnalogClock::AnalogClock(QWidget *parent) : QWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);
    setWindowTitle(tr("Analog Clock"));
    setWindowIcon(QIcon(":/images/key-logo.ico"));
    resize(200, 200);
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    static const QPoint hour_hand[4] = {
        QPoint(5, 14),
        QPoint(-5, 14),
        QPoint(-4, -71),
        QPoint(4, -71)
    };
    static const QPoint minute_hand[4] = {
        QPoint(4, 14),
        QPoint(-4, 14),
        QPoint(-3, -89),
        QPoint(3, -89)
    };
    static const QPoint second_hand[4] = {
        QPoint(1, 14),
        QPoint(-1, 14),
        QPoint(-1, -89),
        QPoint(1, -89)
    };

    const QColor hour_color(palette().color(QPalette::Text));
    const QColor minute_color(palette().color(QPalette::Text));
    const QColor second_color(palette().color(QPalette::Accent));

    int side = qMin(width(), height());

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    QTime time = QTime::currentTime();

    painter.setPen(Qt::NoPen);

    // Draw hour hand
    painter.setBrush(hour_color);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hour_hand, 4);
    painter.restore();

    // Draw hour grid
    // painter.setBrush(palette().color(QPalette::AlternateBase));
    for (int i = 0; i < 12; ++i) {
        painter.drawRect(73, -3, 16, 6);
        painter.rotate(30.0);
    }

    // Draw minute hand
    painter.setBrush(minute_color);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minute_hand, 4);
    painter.restore();

    // Draw second hand
    painter.setBrush(second_color);
    painter.save();
    painter.rotate(6.0 * time.second());
    painter.drawConvexPolygon(second_hand, 4);
    painter.drawEllipse(-3, -3, 6, 6);
    painter.drawEllipse(-5, -68, 10, 10);
    painter.restore();

    // Draw minute grid
    painter.setPen(minute_color);
    for (int i = 0; i < 60; ++i) {
        painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
}


