#include <QApplication>

#include "OnboardMediaControl.h"

int main(int argc, char* argv[])
{
#if QT_VERSION >= 0x050600
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QScopedPointer<EpsilonOnboardMediaControl> app;
    app.reset(new EpsilonOnboardMediaControl(argc, argv));
    return app->exec();
}
