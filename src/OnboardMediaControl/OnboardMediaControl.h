#pragma once

#include <QApplication>
#include <QScopedPointer>

class BusinessContainer;
class ViewContainer;

class EpsilonOnboardMediaControl : public QApplication
{
public:
    EpsilonOnboardMediaControl(int& argc, char** argv);
    ~EpsilonOnboardMediaControl();

private:
    QScopedPointer<BusinessContainer> businessContainer_;
    QScopedPointer<ViewContainer> viewContainer_;
};
