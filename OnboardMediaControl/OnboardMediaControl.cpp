#include <QCommandLineParser>

#include "../DataLayer/DataContainer.h"
#include "../BusinessLayer/BusinessContainer.h"
#include "../ViewLayer/ViewContainer.h"
#include "OnboardMediaControl.h"

EpsilonDashboard::EpsilonDashboard(int& argc, char** argv)
    : QApplication(argc, argv)
    , dataContainer_(new DataContainer())
    , businessContainer_(new BusinessContainer(*dataContainer_))
{
}

EpsilonDashboard::~EpsilonDashboard()
{
}
