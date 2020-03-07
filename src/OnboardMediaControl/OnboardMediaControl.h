#pragma once

#include <QApplication>
#include <QScopedPointer>

class BusinessContainer;
class ViewContainer;
class ExternalContainer;

class EpsilonOnboardMediaControl : public QApplication
{
public:
    EpsilonOnboardMediaControl(int& argc, char** argv);
    ~EpsilonOnboardMediaControl();

private:
    QScopedPointer<ExternalContainer> externalContainer_;
    QScopedPointer<BusinessContainer> businessContainer_;
    QScopedPointer<ViewContainer> viewContainer_;
};
