#include "I_SongEntity.h"

#include <QImage>
#include <QMediaContent>
#include <QObject>

class SongEntity : public I_SongEntity
{
public:
    SongEntity();

    // I_SongEntity interface
public:
    QImage image();
    QString artist();
    QString songName();
    qint64 duration();
    qint64 position();

    void setImage(QImage image);
    void setArtist(QString artist);
    void setSongName(QString songName);
    void setDuration(qint64 duration);
    void setPosition(qint64 position);

    //Signals
    void metaDataChanged();
    void positionChanged();

private:
    QImage image_;
    QString artist_;
    QString songName_;
    qint64 duration_;
    qint64 position_;
};
