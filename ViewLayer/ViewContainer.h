#pragma once

#include <QScopedPointer>

class I_SongPlayerUi;
class SongPlayerView;
class BusinessContainer;

class ViewContainer
{
    public:
        explicit ViewContainer(BusinessContainer& businessContainer);
        ~ViewContainer();

    private:
        I_SongPlayerUi* SongPlayerUI_;
        QScopedPointer<SongPlayerView> SongPlayerView_;
};
