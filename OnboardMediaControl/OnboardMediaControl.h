#pragma once

#include <QApplication>
#include <QScopedPointer>

class DataContainer;
class BusinessContainer;
class ViewContainer;

class EpsilonDashboard : public QApplication
{
public:
    EpsilonDashboard(int& argc, char** argv);
    ~EpsilonDashboard();

private:
    QScopedPointer<DataContainer> dataContainer_;
    QScopedPointer<CommunicationContainer> communicationContainer_;
    QScopedPointer<BusinessContainer> businessContainer_;
    QScopedPointer<PresenterContainer> presenterContainer_;
    QScopedPointer<ViewContainer> viewContainer_;
};
