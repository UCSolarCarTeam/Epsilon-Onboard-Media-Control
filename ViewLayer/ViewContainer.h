#pragma once

#include <QScopedPointer>

class I_SongPlayerUI;
class SongPlayerView;
class BusinessContainer;

class ViewContainer
{
    public:
        explicit ViewContainer(BusinessContainer& businessContainer);
        ~ViewContainer();

    private:
        I_SongPlayerUI* SongPlayerUI_;
        QScopedPointer<SongPlayerView> SongPlayerView_;
};
