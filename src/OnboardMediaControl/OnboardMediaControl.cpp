#include <QCommandLineParser>

#include "../BusinessLayer/BusinessContainer.h"
#include "../ViewLayer/ViewContainer.h"
#include "OnboardMediaControl.h"

EpsilonOnboardMediaControl::EpsilonOnboardMediaControl(int& argc, char** argv)
    : QApplication(argc, argv)
    , businessContainer_(new BusinessContainer())
    , viewContainer_(new ViewContainer(*businessContainer_))
{
}

EpsilonOnboardMediaControl::~EpsilonOnboardMediaControl()
{
}
