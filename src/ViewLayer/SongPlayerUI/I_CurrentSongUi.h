#pragma once

class QLabel;
class QVBoxLayout;

class I_CurrentSongUi
{
public:
    virtual ~I_CurrentSongUi() {}

    virtual QLabel& infoLabel() = 0;
    virtual QVBoxLayout& progressBarContainer() = 0;
    virtual QLabel& labelPic() = 0;
};
