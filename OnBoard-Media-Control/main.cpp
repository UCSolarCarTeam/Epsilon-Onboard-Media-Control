#include "songloader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SongLoader sl;
    sl.show();

    return a.exec();
}
