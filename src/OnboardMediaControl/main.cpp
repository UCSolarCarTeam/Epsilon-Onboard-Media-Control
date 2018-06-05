#include "OnboardMediaControl.h"
#include <QApplication>


int main(int argc, char* argv[])
{
    QScopedPointer<EpsilonOnboardMediaControl> app;
    app.reset(new EpsilonOnboardMediaControl(argc, argv));
    return app->exec();
}
