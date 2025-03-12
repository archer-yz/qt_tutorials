#include <QWidget>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget w;
    w.setWindowIcon(QIcon(":/resources/key-logo.ico"));

    w.show();

    return app.exec();
}
