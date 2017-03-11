#pragma once

#include <QScopedPointer>

class SongPlayerView;
class BusinessContainer;

class ViewContainer
{
    public:
        explicit ViewContainer(BusinessContainer& businessContainer);
        ~ViewContainer();

    private:
        QScopedPointer<SongPlayerView> SongPlayerView_;
}
