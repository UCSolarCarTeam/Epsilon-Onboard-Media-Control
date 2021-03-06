#pragma once

#include <QWidget>

#include "I_CurrentSongUi.h"
#include "I_SongControlUi.h"

class QProgressBar;
class FontLoader;

namespace Ui
{
    class SongPlayerUi;
}

class SongPlayerUi : public QWidget,
    public I_CurrentSongUi,
    public I_SongControlUi
{
    Q_OBJECT
public:
    explicit SongPlayerUi();
    virtual ~SongPlayerUi();

    QLabel& labelPic() override;
    QLabel& infoLabel() override;
    QPushButton& playButton() override;
    QPushButton& shuffleButton() override;
    QPushButton& loopButton() override;
    QSlider& volumeControlSlider() override;
    QPushButton& nextSongButton() override;
    QPushButton& prevSongButton() override;
    QVBoxLayout& progressBarContainer() override;

private:
    QScopedPointer<Ui::SongPlayerUi> ui_;
    QScopedPointer<FontLoader> fontLoader_;
};
