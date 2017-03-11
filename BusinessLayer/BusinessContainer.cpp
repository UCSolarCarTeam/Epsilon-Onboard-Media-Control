#include "BusinessContainer.h"
#include "../DataLayer/DataContainer.h"

class BusinessContainerPrivate
{
    public:
        BusinessConteinerPrivate(DataContainer& dataContainer)
        {
        }
}
BusinessContainer::BusinessContainer(DataContainer& dataContainter)
    : impl_(new BusinessContainerPrivate(dataContainer))
{
}

BusinessContainer::~BusinessContainer()
{
}
