#include "notepad.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Notepad w;

    w.show();

    return app.exec();
}
