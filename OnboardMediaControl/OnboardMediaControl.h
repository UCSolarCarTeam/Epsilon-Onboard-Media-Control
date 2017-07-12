#pragma once

#include <QApplication>
#include <QScopedPointer>

//class DataContainer;
class BusinessContainer;
class ViewContainer;

class EpsilonOnboardMediaControl : public QApplication
{
public:
    EpsilonOnboardMediaControl(int& argc, char** argv);
    ~EpsilonOnboardMediaControl();

private:
    //QScopedPointer<DataContainer> dataContainer_;
    QScopedPointer<BusinessContainer> businessContainer_;
    QScopedPointer<ViewContainer> viewContainer_;
};
