#pragma once

#include <QScopedPointer>

class DataContainer;
class BusinessContainerPrivate;

class BusinessContainer
{
public:
    explicit BusinessContainer(DataContainer& dataContainer);
    ~BusinessContainer();

private:
    QScopedPointer<BusinessContainerPrivate> impl_;
}
