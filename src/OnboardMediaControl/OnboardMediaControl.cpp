#include <QCommandLineParser>

#include "BusinessContainer.h"
#include "ExternalContainer.h"
#include "ViewContainer.h"
#include "OnboardMediaControl.h"

EpsilonOnboardMediaControl::EpsilonOnboardMediaControl(int& argc, char** argv)
    : QApplication(argc, argv)
    , externalContainer_(new ExternalContainer())
    , businessContainer_(new BusinessContainer(*externalContainer_))
    , viewContainer_(new ViewContainer(*businessContainer_))
{
}

EpsilonOnboardMediaControl::~EpsilonOnboardMediaControl()
{
}
