#include "analog_clock.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    // app.setWindowIcon(QIcon(":/images/key-logo.ico"));
    AnalogClock w;

    w.show();

    return app.exec();
}
