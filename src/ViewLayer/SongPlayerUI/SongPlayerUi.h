#pragma once

#include <QWidget>
#include "I_CurrentSongUi.h"
#include "I_SongControlUi.h"
#include "I_SongPlayerUi.h"

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
    ~SongPlayerUi();
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
    Ui::SongPlayerUi* ui_;
    QScopedPointer<FontLoader> fontLoader_;
};
